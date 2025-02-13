/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： mingganghuang
 * 完成日期： 2021年11月15日
 *
 *******************************************************************************/
#include "lks32mc03x_lib.h"
#include "hardware_init.h"
#include "delay.h"

#include "sGSlave.h"

/*******************************************************************************
 函数名称：    u8 OPA_CommonVoltageCorrection(void)
 功能描述：    利用硬件的比较器CMP1和DAC完成OPA输出的共模电压的自校正
 输入参数：    无
 输出参数：    无
 返 回 值：    校正以后的OPA共模电压值，单位是DAC的最小分辨率
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/11/24     V1.0          MrYang             创建
 *******************************************************************************/
 u16 MedianFilter(u16 datBuffer[],uint16_t length)
{
    if(length < 3){
        return 0;
    }

    for(int i = 0;i < length - 1;++i){
        for(int j = 0;j < length - i - 1;++j){
            if(datBuffer[j] > datBuffer[j + 1]){
                u16 tmp = datBuffer[j];
                datBuffer[j] = datBuffer[j + 1];
                datBuffer[j + 1] = tmp;
            }
        }
    }

    return datBuffer[length / 2];
}
u8 OPA_CommonVoltageCorrection(void)
{
		u8 cv = 0;u16 cnt = 0;u16 outVoltage = (u16)(1.9f * BIT12);u16 datBuffer[512];
		SYS_WR_PROTECT = 0x7A83;
		/*保存DAC上一次的输出*/
		u32 dacOut = SYS_AFE_DAC & 0x000000FF;
		/*设置DAC输出在1.9V附近*/
		DAC_OutputVoltage(outVoltage);
		/*保存当前比较器1的正端输入以及负端输入*/
		u32 sysReg1 = SYS_AFE_REG1;
		/*设置比较器1的正端输入为OPA的输出，以及负端输入为DAC的输出*/
		SYS_AFE_REG1 = (sysReg1 & 0xFFFF8FCF);
		SYS_AFE_REG1 |= (0x00002000 | 0x00000020);
		/*开始进行自校正*/
		for(;cnt < 512;cnt++){
			delay_us(10);
			if(GET_CMP_data(CMP1,0)) 
				outVoltage += 48;
			else 
				outVoltage -= 48;
			datBuffer[cnt] = outVoltage;
			DAC_OutputVoltage(outVoltage);
		}
		/*恢复当前比较器1的正端输入以及负端输入*/
		SYS_AFE_REG1 = sysReg1;
		/*恢复DAC的输出*/
		SYS_AFE_DAC = dacOut;
		SYS_WR_PROTECT = 0;
		
		cv = MedianFilter(datBuffer,512) / 48;
		return cv;
}
/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void Hardware_init(void)
{
    __disable_irq();                  /* 关闭中断 中断总开关 */
    SYS_WR_PROTECT = 0x7a83;          /* 开启写使能*/
		SYS_AFE_REG1 &= ~BIT1;
    IWDG_DISABLE();                   /* 关闭独立看门狗使能*/
    FLASH_CFG |= 0x00080000;          /* FLASH 预取加速使能*/
    delay_init(48);                   /* 延时函数初始化时钟48MHz*/
	
    GPIO_init();                      /* GPIO初始化 */
		DAC_init();
		CMP_init();
		UTimer_init();
	
    DSP_Cmd(ENABLE);         /* DSP时钟使能*/
	
//		volatile u8 cv = OPA_CommonVoltageCorrection();
		HALL_init();
	  TempSensor_init();                /* 芯片温度传感器初始化*/
		PGA_init();                    		/* PGA初始化 */
		ADC0_init();                   		/* ADC初始化 */
    MCPWM_init();                     /* MCPWM初始化 */
	
//	  IWDG_init();                      /* 看门狗初始化*/
		delay_ms(50);
//		
    NVIC_EnableIRQ(HALL_IRQn);      		/* 使能HALL中断 */
    NVIC_SetPriority(HALL_IRQn, 0); 		/* 配置HALL中断优先级 */
		
    NVIC_EnableIRQ(ADC_IRQn);      		/* 使能ADC中断 */
    NVIC_SetPriority(ADC_IRQn, 4); 		/* 配置ADC中断优先级 */
		
    NVIC_EnableIRQ(CMP_IRQn);      		/* 使能COMP0中断 */
    NVIC_SetPriority(CMP_IRQn, 1); 		/* 配置COMP0优先级 */
		
    NVIC_EnableIRQ(MCPWM0_IRQn);      		/* 使能MCPWM0中断 */
    NVIC_SetPriority(MCPWM0_IRQn, 0); 		/* 配置FMCPWM0优先级 */
		
	  __enable_irq();                   /* 开启总中断 */
		
    NVIC_SetPriority(DMA_IRQn,3); 		/* DMA_IRQn 外部中断优先级设置为4*/
		
    NVIC_SetPriority(TIMER1_IRQn,3); /* TIMER1 外部中断优先级设置为3*/
		
}

