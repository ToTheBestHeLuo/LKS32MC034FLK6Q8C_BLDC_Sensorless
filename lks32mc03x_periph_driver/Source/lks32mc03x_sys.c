/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_sys.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� SYS������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
#include "lks32mc03x_sys.h"

/**
 * @brief �͹��ĳ�ʼ���ṹ�嶨��
 * 
 */
WAKE_InitTypeDef WAKE_InitStruct;

/**
 *@brief @b ��������:   void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b ��������:   SYSģ���ʼ������
 *@see�����ú�����      ��
 *@param���������      SYS_InitTypeDef* SYS_InitStruct
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       һ�㲻ʹ�øú�������Ϊ�漰ģ��϶࣬�Ƚ����ң���Ӧ����������ڸ�ģ��
 *                     ��ʼ���������á�
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
           SYS_InitStruct.PLL_SrcSel = SYS_PLLSRSEL_RCH;    // ʹ���ڲ�4MHz������Ϊʱ������Դ
           SYS_Init(&SYS_InitStruct);
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>Yangzj      <td>����
 * </table>
 */
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
{
    uint32_t tmp1;

    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    tmp1 = SYS_AFE_REG0;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    SYS_AFE_REG0 = tmp1;
    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->Clk_Sel << 8);
    
    SYS_CLK_DIV0 = SYS_InitStruct->Clk_DivI2C;
    SYS_CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS_CLK_FEN = SYS_InitStruct->Clk_FEN;
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b ��������:   void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 *@brief @b ��������:   SYS�ṹ���ʼ��
 *@see�����ú�����      ��
 *@param���������      SYS_InitTypeDef* SYS_InitStruct
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��   
 *@par ʾ�����룺
 *@code    
           SYS_InitTypeDef SYS_InitStruct;
           SYS_StructInit(&SYS_InitStruct);
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
{
    SYS_InitStruct -> PLL_SrcSel  = SYS_PLLSRSEL_RCH;
    SYS_InitStruct -> PLL_DivSel  = 0xFF;
    SYS_InitStruct->Clk_Sel = CLK_SEL_PLL;
                                  
    SYS_InitStruct -> Clk_DivI2C  = SYS_Clk_SPIDiv1;
    SYS_InitStruct -> Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct -> Clk_FEN     = 0;
}

