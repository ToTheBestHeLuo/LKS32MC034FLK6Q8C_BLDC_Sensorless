 /**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_i2c.c\n
 * 文件标识： 无 \n
 * 内容摘要： I2C外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	         <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ       <td>创建
 * </table>
 */
 #include "lks32mc03x_i2c.h"

static volatile u8 i2c_dma_state = 0;   /**< I2C发送状态 */

/**
 *@brief @b 函数名称:   void I2C_Init(I2C_InitTypeDef *this)
 *@brief @b 功能描述:   I2C初始化
 *@see被引用内容：       SYS_ModuleClockCmd()  SYS_SoftResetModule();
 *@param输入参数：       I2C_InitTypeDef *I2C_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          I2C_InitTypeDef I2C_InitStruct;
          I2C_StructInit(&I2C_InitStruct);                //  初始化结构体
          I2C_InitStruct.ADRCMP           =   DISABLE ;   //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
          I2C_InitStruct.MST_MODE         =   ENABLE  ;   //  I2C 主模式使能
          I2C_InitStruct.SLV_MODE         =   DISABLE ;   //  I2C 从模式使能
          I2C_InitStruct.DMA              =   ENABLE  ;   //  I2C DMA传输使能
          I2C_InitStruct.BaudRate         =   100000 ;    //  I2C 波特率
          I2C_InitStruct.IE               =   ENABLE  ;   //  I2C 中断使能
          I2C_InitStruct.TC_IE            =   ENABLE  ;   //  I2C 数据传输完成中断使能
          I2C_InitStruct.BUS_ERR_IE       =   DISABLE ;   //  I2C 总线错误事件中断使能
          I2C_InitStruct.STOP_IE          =   DISABLE ;   //  I2C STOP 事件中断使能
          I2C_InitStruct.BURST_NACK       =   ENABLE  ;   //  I2C 传输，NACK 事件中断使能
          I2C_InitStruct.BURST_ADDR_CMP   =   DISABLE ;   //  I2C 传输，硬件地址匹配中断使能
          I2C_Init(&I2C_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ           <td>创建
 * </table>
 */
void I2C_Init(I2C_InitTypeDef *this)
{
    SYS_ModuleClockCmd(SYS_Module_I2C,ENABLE);
    SYS_SoftResetModule(SYS_Module_I2C);

    {
        u32 BaudRate;
        BaudRate = ((u32)48000000+((this->BaudRate*17)>>1)) / (this->BaudRate*17) - 1;
        SYS_WR_PROTECT = 0x7A83;    //解除系统寄存器写保护
        SYS_CLK_DIV0 = BaudRate;
        SYS_WR_PROTECT = 0;    //解除系统寄存器写保护
    }
    
    I2C -> ADDR  = (this -> ADRCMP << 7);
    I2C -> CFG   = (this -> IE          << 7) | (this -> TC_IE       << 6) | 
                   (this -> BUS_ERR_IE  << 5) | (this -> STOP_IE     << 4) |
                   (this -> MST_MODE    << 1) | (this -> SLV_MODE);
    I2C -> SCR   = 0;
    I2C -> DATA  = 0;
    I2C -> MSCR  = 0;
    I2C -> BCR   = (this -> BURST_NACK     << 7) | (this -> BURST_ADDR_CMP << 6) |
                   (this -> DMA    << 5);
    I2C -> BSIZE = 0;
    if(this->DMA)
    {
        i2c_dma_init();
    }
}

/**
 *@brief @b 函数名称:   void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
 *@brief @b 功能描述:   I2C结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       I2C_InitTypeDef *I2C_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		      I2C_InitTypeDef I2C_InitStruct;
              I2C_StructInit(&I2C_InitStruct);  //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0      <td>YangZJ      <td>创建
 * </table>
 */ 
void I2C_StructInit(I2C_InitTypeDef *this)
{
    this->ADRCMP           =   DISABLE    ;   //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
    this->MST_MODE         =   DISABLE    ;   //  I2C 主模式使能
    this->SLV_MODE         =   DISABLE    ;   //  I2C 从模式使能
    this->DMA              =   DISABLE    ;   //  I2C DMA传输使能
    this->BaudRate         =   100000     ;   //  I2C 波特率
    this->IE               =   DISABLE    ;   //  I2C 中断使能
    this->TC_IE            =   DISABLE    ;   //  I2C 数据传输完成中断使能
    this->BUS_ERR_IE       =   DISABLE    ;   //  I2C 总线错误事件中断使能
    this->STOP_IE          =   DISABLE    ;   //  I2C STOP 事件中断使能
    this->BURST_NACK       =   DISABLE    ;   //  I2C 传输，NACK 事件中断使能
    this->BURST_ADDR_CMP   =   DISABLE    ;   //  I2C 传输，硬件地址匹配中断使能
}

