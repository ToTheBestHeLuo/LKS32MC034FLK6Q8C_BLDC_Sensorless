/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_mcpwm.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� MCPWM������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
#include "lks32mc03x_mcpwm.h"
#include "string.h"

/**
 *@brief @b ��������:   void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
 *@brief @b ��������:   MCPWM CH0/CH1/CH2�źŲ������ʹ����ʧ�ܺ���
 *@see���������ݣ�      ��
 *@param���������      MCPWMx:MCPWM0, FuncState t_state ENABLE��ʹ��, DISABLE��ʹ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
		   PWMOutputs(MCPWM0, ENABLE); //ʹ��MCPWM���
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
{
    MCPWMx->PWM_PRT = 0x0000DEAD;
    if (t_state == ENABLE)
    {
        MCPWMx->PWM_FAIL012 |= MCPWM_MOE_ENABLE_MASK;
    }
    else
    {
        MCPWMx->PWM_FAIL012 &= MCPWM_MOE_DISABLE_MASK;
    }
    MCPWMx->PWM_PRT = 0x0000CAFE;
}

/**
 *@brief @b ��������:   void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
 *@brief @b ��������:   MCPWM CH3�źŲ������ʹ����ʧ�ܺ���
 *@see���������ݣ�      ��
 *@param���������      MCPWMx:MCPWM0, FuncState t_state ENABLE��ʹ��, DISABLE��ʹ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
		   PWMOutputs_CH3(MCPWM0, ENABLE);  //ʹ��MCPWM���
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
{
    MCPWMx->PWM_PRT = 0x0000DEAD;
    if (t_state == ENABLE)
    {
        MCPWMx->PWM_FAIL3 |= MCPWM_MOE_ENABLE_MASK;
    }
    else
    {
        MCPWMx->PWM_FAIL3 &= MCPWM_MOE_DISABLE_MASK;
    }
    MCPWMx->PWM_PRT = 0x0000CAFE;
}

/**
 *@brief @b ��������:   void MCPWM_StructInit(MCPWM_InitTypeDef* MCPWM_InitStruct)
 *@brief @b ��������:   MCPWM�ṹ���ʼ��
 *@see���������ݣ�       ��
 *@param���������       MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
            MCPWM_InitTypeDef MCPWM_InitStructure;
            MCPWM_StructInit(&MCPWM_InitStructure);//��ʼ��MCPWM��ؽṹ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
void MCPWM_StructInit(MCPWM_InitTypeDef *MCPWM_InitStruct)
{

    memset(MCPWM_InitStruct, 0, sizeof(MCPWM_InitTypeDef));
}

/**
 *@brief @b ��������:   void MCPWM_Init(MCPWM_REG_TypeDef *MCPWMx, MCPWM_InitTypeDef *MCPWM_InitStruct)
 *@brief @b ��������:   MCPWM��ʼ������
 *@see���������ݣ�      SYS_ModuleClockCmd()
 *@param���������      MCPWM_InitTypeDef *MCPWM_InitStruct
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
           MCPWM_InitTypeDef MCPWM_InitStructure;
           MCPWM_StructInit(&MCPWM_InitStructure);
           MCPWM_InitStructure.CLK_DIV = PWM_Clk_Div1;                 // MCPWMʱ�ӷ�Ƶ����48MHZ 
           MCPWM_InitStructure.MCLK_EN = ENABLE;                       // ģ��ʱ�ӿ��� 
           MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE;                 // ʱ��0����������ʼ����ʹ�ܿ��� ʹ��
           MCPWM_InitStructure.MCPWM_Cnt1_EN = ENABLE;                 // ʱ��1����������ʼ����ʹ�ܿ��� ʹ��
           MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;
           MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE;   // ͨ������ģʽ���ã����Ķ������ض���
           MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;
           MCPWM_InitStructure.MCPWM_WorkModeCH3 = CENTRAL_PWM_MODE;
           MCPWM_Init(&MCPWM_InitStructure);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0       <td>HMG         <td>����
 * </table>
 */