/**
 *@brief @b ��������:   void SYS_ClearRst(void)
 *@brief @b ��������:   SYS�����λ��־��¼
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��ע�����ڸ�λ��¼�����ڵ���ʱ�������ִ�������Ҫһ��ʱ�䣬��Ӧ��
                       ������������¼״̬ 
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           u32 RSET_VALUE = 0;
           SYS_ClearRst();//�����λ��־��¼
           delay_ms(1);
           RSET_VALUE = SYS_GetRstSource();//��ȡ��λԴ��¼ֵ
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void SYS_ClearRst(void)
{
    AON_EVT_RCD = 0xCA40;
}

/**
 *@brief @b ��������:   uint32_t SYS_GetRstSource(void)
 *@brief @b ��������:   ���SYS��λԴ�ź�
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      
 * <table>
 *                     <tr><th>BIT3 <td>���Ź���λ������־<td> ����Ч
 *                     <tr><th>BIT2 <td>������λ������־  <td> ����Ч
 *                     <tr><th>BIT1 <td>HPOR ��λ������־ <td> ����Ч
 *                     <tr><th>BIT0 <td>LPOR ��λ������־ <td> ����Ч
 * </table>
 *@return�� �� ֵ��     ��λԴ��¼ֵ
 *@note����˵����       ����ֵλ����  
 *@warning             ��     
 *@par ʾ�����룺
 *@code    
           u32 RSET_VALUE = 0;
           RSET_VALUE = SYS_GetRstSource();//��ȡ��λԴ��¼ֵ
           �� RSET_VALUE = 0x01;��LPOR������λ
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
uint32_t SYS_GetRstSource(void)
{
    return AON_EVT_RCD;
}

/**
 *@brief @b ��������:   void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b ��������:   ����ģ��ʱ��ʹ�ܺ�ֹͣ
 *@see������ö�٣�      FuncState
 *@param���������   
 *                     state�� ENABLEʹ�� , DISABLE�ر�     
 *                     nModule��������ѡ�� \n 
 * <table> 
 *                     <tr><td> �궨��                   <td>ԭʼֵ    <td>˵��
 *                     <tr><th> SYS_Module_I2C           <td> BIT0    <td> I2Cģ��
 *                     <tr><th> SYS_Module_HALL          <td> BIT1    <td>HALLģ��
 *                     <tr><th> SYS_Module_UART          <td> BIT2    <td>UARTģ��
 *                     <tr><th> SYS_Module_CMP           <td> BIT3    <td> CMPģ��
 *                     <tr><th> SYS_Module_MCPWM         <td> BIT4    <td> MCPWMģ��
 *                     <tr><th> SYS_Module_TIMER0        <td> BIT5    <td>TIMER0ģ��
 *                     <tr><th> SYS_Module_TIMER1        <td> BIT6    <td>TIMER1ģ��
 *                     <tr><th> SYS_Module_GPIO          <td> BIT7    <td>  GPIOģ��
 *                     <tr><th> SYS_Module_DSP           <td> BIT8    <td>DSPģ��
 *                     <tr><th> SYS_Module_ADC           <td> BIT9    <td>ADCģ��
 *                     <tr><th> SYS_Module_SPI           <td> BIT10   <td>SPIģ��
 *                     <tr><th> SYS_Module_DMA           <td> BIT11   <td>DMAģ��
 * </table>
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
        SYS_ModuleClockCmd(SYS_Module_SPI,ENABLE);//ʹ��SPIʱ��
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ         <td>����
 * </table>
 */
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    if (state != DISABLE)
    {
        SYS_CLK_FEN |= nModule;
    }
    else
    {
        SYS_CLK_FEN &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b ��������:   void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
 *@brief @b ��������:   ģ��ģ��ʹ�ܺ�ֹͣ
 *@see������ö�٣�      FuncState
 *@param���������      
 *                     state�� ENABLEʹ�� , DISABLE�ر�  \n 
 *                     nModule��������ѡ�� \n 
 * <table> 
 *                     <tr><td> �궨��                  <td>˵��
 *                     <tr><th> SYS_AnalogModule_ADC   <td>  BIT8  <td> ADCģ��  
 *                     <tr><th> SYS_AnalogModule_OPA   <td>  BIT9  <td> OPA0ģ�� 
 *                     <tr><th> SYS_AnalogModule_BGP   <td>  BIT10 <td> OPA1ģ�� 
 *                     <tr><th> SYS_AnalogModule_DAC   <td>  BIT11 <td> OPA2ģ�� 
 *                     <tr><th> SYS_AnalogModule_TMP   <td>  BIT12 <td> OPA3ģ��
 *                     <tr><th> SYS_AnalogModule_CMP0  <td>  BIT13 <td> CMP0ģ�� 
 *                     <tr><th> SYS_AnalogModule_CMP1  <td>  BIT14 <td> CMP1ģ�� 
 *                     <tr><th> SYS_AnalogModule_PLL   <td>  BIT8  <td> BGPģ��                 
 * </table>
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
        SYS_AnalogModuleClockCmd(SYS_AnalogModule_PLL,ENABLE);//ʹ��PLLģ��
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ         <td>����
 * </table>
 */
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    
    if (state == ENABLE)
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP������ģ�鼫���෴
            SYS_AFE_REG0 &= ~SYS_AnalogModule_BGP;
            nModule &= ~SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 |= nModule;
    }
    else
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP������ģ�鼫���෴
            SYS_AFE_REG0 |= SYS_AnalogModule_BGP;
            nModule |= SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b ��������:   void SYS_SoftResetModule(uint32_t nModule)
 *@brief @b ��������:   ģ����λ����
 *@see�����ú�����      ��
 *@param���������      
 *                     nModule��������ѡ�� \n 
 * <table> 
 *                     <tr><td> �궨��                   <td>ԭʼֵ    <td>˵��
 *                     <tr><th> SYS_Module_I2C           <td> BIT0    <td> I2Cģ��
 *                     <tr><th> SYS_Module_HALL          <td> BIT1    <td>HALLģ��
 *                     <tr><th> SYS_Module_UART          <td> BIT2    <td>UARTģ��
 *                     <tr><th> SYS_Module_CMP           <td> BIT3    <td> CMPģ��
 *                     <tr><th> SYS_Module_MCPWM         <td> BIT4    <td> MCPWMģ��
 *                     <tr><th> SYS_Module_TIMER0        <td> BIT5    <td>TIMER0ģ��
 *                     <tr><th> SYS_Module_TIMER1        <td> BIT6    <td>TIMER1ģ��
 *                     <tr><th> SYS_Module_GPIO          <td> BIT7    <td>  GPIOģ��
 *                     <tr><th> SYS_Module_DSP           <td> BIT8    <td>DSPģ��
 *                     <tr><th> SYS_Module_ADC           <td> BIT9    <td>ADCģ��
 *                     <tr><th> SYS_Module_SPI           <td> BIT10   <td>SPIģ��
 *                     <tr><th> SYS_Module_DMA           <td> BIT11   <td>DMAģ��
 * </table>
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��     
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SYS_SoftResetModule(SYS_Module_ADC);
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SYS_SoftResetModule(uint32_t nModule)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    SYS_SFT_RST = nModule;
    SYS_SFT_RST = 0;
    SYS_WR_PROTECT = 0;
}