/**
 *@brief @b 函数名称:   u8 Read_I2c_Bus_State(u16 n)
 *@brief @b 功能描述:   读I2C总线状态
 *@see被引用内容：       无
 *@param输入参数：       n
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		      Read_I2c_Bus_State(1);  
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0      <td>YangZJ      <td>创建
 * </table>
 */
u8 Read_I2c_Bus_State(u16 n)
{
    if(I2C->SCR&n)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

 /**
 *@brief @b 函数名称:   void Clear_I2c_Bus_State(u16 n)
 *@brief @b 功能描述:   I2C总线状态复位
 *@see被引用内容：       无
 *@param输入参数：       n
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		      Clear_I2c_Bus_State(1);  
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0      <td>YangZJ      <td>创建
 * </table>
 */
void Clear_I2c_Bus_State(u16 n)
{
    I2C_SCR &= ~n;
}

/**
 *@brief @b 函数名称:   void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t n)
 *@brief @b 功能描述:   I2C发送数据
 *@see被引用内容：       无
 *@param输入参数：       I2Cx:I2C , n:要发生的一字节数据
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		      I2C_SendData(I2C,0x12);  //发生0x12数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0      <td>YangZJ      <td>创建
 * </table>
 */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t n)
{
    I2Cx->DATA = n;
}

/**
*@brief @b 函数名称:   uint8_t I2C_ReadData(I2C_TypeDef *I2Cx)
*@brief @b 功能描述:   I2C读缓冲区数据
*@see被引用内容：       无
*@param输入参数：       I2Cx:I2C
*@param输出参数：       无
*@return返 回 值：      I2C接收的一字节数据
*@note其它说明：        无
*@warning              无
*@par 示例代码：
*@code
         u8 I2C_Value = 0;		      
         I2C_Value = I2C_ReadData(I2C);  //I2C接收的一字节数据
 @endcode
*@par 修改日志:
* <table>
* <tr><th>Date	        <th>Version  <th>Author  <th>Description
* <tr><td>2022年05月21日 <td>1.0      <td>YangZJ      <td>创建
* </table>
*/
uint8_t I2C_ReadData(I2C_TypeDef *I2Cx)
{
    return I2Cx->DATA;
}

/**
 *@brief @b 函数名称:   static void i2c_dma_delay_over()
 *@brief @b 功能描述:   I2C发送接收等待函数
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          i2c_dma_delay_over(); 
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0      <td>YangZJ    <td>创建
 * </table>
 */
static void i2c_dma_delay_over()
{
	u32 t = 10000000;
	while (i2c_dma_state)       // 等待I2C发送完成
	{
		t--;
		if(t==0)
		{// 避免程序卡死
			return;
		}
	}
    i2c_dma_state = 0;
    while(I2C->MSCR & BIT3)     // 等待I2C总线空闲
    {
		t--;
		if(t==0)
		{// 避免程序卡死
			return;
		}
    }
}

/**
 *@brief @b 函数名称:   void i2c_dma_state_over()
 *@brief @b 功能描述:   I2C发送完成函数
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          void I2C0_IRQHandler    (void)
          {
              I2C->SCR = 0;
              i2c_dma_state_over();  // iic传输完成
          } 
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0      <td>YangZJ    <td>创建
 * </table>
 */ 
void i2c_dma_state_over()  // I2C发送完成
{
    i2c_dma_state = 0;
}

