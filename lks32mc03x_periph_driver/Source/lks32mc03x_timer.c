/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_tim.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� ��ʱ�������������� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ        <td>����
 * </table>
 */
#include "lks32mc03x_timer.h"

/**
 *@brief @b ��������:   void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *this)
 *@brief @b ��������:   ��ʱ����ʼ������
 *@see���������ݣ�      SYS_ModuleClockCmd()
 *@param���������      TIMERx��TIMER0/TIMER1/TIMER2/TIMER3 \n
                        TIM_TimerInitTypeDef *this
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
          TIM_TimerInitTypeDef TIM_InitStruct;
          TIM_TimerStrutInit(&TIM_InitStruct);        // Timer�ṹ�������ʼ�� 
          TIM_InitStruct.CLK_DIV = TIM_Clk_Div1;      // ����Timerģ�����ݷ�Ƶϵ�� 
          TIM_InitStruct.CH0_MODE = TIMER_OPMode_CMP; // ����Timer CH0Ϊ�Ƚ�ģʽ
          TIM_InitStruct.CH0_POL = 0;                 // ����������ʱ���Ƚ�ģʽ������Կ���
          TIM_InitStruct.CH1_MODE = TIMER_OPMode_CMP; // ����Timer CH1Ϊ�Ƚ�ģʽ
          TIM_InitStruct.CH1_POL = 0;                 // ����������ʱ���Ƚ�ģʽ������Կ��� 
          TIM_InitStruct.TH = 24000;                  // ���ü���������ģֵ 0.5ms 2KHZ
          TIM_InitStruct.TIM_CMP0 = 18000;            // ���ñȽ�ģʽ��CH0�Ƚ�ֵ 
          TIM_InitStruct.TIM_CMP1 = 18000;            // ���ñȽ�ģʽ��CH1�Ƚ�ֵ 
          TIM_InitStruct.IE = TIM_IRQ_IE_CH1;         // ����Timerģ��CH1�Ƚ��ж� 
          TIM_TimerInit(TIMER1, &TIM_InitStruct);
		  TIM_TimerCmd(TIMER1,ENABLE);                // ʹ��Timer1ʱ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0       <td>YangZJ          <td>����
 * </table>
 */
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *this)
{
    if(TIMERx == TIMER0)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER0,ENABLE);     //��Timerʱ��
    }
    if(TIMERx == TIMER1)
    {
        SYS_ModuleClockCmd(SYS_Module_TIMER1,ENABLE);     //��Timerʱ��
    }
		
		
    TIMERx -> CFG  = (this->CAP1_CLR_EN   << 27) |
                     (this->CAP0_CLR_EN   << 26) | (this->ETON          << 24) |
                     (this->CLK_DIV       << 20) | (this->CLK_SRC       << 16) |
                     (this->SRC1          << 12) | (this->CH1_POL       << 11) |
                     (this->CH1_MODE      << 10) | (this->CH1_FE_CAP_EN <<  9) |
                     (this->CH1_RE_CAP_EN <<  8) | (this->SRC0          <<  4) |
                     (this->CH0_POL       <<  3) | (this->CH0_MODE      <<  2) |
                     (this->CH0_FE_CAP_EN <<  1) | (this->CH0_RE_CAP_EN);
    TIMERx -> TH    = this->TH;
    TIMERx -> CNT   = this->CNT;
    TIMERx -> CMPT0 = this->TIM_CMP0;
    TIMERx -> CMPT1 = this->TIM_CMP1;
    TIMERx -> EVT   = this->EVT_SRC;
    TIMERx -> FLT   = this->FLT;
    TIMERx -> IE    = this->IE;
    TIMERx -> IF    = 0x7;
		TIM_TimerCmd(TIMERx,this->EN);
}
/**
 *@brief @b ��������:   void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
 *@brief @b ��������:   ��ʱ��ʱ��ʹ�ܺ���
 *@see���������ݣ�      FuncState
 *@param���������      TIM_TimerTypeDef *TIMERx , FuncState state
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			    TIM_TimerCmd(TIMER1,ENABLE); // ʹ��Timer1ʱ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version     <th>Author       <th>Description
 * <tr><td>2022��12��5��  <td>1.0       <td>HuangMG          <td>����
 * </table>
 */