/**
 *@brief @b ��������:   void SYS_VolSelModule(uint32_t Vol)
 *@brief @b ��������:   ʱ��У������
 *@see�����ú�����      ��
 *@param���������      Vol��0 3.3 Voltage��1 5.0 Voltage
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��     
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SYS_VolSelModule(0);
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SYS_VolSelModule(uint32_t Vol)
{
	if((Read_Trim(0x000001D4)>>16) >= 0x03)
	{
		if(Vol == 0) //3.3 Voltage
		{

		SYS_AFE_REG5 = (Read_Trim(0x00000198)>>16) & 0xffff; 

		SYS_AFE_REG6 = (Read_Trim(0x0000019C)>>16) & 0xffff; 
        }
        else         // 5.0 Voltage
        {
	    SYS_AFE_REG5 = Read_Trim(0x00000198) & 0xffff;

		SYS_AFE_REG6 = Read_Trim(0x0000019C) & 0xffff;
        }

	}
}

/**
 *@brief @b ��������:   static void SoftDelay(u32 cnt)
 *@brief @b ��������:   ��ʱ����
 *@see�����ú�����      ��
 *@param���������      cnt����ʱcnt�Ŀ�ָ��_NOP()
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       �ĺ���ֻ�ڴ��ļ�ʹ�ã���Ҫ����Switch2PLL������      
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SoftDelay(0xff);//��ʱ255��_NOP()ʱ��1��_NOP��Լ��һ��ϵͳʱ�����ڼ���
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}

/**
 *@brief @b ��������:   void Switch2PLL(void)
 *@brief @b ��������:   ���߻��Ѻ�ϵͳʱ���л���PLLʱ�Ӻ���
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ϵͳ�͹��Ļ���ʹ��  
 *@warning             �� 
 *@par ʾ�����룺
 *@code    
           Switch2PLL();
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void Switch2PLL(void)
{
	  SYS_WR_PROTECT = 0x7a83;                        /*�����Ĵ���дʹ��*/
    SYS_AFE_REG0 = WAKE_InitStruct.AFE_REG0_RECORD; /*���� PLL,BGP*/
    SoftDelay(200);
    SYS_CLK_CFG = WAKE_InitStruct.CLK_CFG_RECORD;   /*����ʱ���л���PLLʱ��*/
	  SYS_WR_PROTECT = 0x0; 
}