/**
 *@brief @b 函数名称:   static void i2c_dma_state_start()
 *@brief @b 功能描述:   I2C开始发送
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          i2c_dma_state_start(); 
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
static void i2c_dma_state_start() // I2C开始发送
{
    i2c_dma_state = 1;
}

/**
 *@brief @b 函数名称:   void i2c_dma_tx(u8 addr, u8 *data, u8 len)
 *@brief @b 功能描述:   I2C数据发送函数
 *@see被引用内容：       无
 *@param输入参数：       
 *                      addr：IIC发送地址
 *                      data：发送数据缓冲器
 *                      len：发送数据长度
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          u8 i2c_Buff[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
          i2c_dma_tx(0x23 , i2c_Buff , 8);//发生给0x23地址的从机8个字节i2c_Buff数据
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
void i2c_dma_tx(u8 addr, u8 *data, u8 len)
{
	len = (len)?len:1;
	len = (len>16)?16:len;      // 输入限制，1-16
	i2c_dma_delay_over();       // 等待I2C完成
	I2C->ADDR = addr & 0x7f;    // 从设备地址
	I2C->SCR = BIT2;           // I2C传输方向
  I2C->BSIZE = len-1;         // I2C传输数据长度
  DMA_CH3->DMA_CCR = 0;
	DMA_CH3->DMA_CTMS = 16;     // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1,大于I2C数据传输长度即可
	DMA_CH3->DMA_SADR = (u32)data;          // DMA源地址
	DMA_CH3->DMA_DADR = (u32)&(I2C->DATA);  // DMA目的地址
  DMA_CH3->DMA_CCR  = BIT6|BIT1|BIT0;     // 配置DMA传输方向并使能DMA
  i2c_dma_state_start();
	I2C->MSCR = 1;								// 触发I2C发送数据
}

/**
 *@brief @b 函数名称:   void i2c_dma_rx(u8 addr, u8 *data, u8 len)
 *@brief @b 功能描述:   I2C数据接收函数
 *@see被引用内容：       无
 *@param输入参数：       
 *                      addr：IIC发送地址
 *                      data：发送数据缓冲器
 *                      len：发送数据长度
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          u8 i2c_Buff[8] = {0x00};
          i2c_dma_rx(0x23 , i2c_Buff , 8);//将接收0x23地址的从机8个字节存储在i2c_Buff数组内
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
void i2c_dma_rx(u8 addr, u8 *data, u8 len)
{
	len = (len)?len:1;
	len = (len>16)?16:len;      // 输入限制，1-16
	i2c_dma_delay_over();       // 等待I2C完成
	I2C->ADDR = addr & 0x7f;    // 从设备地址
	I2C->SCR = BIT4;          // I2C传输方向
  I2C->BSIZE = len-1;         // I2C传输数据长度
  DMA_CH3->DMA_CCR = 0;
	DMA_CH3->DMA_CTMS = 16;     // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1,大于I2C数据传输长度即可
	DMA_CH3->DMA_SADR = (u32)&(I2C->DATA);  // DMA源地址
	DMA_CH3->DMA_DADR = (u32)data;          // DMA目的地址
  DMA_CH3->DMA_CCR  = BIT4|BIT1|BIT0;     // 配置DMA传输方向并使能DMA
  i2c_dma_state_start();
	I2C->MSCR = 1;								// 触发I2C发送数据
}

/**
 *@brief @b 函数名称:   void i2c_dma_init(void)
 *@brief @b 功能描述:   DMA硬件初始化
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
          i2c_dma_init();//I2C的相关DMA模块硬件初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年05月21日 <td>1.0     <td>YangZJ     <td>创建
 * </table>
 */
void i2c_dma_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;

    DMA_InitStruct.DMA_IRQ_EN       = DISABLE;  /* DMA 中断使能 */
    DMA_InitStruct.DMA_RMODE        = DISABLE;  /* 多轮传输使能 */
    DMA_InitStruct.DMA_CIRC         = DISABLE;  /* 循环模式使能 */
    DMA_InitStruct.DMA_SINC         = DISABLE;  /* 源地址递增使能 */
    DMA_InitStruct.DMA_DINC         = DISABLE;  /* 目的地址递增使能 */
    DMA_InitStruct.DMA_SBTW         = 0;        /* 源地址访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_DBTW         = 0;        /* 目的地址访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN       = DMA_I2C_REQ_EN;   /* 通道 x 硬件 DMA 请求使能，高有效 */
    DMA_InitStruct.DMA_SADR         = 0;        /* DMA 通道 x 源地址 */
    DMA_InitStruct.DMA_DADR         = 0;        /* DMA 通道 x 目的地址 */
    
    DMA_Init(DMA_CH3, &DMA_InitStruct);
	  DMA_CHx_EN(DMA_CH3,DISABLE,1);              /* 关闭DMA使能，DMA 通道 1 数据搬运次数 */
    DMA_IF=0xff;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