void MCPWM_Init(MCPWM_REG_TypeDef *MCPWMx, MCPWM_InitTypeDef *MCPWM_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_MCPWM, ENABLE);

    MCPWMx->PWM_PRT = 0x0000DEAD; /*enter password to unlock write protection */
    MCPWMx->PWM_TCLK = MCPWM_InitStruct->CLK_DIV | (MCPWM_InitStruct->MCLK_EN << 2) | (MCPWM_InitStruct->TMR2_TimeBase_Sel << 4) | (MCPWM_InitStruct->TMR3_TimeBase_Sel << 5) | (MCPWM_InitStruct->TimeBase0_Trig_Enable << 8) | (MCPWM_InitStruct->TimeBase1_Trig_Enable << 9);
    MCPWMx->PWM_TH0 = MCPWM_InitStruct->TimeBase0_PERIOD;
    MCPWMx->PWM_TH1 = MCPWM_InitStruct->TimeBase1_PERIOD;

    MCPWMx->PWM_TMR0 = MCPWM_InitStruct->TriggerPoint0;
    MCPWMx->PWM_TMR1 = MCPWM_InitStruct->TriggerPoint1;
    MCPWMx->PWM_TMR2 = MCPWM_InitStruct->TriggerPoint2;
    MCPWMx->PWM_TMR3 = MCPWM_InitStruct->TriggerPoint3;

    MCPWMx->PWM_FLT = (MCPWM_InitStruct->CMP_BKIN_Filter << 8) | MCPWM_InitStruct->GPIO_BKIN_Filter;

    MCPWMx->PWM_IO01 = MCPWM_InitStruct->CH0N_Polarity_INV | (MCPWM_InitStruct->CH0P_Polarity_INV << 1) \
	                     | (MCPWM_InitStruct->Switch_CH0N_CH0P << 6) | (MCPWM_InitStruct->MCPWM_WorkModeCH0 << 7) \
	                     | (MCPWM_InitStruct->CH1N_Polarity_INV << 8) | (MCPWM_InitStruct->CH1P_Polarity_INV << 9)\
	                     | (MCPWM_InitStruct->Switch_CH1N_CH1P << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH1 << 15)\
                       | (MCPWM_InitStruct->CH0P_SCTRLP << 5) | (MCPWM_InitStruct->CH0N_SCTRLN << 4) \
                       | (MCPWM_InitStruct->CH1P_SCTRLP << 13) | (MCPWM_InitStruct->CH1N_SCTRLN << 12) \
	                     | (MCPWM_InitStruct->CH0_PS << 3) | (MCPWM_InitStruct->CH0_NS << 2) \
	                     | (MCPWM_InitStruct->CH1_PS << 11) | (MCPWM_InitStruct->CH1_NS << 10);

    MCPWMx->PWM_IO23 = MCPWM_InitStruct->CH2N_Polarity_INV | (MCPWM_InitStruct->CH2P_Polarity_INV << 1) \
		                  | (MCPWM_InitStruct->Switch_CH2N_CH2P << 6) | (MCPWM_InitStruct->MCPWM_WorkModeCH2 << 7) \
		                  | (MCPWM_InitStruct->CH3N_Polarity_INV << 8) | (MCPWM_InitStruct->CH3P_Polarity_INV << 9) \
		                  | (MCPWM_InitStruct->Switch_CH3N_CH3P << 14) | (MCPWM_InitStruct->MCPWM_WorkModeCH3 << 15)\
                      | (MCPWM_InitStruct->CH2P_SCTRLP << 5) | (MCPWM_InitStruct->CH2N_SCTRLN << 4)\
	                    | (MCPWM_InitStruct->CH2_PS << 3) | (MCPWM_InitStruct->CH2_NS << 2)\
	                    | (MCPWM_InitStruct->CH3_PS << 11) | (MCPWM_InitStruct->CH3_NS << 10);

    MCPWMx->PWM_FAIL012 = MCPWM_InitStruct->FAIL0_Signal_Sel | (MCPWM_InitStruct->FAIL0_Polarity << 2) \
		| (MCPWM_InitStruct->FAIL0_INPUT_EN << 4) | (MCPWM_InitStruct->FAIL1_INPUT_EN << 5) \
		| (MCPWM_InitStruct->FAIL1_Signal_Sel << 1) | (MCPWM_InitStruct->FAIL1_Polarity << 3)\
		| (MCPWM_InitStruct->DebugMode_PWM_out << 7) | (MCPWM_InitStruct->CH0N_default_output << 8) \
		| (MCPWM_InitStruct->CH0P_default_output << 9) | (MCPWM_InitStruct->CH1N_default_output << 10) \
		| (MCPWM_InitStruct->CH1P_default_output << 11) | (MCPWM_InitStruct->CH2N_default_output << 12) \
		| (MCPWM_InitStruct->CH2P_default_output << 13);

    MCPWMx->PWM_FAIL3 = MCPWM_InitStruct->FAIL2_Signal_Sel | (MCPWM_InitStruct->FAIL2_Polarity << 2) \
		| (MCPWM_InitStruct->FAIL2_INPUT_EN << 4) | (MCPWM_InitStruct->FAIL3_INPUT_EN << 5) \
		| (MCPWM_InitStruct->FAIL3_Signal_Sel << 1) | (MCPWM_InitStruct->FAIL3_Polarity << 3) \
		| (MCPWM_InitStruct->DebugMode_PWM_out << 7) | (MCPWM_InitStruct->CH3N_default_output << 8) \
		| (MCPWM_InitStruct->CH3P_default_output << 9);

    MCPWMx->PWM_SDCFG = MCPWM_InitStruct->MCPWM_UpdateT0Interval | (MCPWM_InitStruct->MCPWM_Base0T0_UpdateEN << 4) \
		| (MCPWM_InitStruct->MCPWM_Base0T1_UpdateEN << 5) | (MCPWM_InitStruct->MCPWM_Auto0_ERR_EN << 6) \
		| (MCPWM_InitStruct->MCPWM_UpdateT1Interval) << 8 | (MCPWM_InitStruct->MCPWM_Base1T0_UpdateEN << 12) \
		| (MCPWM_InitStruct->MCPWM_Base1T1_UpdateEN << 13) | (MCPWM_InitStruct->MCPWM_Auto1_ERR_EN << 14);

    MCPWMx->PWM_DTH0 = MCPWM_InitStruct->DeadTimeCH0123N;
    MCPWMx->PWM_DTH1 = MCPWM_InitStruct->DeadTimeCH0123P;

    MCPWMx->PWM_AUEN = MCPWM_InitStruct->AUEN;

    MCPWMx->PWM_EVT0 = MCPWM_InitStruct->TimeBase_TrigEvt0;
    MCPWMx->PWM_EVT1 = MCPWM_InitStruct->TimeBase_TrigEvt1;

    MCPWMx->PWM_CNT0 = MCPWM_InitStruct->TimeBase0Init_CNT;
    MCPWMx->PWM_CNT1 = MCPWM_InitStruct->TimeBase1Init_CNT;

    MCPWMx->PWM_IE0 = MCPWM_InitStruct->CNT0_T0_Update_INT_EN | (MCPWM_InitStruct->CNT0_T1_Update_INT_EN << 1) | (MCPWM_InitStruct->CNT0_Update_TH00_EN << 2) | (MCPWM_InitStruct->CNT0_Update_TH01_EN << 3) | (MCPWM_InitStruct->CNT0_Update_TH10_EN << 4) | (MCPWM_InitStruct->CNT0_Update_TH11_EN << 5) | (MCPWM_InitStruct->CNT0_Update_TH20_EN << 6) | (MCPWM_InitStruct->CNT0_Update_TH21_EN << 7) | (MCPWM_InitStruct->CNT0_Update_TH30_EN << 8) | (MCPWM_InitStruct->CNT0_Update_TH31_EN << 9) | (MCPWM_InitStruct->CNT0_TMR0_Match_INT_EN << 10) | (MCPWM_InitStruct->CNT0_TMR1_Match_INT_EN << 11) | (MCPWM_InitStruct->CNT0_TMR2_Match_INT_EN << 12) | (MCPWM_InitStruct->CNT0_TMR3_Match_INT_EN << 13) | (MCPWM_InitStruct->CNT0_Update_EN << 14);
    MCPWMx->PWM_IE1 = MCPWM_InitStruct->CNT1_T0_Update_INT_EN | (MCPWM_InitStruct->CNT1_T1_Update_INT_EN << 1) | (MCPWM_InitStruct->CNT1_Update_TH30_EN << 8) | (MCPWM_InitStruct->CNT1_Update_TH31_EN << 9) | (MCPWM_InitStruct->CNT1_TMR2_Match_INT_EN << 12) | (MCPWM_InitStruct->CNT1_TMR3_Match_INT_EN << 13) | (MCPWM_InitStruct->CNT1_Update_EN << 14);
		

    MCPWMx->PWM_EIE = (MCPWM_InitStruct->FAIL0_INT_EN << 4) | (MCPWM_InitStruct->FAIL1_INT_EN << 5) | (MCPWM_InitStruct->FAIL2_INT_EN << 6) | (MCPWM_InitStruct->FAIL3_INT_EN << 7);

    MCPWMx->PWM_RE = (MCPWM_InitStruct->TMR0_DMA_RE) | (MCPWM_InitStruct->TMR1_DMA_RE << 1) | (MCPWM_InitStruct->TMR2_DMA_RE << 2) | (MCPWM_InitStruct->TMR3_DMA_RE << 3) | (MCPWM_InitStruct->TR0_T0_DMA_RE << 4) | (MCPWM_InitStruct->TR0_T1_DMA_RE << 5) | (MCPWM_InitStruct->TR1_T0_DMA_RE << 6) | (MCPWM_InitStruct->TR1_T1_DMA_RE << 7);

    MCPWMx->PWM_PP = MCPWM_InitStruct->IO_PPE;

    MCPWMx->PWM_UPDATE = 0xffff; /* write whatever value to trigger update */

    MCPWMx->PWM_IF0 = 0xffff;
    MCPWMx->PWM_IF1 = 0xffff;
    MCPWMx->PWM_EIF = 0xffff;
	
		//ͬʱ������ʱ��CNT0��CNT1
		MCPWMx->PWM_TCLK |= ((MCPWM_InitStruct->MCPWM_Cnt0_EN << 6) | (MCPWM_InitStruct->MCPWM_Cnt1_EN << 7));

    MCPWMx->PWM_PRT = 0x0000CAFE; /* write any value other than 0xDEAD to enable write protection */
}