/**
 *@brief @b ��������:   void Switch2HRC(void)
 *@brief @b ��������:   ���߻���ǰһʱ�̣��رո���ʱ����BGP�͵������·����
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ϵͳ�͹�������ʹ��   
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           Switch2HRC();
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void Switch2HRC(void)
{
	  SYS_WR_PROTECT = 0x7a83; /*�����Ĵ���дʹ��*/
    WAKE_InitStruct.AFE_REG0_RECORD = SYS_AFE_REG0;
	  WAKE_InitStruct.CLK_CFG_RECORD = SYS_CLK_CFG;
	  SYS_CLK_CFG = 0x101;         /* ʹ��PLL 1/8��Ƶʱ�� */
	  SYS_AFE_REG0 = 0x0400;    /* ׼���ر� PLL,BGP*/  
	  SYS_WR_PROTECT = 0x0; 
}

/**
 *@brief @b ��������:    void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
 *@brief @b ��������:    �������߻���IO
 *@see���ѵ�ƽѡ��ö�٣�  enumWakeTrigLevel 
 *@param���������                           
 * <table>              <tr><td>wakeIO = BIT5: GPIO 1[5]  / P1[5]  �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á� \n
 *                              wakeIO = BIT4: GPIO 0[10] / P0[10] �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á� \n
 *                              wakeIO = BIT3: GPIO 0[9]  / P0[9]  �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á� \n
 *                              wakeIO = BIT2: GPIO 0[8]  / P0[8]  �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á� \n
 *                              wakeIO = BIT1: GPIO 0[2]  / P0[2]  �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á� \n
 *                              wakeIO = BIT0: GPIO 0[0]  / P0[0]  �ⲿ����ʹ�ܡ�1��ʹ�ܣ�0�����á�
 *                      <tr><td>enumWakeTrigLevel : \n
 *                              ���ѵ�ƽѡ�� \n 
 *                              0:�͵�ƽ���� \n
 *                              1:�ߵ�ƽ���� 
 *                      <tr><td>flt: \n
 *                              ENABLE�� ����IO�˲� \n
 *                              DISABLE���ر�IO�˲� 
 *                      <tr><td>ena: \n
 *                              ENABLE�� ����IO���� \n
 *                              DISABLE���ر�IO���� 
 * </table>
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��    
 *@warning             �� 
 *@par ʾ�����룺
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//ϵͳ����ʱ,ʹ��P0.0��Ϊ�͹��Ļ���IO��
           �͵�ƽ����
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SetWakeIO(uint32_t wakeIO, enumWakeTrigLevel trigLevel, uint32_t flt , uint8_t ena)
{
	if(ena == ENABLE)
	{
		AON_IO_WAKE_EN |= wakeIO;
	}
	else
	{
		AON_IO_WAKE_EN &= ~wakeIO;
	}
	
	if (trigLevel == WAKETRIG_HIGH)
	{
		AON_IO_WAKE_POL = 0x01;
	}
	else
	{
		AON_IO_WAKE_POL = 0x00;
	}
	
	if(flt == IOWK_FLT_EN)
	{
	  AON_PWR_CFG = BIT1;
	}else{
		AON_PWR_CFG = 0;
	}
}

/**
 *@brief @b ��������:   void SYS_FallSleep(void)
 *@brief @b ��������:   ����ϵͳ��������״̬
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       �� 
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SYS_FallSleep();
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SYS_FallSleep(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn); /*�ر�TIMER0�ж�*/
	NVIC_DisableIRQ(TIMER1_IRQn); /*�ر�TIMER1�ж�*/
	NVIC_DisableIRQ(I2C_IRQn); /*�ر�I2C�ж�*/
	NVIC_DisableIRQ(SPI_IRQn); /*�ر�SPI�ж�*/
	NVIC_DisableIRQ(GPIO_IRQn); /*�ر�GPIO�ж�*/
	NVIC_DisableIRQ(HALL_IRQn); /*�ر�HALL�ж�*/
	NVIC_DisableIRQ(UART_IRQn); /*�ر�UART�ж�*/
	NVIC_DisableIRQ(CMP_IRQn); /*�ر�CMP�ж�*/
	NVIC_DisableIRQ(ADC_IRQn); /*�ر�ADC�ж�*/
	NVIC_DisableIRQ(MCPWM0_IRQn); /*�ر�MCPWM0�ж�*/
	NVIC_DisableIRQ(MCPWM1_IRQn); /*�ر�MCPWM1�ж�*/
	NVIC_DisableIRQ(DMA_IRQn); /*�ر�DMA�ж�*/
	NVIC_DisableIRQ(SW_IRQn); /*�ر�SW�ж�*/

	IWDG_PSW = 0xA6B4;
	IWDG_CLR = 0x798D;
	SCB->SCR |= (1UL << 2);
	 __WFI();	  /*PCָ��ֹͣ���У��ȴ��ж�*/
}