/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;   /* 解除系统寄存器写保护 */
    SYS_VolSelModule(1);       /* 0: 3.3V ; 1: 5.0V*/
    SYS_AFE_REG0 |= BIT15;     /* BIT15:PLLPDN */
    SoftDelay(100);            /* 等待PLL稳定*/
	  SYS_CLK_CFG = 0x000001ff; /* BIT[9:8]:0: CLK_HS,1:PLL,2:LRC,3:LRC
                                 | BIT[7:0]CLK_DIV  | 0x1ff对应48M时钟 */
}

/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void SystemInit(void)
{
    Clock_Init(); /* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        HuangMG        创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
	
//		/*P1.3 Debug专用，在最新的硬件中不使用*/
//		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
//    GPIO_Init(GPIO1, &GPIO_InitStruct);
	
		/*P0.9 LED灯光指示*/
    GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
		GPIO_SetBits(GPIO0,GPIO_Pin_9);
	
		/*P1.6 TX，目前先做DEBUG口*/
    GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;  /*新版本不再使用内部上拉功能*/
		GPIO_InitStruct.GPIO_PODEna = ENABLE;			/*使能开漏输出*/
    GPIO_Init(GPIO1, &GPIO_InitStruct);
		GPIO_SetBits(GPIO1,GPIO_Pin_6);
	
		/*P0.0 ADC通道10 上电默认为AIN*/
    GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIO0, &GPIO_InitStruct);		
	
    /*P1.5 TIM1_CH1*/
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; /*GPIO输入模式*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;     /*P1.5*/
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;  /*新版本不再使用内部上拉功能*/
		GPIO_InitStruct.GPIO_PODEna = ENABLE;			/*使能开漏输出*/
    GPIO_Init(GPIO1, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF8_TIMER1); /*IO复用UTIMER功能*/

    /* MCPWM_CH0~MCPWM_CH2 P0.10~P0.15 */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 \
	  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_10, AF3_MCPWM);/*GPIO复用为MCPWM功能*/
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_11, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF3_MCPWM);
		
		/*预驱的使能IO*/
    GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
}
/*******************************************************************************
 函数名称：    void DAC_init(void)
 功能描述：    DAC初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/26    V1.0           YangZJ            创建
 *******************************************************************************/
void DAC_init(void)
{
		DAC_InitTypeDef DAC_InitStructure;
		
		DAC_StructInit(&DAC_InitStructure);
		DAC_InitStructure.DACOUT_EN = DISABLE ;//禁止DAC电压通过P0.0输出
		DAC_Init(&DAC_InitStructure);        /* DAC初始化 */
		DAC_OutputVoltage((1.9f + 25.f / 0.5f * 0.01f) * BIT12);  /* DAC输出，每0.01V对应0.5A过流保护阈值*/
}
/*******************************************************************************
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/25      V1.0           HuangMG              创建
 *******************************************************************************/