/**
 *@brief @b ��������:   void MCPWM_SwapFunction(void)
 *@brief @b ��������:   MCPWMͨ������Ԥ��ʱ����
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       оƬ�ڲ���Ԥ��ʱʹ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
            MCPWM_SwapFunction();
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0       <td>HMG         <td>����
 * </table>
 */
void MCPWM_SwapFunction(void)
{
    MCPWM_PRT = 0x0000DEAD; /* ���MCPWM �Ĵ���д����*/
    MCPWM_SWAP = 0x67;      /* ����оƬ�ڲ�MCPWMͨ��ת��˳��*/
    MCPWM_PRT = 0x0000CAFE; /* ����MCPWM �Ĵ���д����*/
}

/**
 *@brief @b ��������:   void MCPWM_Update(strPWM_DutyCycleDef *Duty)
 *@brief @b ��������:   MCPWM���±Ƚ�����ֵ
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       оƬ�ڲ���Ԥ��ʱʹ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
            MCPWM_Update(&strPWM_DutyCycle);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0       <td>HMG         <td>����
 * </table>
 */
void MCPWM_Update(strPWM_DutyCycleDef *Duty)
{
    MCPWM_TH00 = Duty->th00;
	  MCPWM_TH01 = Duty->th01;
	
	  MCPWM_TH10 = Duty->th10;
	  MCPWM_TH11 = Duty->th11;
	
	  MCPWM_TH20 = Duty->th20;
	  MCPWM_TH21 = Duty->th21;
	
	  MCPWM_TH30 = Duty->th30;
	  MCPWM_TH31 = Duty->th31;
}