void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state)
{
    if (state != DISABLE)
    {
         TIMERx -> CFG |= BIT31;
    }
    else
    {   
         TIMERx -> CFG &= ~BIT31;
    }
}


/**
 *@brief @b ��������:   void TIM_TimerStrutInit(TIM_TimerInitTypeDef *this)
 *@brief @b ��������:   ��ʱ���ṹ���ʼ��
 *@see���������ݣ�      ��
 *@param���������      TIM_TimerInitTypeDef *this
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
			    TIM_TimerInitTypeDef TIM_InitStruct;
          TIM_TimerStrutInit(&TIM_InitStruct);  // Timer�ṹ���ʼ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0       <td>YangZJ          <td>����
 * </table>
 */
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *this)
{
    this -> CAP1_CLR_EN   = DISABLE;          // ������ CAP1 �����¼�ʱ������ Timer ������������Ч
    this -> CAP0_CLR_EN   = DISABLE;          // ������ CAP0 �����¼�ʱ������ Timer ������������Ч
    this -> ETON          = DISABLE;          // Timer ����������ʹ������ 0: �Զ����� 1: �ȴ��ⲿ�¼���������
    this -> CLK_DIV       = 0;                // Timer ��������Ƶ
    this -> CLK_SRC       = TIM_Clk_SRC_MCLK; // Timer ʱ��Դ
    this -> TH            = 0;                // Timer �������������ޡ��������� 0 ������ TH ֵ���ٴλ� 0 ��ʼ����
            
    this -> SRC1          = TIM_SRC1_1;       // Timer ͨ�� 1 ����ģʽ�ź���Դ
    this -> CH1_POL       = 1;                // Timer ͨ�� 1 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ
    this -> CH1_MODE      = 0;                // Timer ͨ�� 1 ����ģʽѡ��0���Ƚ�ģʽ��1������ģʽ
    this -> CH1_FE_CAP_EN = DISABLE;          // Timer ͨ�� 1 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    this -> CH1_RE_CAP_EN = DISABLE;          // Timer ͨ�� 1 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    this -> TIM_CMP1      = 0;            // Timer ͨ�� 1 �Ƚ�����
            
    this -> SRC0          = TIM_SRC1_0;       // Timer ͨ�� 0 ����ģʽ�ź���Դ
    this -> CH0_POL       = 1;                // Timer ͨ�� 0 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ
    this -> CH0_MODE      = 0;                // Timer ͨ�� 0 ����ģʽѡ��0���Ƚ�ģʽ��1������ģʽ
    this -> CH0_FE_CAP_EN = DISABLE;          // Timer ͨ�� 0 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    this -> CH0_RE_CAP_EN = DISABLE;          // Timer ͨ�� 0 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    this -> TIM_CMP0      = 0;            // Timer ͨ�� 0 �Ƚ�����
            
    this -> CNT           = 0;                // Timer ��������ǰ����ֵ��д��������д���µļ���ֵ��
    this -> EVT_SRC       = 0;                // Timer ����ʹ�ܿ�ʼ���ⲿ�¼�ѡ��
    this -> FLT           = 0;                // ͨ�� 0/1 �ź��˲����ѡ��0-255
    this -> IE            = 0;                // Timer �ж�ʧ��
		this -> EN = DISABLE;                     // Timer �ж�ʧ��
}

/**
 *@brief @b ��������:   uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
 *@brief @b ��������:   ��ȡTIM�жϱ�־
 *@see���������ݣ�      ��
 *@param���������      TIMERx��TIMER0/TIMER1 \n
                        timer_if��
 * <table>              <tr><th>TIM_IRQ_IF_ZC   <td>TIMER��������0(����������)�жϱ�־
                        <tr><th>TIM_IRQ_IF_CH1  <td>Timer1�Ƚ�OR�����¼��жϱ�־
                        <tr><th>TIM_IRQ_IF_CH0  <td>Timer0�Ƚ�OR�����¼��жϱ�־
 * </table> 
 *@param���������      ��
 *@return�� �� ֵ��     0��1����Ӧ�жϱ�־��λ����1��δ��λ����0
 *@note����˵����       ��
 *@warning             ֻ�ж�Ӧ�ж�ʹ�ܺ󣬸�Ϊ���ܶ�ȡ�������Ӧ�ж�δʹ�ܣ���ȡ���һֱΪ0
 *@par ʾ�����룺
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIM_IRQ_IF_CH0)) //�ж�UTimer0��CH0�Ƿ����Ƚ��ж�
                {
                }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022��04��11�� <td>1.0     <td>HuangMG        <td>�޸�
 * </table>
 */
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if)
{
	if(TIMERx == TIMER0)
    {
			if((UTIMER0_IF & timer_if & UTIMER0_IE) == 0)
			{
			  return 0;
			}else{
				return 1;
			}    
    }
    if(TIMERx == TIMER1)
    {
      if((UTIMER1_IF & timer_if & UTIMER1_IE) == 0)
			{
			  return 0;
			}else{
				return 1;
			}
    }
     return 0;
}