/**
 *@brief @b ��������:   void SYS_EVTCLRSleep(void)
 *@brief @b ��������:   �������ȫ���¼���¼
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       �� 
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           SYS_EVTCLRSleep();
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SYS_EVTCLRSleep(void)
{
	 AON_EVT_RCD = PSW_EVT_CLR;/* ���ȫ���¼���¼*/
}

/**
 *@brief @b ��������:    void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
 *@brief @b ��������:    �������߻�������
 *@see�����ú�����  ��
 *@param���������                           
 * <table>
 *                     <tr><th>rth <td>���Ź���ʱ��λ����ֵ��Ҳ������װ��ֵ(���ֵ0x1FF000)
 *                     <tr><th>wth <td>���Ź���ʱ��������ֵ(���ֵС��rth)
 *                     <tr><th>ena <td>ENABLE��������ʱ����  DISABLE���رն�ʱ����  
 * </table>
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       
 *               ����ʱ����㹫ʽ��
 *               WakeupIWDG = tLRC * (rth - Iwth) 
 *               tLRC Ϊ LRCʱ�����ڣ�1/64kHz=15.625uS
 *</table>
 *               <tr><th>rth - wth    <td>����ʱ��
 *               <tr><th>16000        <td>0.25S
 *               <tr><th>32000        <td>0.5S
 *               <tr><th>64000        <td>1S
 *               <tr><th>128000       <td>2S
 *               <tr><th>256000       <td>4S  
 *</table> 
 *@warning             �� 
 *@par ʾ�����룺
 *@code    
           SetWakeIO(WAKEIO_P0_0,WAKETRIG_LOW,ENABLE,ENABLE);//ϵͳ����ʱ,ʹ��P0.0��Ϊ�͹��Ļ���IO��
           �͵�ƽ����
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2022��04��26�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void SYS_SetWakeInterval(uint32_t rth , uint32_t wth , uint8_t ena)
{ 
	 if(ena == ENABLE)
	 { 
	   IWDG_CFG |= 0x01 << 4; /*������߶�ʱ����ʹ��*/
	 }else{
		 IWDG_CFG &= ~(0x01 << 4); /*�ر�������߶�ʱ����*/
	 }
	  IWDG_PSW = 0xA6B4;     /*ʹ�ܿ��Ź����ּĴ���д����*/
	  IWDG_RTH = rth;
	  IWDG_WTH = wth;
}

/**
 *@brief @b ��������:   void DSP_Init(void)
 *@brief @b ��������:   DSPʱ��ʹ��
 *@see�����ú�����      ��
 *@param���������      ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       �� 
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           DSP_Init();
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author     <th>Description
 * <tr><td>2016��06��28�� <td>1.0     <td>cfwu      <td>����
 * </table>
 */
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, ENABLE); /* DSPʱ��ʹ��*/
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