void UTimer_init(void)
{
		TIM_TimerInitTypeDef TIM_InitStruct;
    TIM_TimerStrutInit(&TIM_InitStruct); /* Timer结构体变量初始化 */

    TIM_InitStruct.TH = 0xFFFFFFFF;  
                 
    TIM_InitStruct.CLK_DIV = TIM_Clk_Div1;      /* 设置Timer模块数据分频系数 */
    TIM_InitStruct.CH1_MODE = TIMER_OPMode_CAP; /* 设置Timer CH1为捕获，后续也会切换到比较模式*/
		TIM_InitStruct.CH1_FE_CAP_EN = ENABLE;			/* 先使用到CH1的捕获模式，这里给出一个预设值，也即下降沿触发捕获 */
		TIM_InitStruct.CAP1_CLR_EN = ENABLE;				/* 使能捕获模式下的清零功能 */ 
    TIM_InitStruct.CH0_POL = 0;                 /* 计数器回零时，比较模式输出极性控制*/
		TIM_InitStruct.CH1_POL = 0;
    TIM_InitStruct.TIM_CMP1 = 1 - 1;            /* 设置比较模式的CH1比较值*/
	
		TIM_InitStruct.CH0_MODE = TIMER_OPMode_CMP;			/* CH0作为比较模式 */
		TIM_InitStruct.TIM_CMP0 = 160 * 3 - 1;
	
		TIM_InitStruct.FLT = 1;
			
		TIM_InitStruct.IE = TIM_IRQ_IE_CH0; 					/*开启比较中断*/
	
    TIM_TimerInit(TIMER1, &TIM_InitStruct);
	
		/*配置对应的DMA信号传送：由软件使能DMA通道，由TIMER1的比较事件触发GPIOx->PDI到sG专用接收缓冲区*/
    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
		
		DMA_ClearIRQFlag(CH1_FIF);

    DMA_InitStruct.DMA_IRQ_EN = DISABLE;             /* DMA传输完成中断禁止 */
    DMA_InitStruct.DMA_CIRC = DISABLE;              /* DMA传输模式：循环模式，高有效 */
    DMA_InitStruct.DMA_SINC = DISABLE;              /* 源地址递增, 高有效,地址按照SBTW对应大小递增 1/2/4*/
    DMA_InitStruct.DMA_DINC = ENABLE;               /* 目的地址递增,高有效,地址按照DBTW对应大小递增 1/2/4*/
    DMA_InitStruct.DMA_SBTW = DMA_HALFWORD_TRANS;   /* 源访问位宽，0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_DBTW = DMA_HALFWORD_TRANS;   /* 目的访问位宽，0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_TIMER1_REQ_EN; 	/* UTimer的DMA请求使能，高有效*/
    DMA_InitStruct.DMA_RMODE = ENABLE;              /* 0:单轮传输，一轮连续传输多次 或 1:多轮，每轮进行一次数据传输*/
    DMA_InitStruct.DMA_SADR = (u32)&GPIO1->PDI;   /* 设置为GPIO1的输入寄存器的目的地址*/
    DMA_InitStruct.DMA_DADR = (u32)&sG.receiveBuffer[0];     	/* DMA目的地址设置为DHSOT专用的接收缓冲区*/
    DMA_Init(DMA_CH0, &DMA_InitStruct);							/* 由DMA的通道0完成这个事件*/	
}
/*******************************************************************************
 函数名称：    void CMP_init(void)
 功能描述：    比较器初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/26    V1.0           YangZJ            创建
 *******************************************************************************/