/**
 *@brief @b ��������:   void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag)
 *@brief @b ��������:   ���TIM�жϱ�־
 *@see���������ݣ�      ��
 *@param���������      TIMERx��TIMER0/TIMER1 \n
                        timer_if��
 * <table>              <tr><th>TIM_IRQ_IF_ZC   <td>TIMER��������0(����������)�жϱ�־
                        <tr><th>TIM_IRQ_IF_CH1  <td>Timer1�Ƚ�OR�����¼��жϱ�־
                        <tr><th>TIM_IRQ_IF_CH0  <td>Timer0�Ƚ�OR�����¼��жϱ�־
 * </table> 
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			    if(TIM_GetIRQFlag(TIMER0,TIM_IRQ_IF_CH0)) //�ж�UTimer0��CH0�Ƿ����Ƚ��ж�
          {
              TIM_ClearIRQFlag(TIMER0,TIM_IRQ_IF_CH0); //���UTimer0ͨ��0�Ƚ��жϱ�־λ
          }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022��04��13�� <td>1.0     <td>HuangMG        <td>�޸�
 * </table>
 */
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag)
{
		if(TIMERx == TIMER0)
    {
        UTIMER0_IF = tempFlag;
    }
    if(TIMERx == TIMER1)
    {
        UTIMER1_IF = tempFlag;
    }
}

/**
 *@brief @b ��������:   uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
 *@brief @b ��������:   ��ȡTimer����ֵ
 *@see���������ݣ�      ��
 *@param���������      TIMERx��TIMER0/TIMER1
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
            uint32_t TIMER0_Value = 0;
            TIMER0_Value = TIM_Timer_GetCount(TIMER0); //��ȡ��ʱ��0����ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022��04��11�� <td>1.0      <td>HuangMG          <td>�޸�
 * </table>
 */
uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx)
{
   return TIMERx->CNT;
}

/**
 *@brief @b ��������:   uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b ��������:   ��ȡ��ʱ��ͨ��0����ֵ
 *@see���������ݣ�       ��
 *@param���������      TIM_TIMERx��TIMER0/TIMER1
 *@param���������      ��
 *@return�� �� ֵ��     ��ʱ��ͨ��0����ֵ
 *@note����˵����       ����ʱ�����������¼�ʱ��������ʱ�̵�cntֵ�洢���üĴ�����
 *@warning              ��
 *@par ʾ�����룺
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT0(TIMER0); //��ȡ��ʱ��0����ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022��04��11�� <td>1.0      <td>HuangMG          <td>�޸�
 * </table>
 */
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx)
{
   return TIM_TIMERx->CMPT0;
}

/**
 *@brief @b ��������:   uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
 *@brief @b ��������:   ��ȡ��ʱ��ͨ��1����ֵ
 *@see���������ݣ�      ��
 *@param���������      TIM_TIMERx��TIMER0/TIMER1
 *@param���������      ��
 *@return�� �� ֵ��     ��ʱ��ͨ��1����ֵ
 *@note����˵����       ����ʱ�����������¼�ʱ��������ʱ�̵�cntֵ�洢���üĴ�����
 *@warning              ��
 *@par ʾ�����룺
 *@code
                    uint32_t TIMER0_CAPValue = 0;
                    TIMER0_CAPValue = TIM_Timer_GetCMPT1(TIMER0); //��ȡ��ʱ��0����ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
  * <tr><td>2022��04��11�� <td>1.0      <td>HuangMG          <td>����
 * </table>
 */
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx)
{
   return TIM_TIMERx->CMPT1;  
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