/**
 *@brief @b ��������:   u16 MCPWM_ReadIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag)
 *@brief @b ��������:   ��ȡMCPWM�жϱ�־
 *@see���������ݣ�      ��
 *@param���������      MCPWMx: MCPWM0, CNT_Num: CNT0/CNT1, INT_flag �ж�����
 * <table>             <tr><th>CNT0_MCPWM_T0_IRQ_IF        <td>BIT0     <td>����������ֵ�ص�MCPWM_TH�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_T1_IRQ_IF        <td>BIT1     <td>����������ֵ�ص�0�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_TH00_IRQ_IF      <td>BIT2     <td>����������ֵ�ص�MCPWM_TH00�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH01_IRQ_IF      <td>BIT3     <td>����������ֵ�ص�MCPWM_TH01�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH10_IRQ_IF      <td>BIT4     <td>����������ֵ�ص�MCPWM_TH10�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH11_IRQ_IF      <td>BIT5     <td>����������ֵ�ص�MCPWM_TH11�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH20_IRQ_IF      <td>BIT6     <td>����������ֵ�ص�MCPWM_TH20�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH21_IRQ_IF      <td>BIT7     <td>����������ֵ�ص�MCPWM_TH21�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH30_IRQ_IF      <td>BIT8     <td>����������ֵ�ص�MCPWM_TH30�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TH31_IRQ_IF      <td>BIT9     <td>����������ֵ�ص�MCPWM_TH31�жϱ�־λ
 *                     <tr><th>CNT0_MCPWM_TMR0_IRQ_IF      <td>BIT10    <td>����������ֵ�ص�MCPWM_TMR0�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_TMR1_IRQ_IF      <td>BIT11    <td>����������ֵ�ص�MCPWM_TMR1�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_TMR2_IRQ_IF      <td>BIT12    <td>����������ֵ�ص�MCPWM_TMR0�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_TMR3_IRQ_IF      <td>BIT13    <td>����������ֵ�ص�MCPWM_TMR1�жϱ�־λ 
 *                     <tr><th>CNT0_MCPWM_SHADE_IRQ_IF     <td>BIT14    <td>MCPWM_TH/MCPWM_TH00-MCPWM_TH31/MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� 
 *                     <tr><th>CNT1_MCPWM_T0_IRQ_IF        <td>BIT0     <td>����������ֵ�ص�MCPWM_TH�жϱ�־λ
 *                     <tr><th>CNT1_MCPWM_T1_IRQ_IF        <td>BIT1     <td>����������ֵ�ص�0�ж�ʹ��
 *                     <tr><th>CNT1_MCPWM_TH30_IRQ_IF      <td>BIT8     <td>����������ֵ�ص�MCPWM_TH30�жϱ�־λ
 *                     <tr><th>CNT1_MCPWM_TH31_IRQ_IF      <td>BIT9     <td>����������ֵ�ص�MCPWM_TH31�жϱ�־λ
 *                     <tr><th>CNT1_MCPWM_TMR2_IRQ_IF      <td>BIT12    <td>����������ֵ�ص�MCPWM_TMR0�жϱ�־λ
 *                     <tr><th>CNT1_MCPWM_TMR3_IRQ_IF      <td>BIT13    <td>����������ֵ�ص�MCPWM_TMR1�жϱ�־λ
 *                     <tr><th>CNT1_MCPWM_SHADE_IRQ_IF     <td>BIT14    <td>MCPWM_TH/MCPWM_TH00-MCPWM_TH31/MCPWM_TR0-MCPWM_TR3�ȼĴ������µ�MCPWMʵ������ϵͳ�ж�ʹ�� 
 *                     <tr><th>CNT0_MCPWM_FAIL0_IRQ_IF     <td>BIT19    <td>MCPWM_FAIL0�ж�ʹ��
 *                     <tr><th>CNT0_MCPWM_FAIL1_IRQ_IF     <td>BIT20    <td>MCPWM_FAIL1�ж�ʹ��
 *                     <tr><th>CNT1_MCPWM_FAIL2_IRQ_IF     <td>BIT21    <td>MCPWM_FAIL2�ж�ʹ��
 *                     <tr><th>CNT1_MCPWM_FAIL3_IRQ_IF     <td>BIT22    <td>MCPWM_FAIL3�ж�ʹ��
 * </table>
 *@param���������   ��
 *@return�� �� ֵ��  ����Ӧ��־λ�Ƿ�Ϊ1��1λ��λ��0Ϊδ��λ
 *@note����˵����    ��
 *@warning           ֻ�ж�Ӧ�ж�ʹ�ܺ󣬸�Ϊ���ܶ�ȡ�������Ӧ�ж�δʹ�ܣ���ȡ���һֱΪ0
 *@par ʾ�����룺
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM0,CNT0,CNT0_MCPWM_T0_IRQ_IF));//��ȡMCPWM�ļ���������ֵ�ص�MCPWM_TH�жϱ�־
		   {
		   }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
u16 MCPWM_ReadIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag)
{
	  u8 MCPWMIRQFlag = 0;
	 if(INT_flag <= BIT14)
	 {
		   if(CNTx)
			 {
					 if(MCPWMx->PWM_IF1 & INT_flag)
						{
								MCPWMIRQFlag = 1;
						}
						else
						{
								MCPWMIRQFlag = 0;
						}
			}
			else
			{
					if(MCPWMx->PWM_IF0 & INT_flag)
					{
							MCPWMIRQFlag = 1;
					}
					else
					{
							MCPWMIRQFlag = 0;
					}
			}
	 }
	 else
	 {

				if(MCPWMx->PWM_EIF & (INT_flag >> 15))
				{
						MCPWMIRQFlag = 1;
				}
				else
				{
						MCPWMIRQFlag = 0;
				}
	 }
    return MCPWMIRQFlag;
}

/**
 *@brief @b ��������:   void MCPWM_ClearIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag)
 *@brief @b ��������:   ���MCPWM�жϱ�־
 *@see���������ݣ�      ��
 *@param���������MCPWMx: MCPWM0, CNT_Num: CNT0/CNT1, INT_flag �ж�����
 *@param���������   ��
 *@return�� �� ֵ��  ��
 *@note����˵����    ��
 *@warning          ��
 *@par ʾ�����룺
 *@code
		   if(MCPWM_GetIRQFlag(MCPWM0,CNT0,CNT0_MCPWM_T0_IRQ_IF))//��ȡMCPWM�ļ���������ֵ�ص�MCPWM_TH�жϱ�־
		   {
            MCPWM_ClearIRQFlag(MCPWM0,CNT0,CNT0_MCPWM_T0_IRQ_IF);//���MCPWM�ļ���������ֵ�ص�MCPWM_TH�жϱ�־
		   }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
void MCPWM_ClearIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, uint32_t INT_flag)
{
		if(INT_flag <= BIT14)
	  {
		   if(CNTx)
			 {
				   MCPWMx->PWM_IF1 |= INT_flag;
			 }
			 else
			 {
           MCPWMx->PWM_IF0 |= INT_flag;
			 }
	  }
	  else
	  {
				MCPWMx->PWM_EIF |= (INT_flag >> 15);
	  }
}