void CMP_init(void)
{
    CMP_InitTypeDef CMP_InitStruct;
    CMP_StructInit(&CMP_InitStruct);
    CMP_InitStruct.CLK10_EN             = ENABLE                ;   // 比较器 1/0 滤波时钟使能
    CMP_InitStruct.FIL_CLK10_DIV16      = 5                     ;   // 比较器 1/0 滤波系数       0-0xF
    CMP_InitStruct.FIL_CLK10_DIV2       = 0                     ;   // 比较器 1/0 滤波移位系数   0-0x7   最终分频系数为 (DIV16+1)<<DIV2
    CMP_InitStruct.CMP_FT               = ENABLE               ;   // 比较器快速比较使能
    CMP_InitStruct.CMP_HYS              = CMP_HYS_20mV                     ;   // 比较器回差选择            0：回差20mV 1：回差0mV
    
    CMP_InitStruct.CMP1_EN              = ENABLE               ;   // 比较器 1 使能
    CMP_InitStruct.CMP1_SELP            = CMP_SELP_OPA0_OUT    ;   // 比较器 1 信号正端选择 见 CMP1_SELP_CMP1_IP0 比较器定义
    CMP_InitStruct.CMP1_SELN            = CMP_SELN_DAC         ;   // 比较器 1 信号负端选择
    CMP_InitStruct.CMP1_POL             = 0                     ;   // 比较器 1 极性选择     0：高电平有效 1：低电平有效 只影响比较器中断
    CMP_InitStruct.CMP1_IE              = DISABLE               ;   // 比较器 1 中断使能
    CMP_InitStruct.CMP1_RE              = DISABLE               ;   // 比较器 1 DMA 请求使能
    CMP_InitStruct.CMP1_IRQ_TRIG        = DISABLE               ;   // 比较器 1 边沿触发使能
    CMP_InitStruct.CMP1_IN_EN           = DISABLE               ;   // 比较器 1 信号输入使能 影响比较器数字模块信号，模拟部分不受影响
    CMP_InitStruct.CMP1_CHN3P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN3_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN2P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN2_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN1P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN1_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN0P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN0_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_W_PWM_POL       = DISABLE               ;   // 比较器 1 开窗 PWM 信号极性选择  0:高电平有效；1:低电平有效
    
    CMP_InitStruct.CMP0_EN              = ENABLE                  ;   // 比较器 0 使能
    CMP_InitStruct.CMP0_IN_EN           = ENABLE                  ;   // 比较器 0 信号输入使能
    CMP_InitStruct.CMP0_SELP            = CMP_SELP_IP1            ;   // 比较器 0 信号正端选择
    CMP_InitStruct.CMP0_SELN            = CMP_SELN_HALL_MID            ;   // 比较器 0 信号负端选择
    CMP_InitStruct.CMP0_POL             = 0                     ;   // 比较器 0 极性选择     0：高电平有效 1：低电平有效 只影响比较器中断
    CMP_InitStruct.CMP0_IE              = DISABLE                  ;   // 比较器 0 中断使能
    CMP_InitStruct.CMP0_RE              = DISABLE               ;   // 比较器 0 DMA 请求使能
    CMP_InitStruct.CMP0_W_PWM_POL       = DISABLE               ;   // 比较器 0 开窗 PWM 信号极性选择
    CMP_InitStruct.CMP0_IRQ_TRIG        = ENABLE               ;   // 比较器 0 边沿触发使能
    CMP_InitStruct.CMP0_CHN3P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN3_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN2P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN2_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN1P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN1_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN0P_WIN_EN    = DISABLE               ;   // MCPWM 模块 CHN0_P 通道使能比较器 0 开窗
    CMP_Init(&CMP_InitStruct);
}
/**
 *@brief @b 函数名称:   void TempSensor_Init(void)
 *@brief @b 功能描述:   温度传感器初始化
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		   TempSensor_Init(); //温度传感器初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年11月5日 <td>1.0     <td>Howlet Li      <td>创建
 * </table>
 */
void TempSensor_init(void)
{
		TempSensor_Init();
}
/*******************************************************************************
 函数名称：    void HALL_init(void)
 功能描述：    HALL硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2018/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL_init(void)
{
  HALL_InitTypeDef HALL_InitStruct;
  HALL_StructInit(&HALL_InitStruct);
  HALL_InitStruct.HALL_Ena = ENABLE;             /* 模块使能 */  
  HALL_InitStruct.ClockDivision = HALL_CLK_DIV1; /* 设置Hall模块时钟分频系数 */
  HALL_InitStruct.CountTH = 32767;             /* Hall模块计数模值 */
  HALL_Init(&HALL_InitStruct);
}
/*******************************************************************************
 函数名称：    void PGA_Init(void)
 功能描述：    PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/3/15      V1.0           Howlet Li          创建
 *******************************************************************************/
void PGA_init(void)
{
    OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);

    OPA_InitStruct.OPA_CLEna = ENABLE;       /*使能OPA*/
    OPA_InitStruct.OPA_Gain = PGA_GAIN_20; /*OPA内部增益电阻选择200：10*/
    OPA_InitStruct.OPA_B_EN = OPA0_IN_IP_B;  /*OPA0使用 OPA0_IN_B/OPA0_IP_B 作为差分输入*/
    OPA_Init(OPA, &OPA_InitStruct);

    OPA_OUT(OPA, DISABLE); /* 禁止OPA输出通过外部引脚P0.7输出*/
}

/*******************************************************************************
 函数名称：    void ADC0_init(void)
 功能描述：    ADC0硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/8/25      V1.0          HMG               创建
 *******************************************************************************/
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_StructInit(&ADC_InitStructure);               /*ADC初始化结构体*/
    ADC_InitStructure.Align = ADC_RIGHT_ALIGN;         /* ADC数据输出右对齐*/
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;    /* 设置ADC转换模式为1段式采样 */
    ADC_InitStructure.FirSeg_Ch = ADC_3_TIMES_SAMPLE; /* 第一段共采样3个通道 */
    ADC_InitStructure.Trigger_Cnt = 15;                /* 单段触发模式下触发一次采样所需要的事件数:
                                                        0~15 0表示需要一次触发，15表示需要16次*/
    ADC_InitStructure.ADC_RANGE = ADC_RANGE_3V6;      /* ADC量程选择*/
		ADC_InitStructure.SEL_En = ADC_MCPWM_TRG;				/*设置UTimer为触发来源*/
    ADC_InitStructure.Trigger_En = ADC_HARDWARE_T3_TRG;  /* 开启硬件触发ADC采样使能 */
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;           /* 第一段扫描结束中断*/
    ADC_InitStructure.ADC_SAMP_CLK = 4;              /* 设置采样时间为20个ADC时钟周期 范围4--35*/
    ADC_Init(ADC, &ADC_InitStructure);
    /* ADC采集电流（1m欧姆，Gain=20） ， 温度传感器 , 母线电压（43K：1K，Gain=44）*/
    ADC_CHN0 = ADC_CHANNEL_0 | (ADC_CHANNEL_11 << 4) | (ADC_CHANNEL_10 << 8);

    ADC_IF = 0xff;    /*清中断标志位*/
    ADC_CFG |= BIT11; /*状态机复位控制信号*/
}

/*******************************************************************************
 函数名称：    void MCPWM_init(void)
 功能描述：    MCPWM_init硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/15      V1.0        mingganghuang        创建
 *******************************************************************************/
void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = PWM_Clk_Div1; /* MCPWM时钟分频设置48MHZ */
    MCPWM_InitStructure.MCLK_EN = ENABLE;       /* 模块时钟开启 */
    MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE; /* 时基0主计数器开始计数使能开关 使能*/
    MCPWM_InitStructure.MCPWM_Cnt1_EN = ENABLE; /* 时基1主计数器开始计数使能开关 使能*/
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = EDGE_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = EDGE_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = EDGE_PWM_MODE;
    MCPWM_InitStructure.MCPWM_WorkModeCH3 = EDGE_PWM_MODE;

    /* 自动更新使能寄存器 MCPWM_TMR3*/
    MCPWM_InitStructure.AUEN = TMR3_AUEN;

	  MCPWM_InitStructure.MCPWM_Base0T0_UpdateEN = DISABLE;  /* MCPWM 时基0 T0事件更新 使能 */
    MCPWM_InitStructure.MCPWM_Base0T1_UpdateEN = DISABLE; /* MCPWM 时基0 T1事件更新 禁止*/

    MCPWM_InitStructure.MCPWM_Base1T0_UpdateEN = DISABLE;  /* MCPWM 时基1 T0事件更新 使能 */
    MCPWM_InitStructure.MCPWM_Base1T1_UpdateEN = DISABLE; /* MCPWM 时基1 T1事件更新 禁止*/

    MCPWM_InitStructure.CNT0_T0_Update_INT_EN = DISABLE;   /* 时基0 T0更新事件中斷 禁止 */
    MCPWM_InitStructure.CNT1_T0_Update_INT_EN = DISABLE;   /* 时基1 T0更新事件中斷 禁止 */
		
    MCPWM_InitStructure.TimeBase0_PERIOD = PWM_PERIOD;           /* 时期0周期设置 */
    MCPWM_InitStructure.TimeBase1_PERIOD = PWM_PERIOD;           /* 时期1周期设置 */
		
    MCPWM_InitStructure.TriggerPoint3 = (u16)(-PWM_PERIOD); 		/* MCPWM_TMR3 触发事件T3 设置 */
		MCPWM_InitStructure.TMR3_TimeBase_Sel = 0;						/* 选择时基0作为TMR3事件的触发点*/ 
		MCPWM_InitStructure.CNT0_T0_Update_INT_EN = ENABLE;	/* CNT0对应的更新中断使能 */

    MCPWM_InitStructure.DeadTimeCH0123N = DEADTIME; /* CH0123N死区时间设置 */
    MCPWM_InitStructure.DeadTimeCH0123P = DEADTIME; /* CH0123P死区时间设置 */

    MCPWM_InitStructure.CH0_PS = DISABLE;                     /* CH0_P信号来源，1：来自CH0_SCTRLP；0：来自MCPWM实际运行计数器*/
		MCPWM_InitStructure.CH0_NS = DISABLE;                      /* CH0_N信号来源，1：来自CH0_SCTRLN；0：来自MCPWM实际运行计数器*/
		MCPWM_InitStructure.CH1_PS = DISABLE;                      /* CH1_P信号来源，1：来自CH1_SCTRLP；0：来自MCPWM实际运行计数器*/
		MCPWM_InitStructure.CH1_NS = DISABLE;                      /* CH1_N信号来源，1：来自CH1_SCTRLN；0：来自MCPWM实际运行计数器*/
		MCPWM_InitStructure.CH2_PS = DISABLE;                      /* CH2_P信号来源，1：来自CH2_SCTRLP；0：来自MCPWM实际运行计数器*/
		MCPWM_InitStructure.CH2_NS = DISABLE;                      /* CH2_N信号来源，1：来自CH2_SCTRLN；0：来自MCPWM实际运行计数器*/
		
		MCPWM_InitStructure.CH0P_SCTRLP = ENABLE;                /* 当CH0_PS = 1时，输出到CH0_P通道的值*/
		MCPWM_InitStructure.CH0N_SCTRLN = DISABLE;                 /* 当CH0_NS = 1时，输出到CH0_N通道的值 配置CH0N输出高电平*/
		MCPWM_InitStructure.CH1P_SCTRLP = ENABLE;                 /* 当CH1_PS = 1时，输出到CH1_P通道的值 配置CH1P输出高电平*/
		MCPWM_InitStructure.CH1N_SCTRLN = DISABLE;                /* 当CH1_NS = 1时，输出到CH1_N通道的值 配置CH1N输出低电平*/
		MCPWM_InitStructure.CH2P_SCTRLP = ENABLE;                 /* 当CH2_PS = 1时，输出到CH2_P通道的值 配置CH2P输出高电平*/
		MCPWM_InitStructure.CH2N_SCTRLN = DISABLE;                 /* 当CH2_NS = 1时，输出到CH2_N通道的值配置CH2N输出低电平*/
		
    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 不交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 | CH1P和CH1N是否选择信号交换 不交换*/
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 | CH2P和CH2N是否选择信号交换 不交换*/

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;      /* CH0P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;     /* CH0N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;      /* CH2P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;     /* CH2N对应引脚在空闲状态输出高电平 */
		
		MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;           /* CH0P通道输出极性设置 | 正常输出 */
		MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0N通道输出极性设置 | 取反输出 */
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;           /* CH1P通道输出极性设置 | 正常输出 */
		MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;           /* CH1N通道输出极性设置 | 取反输出 */
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;           /* CH2P通道输出极性设置 | 正常输出 */
		MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;           /* CH2N通道输出极性设置 | 取反输出 */


    MCPWM_InitStructure.IO_PPE = DISABLE ; /* MCPWM推挽模式使能设置 关闭 */

    MCPWM_InitStructure.DebugMode_PWM_out = ENABLE;       /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
                                                                 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
    MCPWM_InitStructure.GPIO_BKIN_Filter = 4; /* 急停事件(来自IO口信号)数字滤波器时间设置1-256 */
    MCPWM_InitStructure.CMP_BKIN_Filter = 4;  /* 急停事件(来自比较器信号)数字滤波器时间设置1-256 */
		
		/*注：对通道0，1，2而言，FAIL0信号来自于CMP0或者外部刹车输入，而FAIL1信号来自于CMP1或者外部刹车输入*/

    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;           /* FAIL0事件 中断使能或关闭 */
    MCPWM_InitStructure.FAIL0_INPUT_EN = DISABLE;         /* FAIL1通道急停功能打开或关闭 */
    MCPWM_InitStructure.FAIL0_Signal_Sel = FAIL_SEL_CMP;  /* FAIL1事件信号选择，比较器或IO口 */
    MCPWM_InitStructure.FAIL0_Polarity = HIGH_LEVEL_VALID; /* FAIL1事件极性选择，高有效或低有效 */

    MCPWM_InitStructure.FAIL1_INT_EN = ENABLE;            /* FAIL1事件 中断使能设置 使能 */
    MCPWM_InitStructure.FAIL1_INPUT_EN = ENABLE;          /* FAIL1通道急停功能使能 使能 */
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1事件信号选择，比较器或IO口 比较器 */
    MCPWM_InitStructure.FAIL1_Polarity = HIGH_LEVEL_VALID; /* FAIL1事件极性选择，高有效或低有效 高有效 */
		
		MCPWM_InitStructure.FAIL2_INT_EN = DISABLE;            /* FAIL1事件 中断使能设置 禁止 */
    MCPWM_InitStructure.FAIL2_INPUT_EN = DISABLE;          /* FAIL1通道急停功能使能 禁止 */
    MCPWM_InitStructure.FAIL2_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1事件信号选择，比较器或IO口 比较器 */
    MCPWM_InitStructure.FAIL2_Polarity = HIGH_LEVEL_VALID; /* FAIL1事件极性选择，高有效或低有效 高有效 */
		
		MCPWM_InitStructure.FAIL3_INT_EN = DISABLE;            /* FAIL1事件 中断使能设置 禁止 */
    MCPWM_InitStructure.FAIL3_INPUT_EN = DISABLE;          /* FAIL1通道急停功能使能 禁止 */
    MCPWM_InitStructure.FAIL3_Signal_Sel = FAIL_SEL_CMP;    /* FAIL1事件信号选择，比较器或IO口 比较器 */
    MCPWM_InitStructure.FAIL3_Polarity = HIGH_LEVEL_VALID; /* FAIL1事件极性选择，高有效或低有效 高有效 */

    MCPWM_Init(MCPWM0, &MCPWM_InitStructure); /* MCPWM0 模块初始化 */
	
    MCPWM_SwapFunction();
		GPIO_SetBits(GPIO1,GPIO_Pin_1);
}
/*******************************************************************************
 函数名称：    void IWDG_init(void)
 功能描述：    看门狗初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/26    V1.0           YangZJ            创建
 *******************************************************************************/
void IWDG_init(void)
{
    IWDG_InitTypeDef IWDG_InitStruct;
    IWDG_StrutInit(&IWDG_InitStruct);
    IWDG_InitStruct.WDG_EN  = ENABLE;      //使能看门狗
    IWDG_InitStruct.RTH     = SECOND2IWDGCNT(2.0);//设置看门狗
    IWDG_InitStruct.DWK_EN  = DISABLE;     // 深度休眠定时唤醒关闭   
    IWDG_InitStruct.WTH     = 0;           // 看门狗定时唤醒时间（21位计数器，但低12恒位0）
    IWDG_Init(&IWDG_InitStruct);
    IWDG_ENABLE();                         // 开启看门狗
}
/*******************************************************************************
 函数名称：    void DebugPWM_OutputFunction(void)
 功能描述：    PWM输出功能调试   输出25%占空比
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{   //输出25%的PWM信号
    MCPWM_TH00 = (-(PWM_PERIOD >> 2));
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = (-(PWM_PERIOD >> 2));
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = (-(PWM_PERIOD >> 2));
    MCPWM_TH21 = (PWM_PERIOD >> 2);
    MCPWM_TH30 = (-(PWM_PERIOD >> 2));
    MCPWM_TH31 = (PWM_PERIOD >> 2);

    PWMOutputs(MCPWM0, ENABLE);
    PWMOutputs_CH3(MCPWM0, ENABLE);
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/*******************************************************************************
 函数名称：    uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 功能描述：    GPIO电平反转函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
uint8_t Invers_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    u16 reg;
    reg = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin); //读GPIO电平
    if (reg)
    {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
        return 0;
    }
    else
    {
        GPIO_SetBits(GPIOx, GPIO_Pin);
        return 1;
    }
}
