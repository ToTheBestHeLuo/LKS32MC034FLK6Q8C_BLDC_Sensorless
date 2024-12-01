/**
 * @file
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_adc.c \n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� ADC������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
#include "lks32mc03x_adc.h"

/**
 *@brief @b ��������:   void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b ��������:   ADC��ʼ������
 *@see���������ݣ�      SYS_AnalogModuleClockCmd()
 *@param���������      ADCx��ADC, ADC_InitTypeDef *ADC_InitTypeDef
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
            ADC_InitTypeDef ADC_InitStructure;
            ADC_StructInit(&ADC_InitStructure);                            // ADC��ʼ���ṹ��
            ADC_InitStructure.Align = ADC_LEFT_ALIGN;                      // ADC������������
            ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;                 // ����ADCת��ģʽΪ1��ʽ���� 
            ADC_InitStructure.FirSeg_Ch = ADC_2_TIMES_SAMPLE;              // ��һ�ι�����2��ͨ�� 
            ADC_InitStructure.SecSeg_Ch = 0;                               // �ڶ��ι�����0��ͨ�� 
            ADC_InitStructure.ThrSeg_Ch = 0;                               // �����ι�����0��ͨ�� 
            ADC_InitStructure.FouSeg_Ch = 0;                               // ���Ķι�����0��ͨ�� 
            ADC_InitStructure.Trigger_Cnt = 0;                             // ���δ���ģʽ�´���һ�β�������Ҫ���¼���:0~15 0��ʾ��Ҫһ�δ�����15��ʾ��Ҫ16��
            ADC_InitStructure.ADC_RANGE = ADC_RANGE_3V6;                   // ADC����ѡ��  
            ADC_InitStructure.Trigger_En = ADC_HARDWARE_T0_TRG;            // ����T0��T1Ӳ�������¼� 
            ADC_InitStructure.SEL_En = ADC_UTIMER_SEL;                     // MCPWM����ADC���� 
            ADC_InitStructure.ADC_SAMP_CLK = 20;                           // ���ò���ʱ��Ϊ20��ADCʱ������ ��Χ4--35
            ADC_InitStructure.IE = ADC_EOS0_IRQ_EN ;                       // ������һ���ж� 
            // ADCģ�⿴�Ź�           
            ADC_InitStructure.ADC_GEN_En  = DISABLE ;                      // ���Ź�����ֹ 
            ADC_InitStructure.ADC_GEN_HTH = 0;                             // ADCģ�⿴�Ź�����ֵ 
            ADC_InitStructure.ADC_GEN_LTH = 0;                             // ADCģ�⿴�Ź�����ֵ 
            ADC_InitStructure.REFOUT_EN = DISABLE;                         // ADC REF�����ʹ��
            ADC_Init(ADC, &ADC_InitStructure);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HungMG        <td>����
 * </table>
 */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{

    uint16_t t_reg;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC, ENABLE); // ADCģ��ʹ��

    ADCx->IE = ADC_InitStruct->IE;

    t_reg = (ADC_InitStruct->Align << 10) |
            (ADC_InitStruct->Trigger_En) |
            (ADC_InitStruct->SEL_En << 12) |
            (ADC_InitStruct->FSM_RESET << 11) |
            (ADC_InitStruct->Trigger_Cnt << 4) |
            (ADC_InitStruct->Trigger_Mode << 8);
    ADCx->CFG = t_reg;

    ADCx->CHNT = ADC_InitStruct->FirSeg_Ch |
                 (ADC_InitStruct->SecSeg_Ch << 4) |
                 (ADC_InitStruct->ThrSeg_Ch << 8) |
                 (ADC_InitStruct->FouSeg_Ch << 12);

    ADC_LTH = ADC_InitStruct->ADC_GEN_LTH;

    ADC_HTH = ADC_InitStruct->ADC_GEN_HTH;

    ADC_GEN = ADC_InitStruct->ADC_GEN_En;

    SYS_WR_PROTECT = 0x7a83; // ���ϵͳ�Ĵ���д���� 

    if (ADC_InitStruct->ADC_SAMP_CLK > 4)
    {
        t_reg = ADC_InitStruct->ADC_SAMP_CLK - 4;
    }
    else
    {
        t_reg = 0;
    }

    if (ADC_InitStruct->ADC_RANGE & 0x01) //2.4V����
    {
        SYS_AFE_REG0 |= 0x01 << 6;        //ADC����ѡ��
        ADC_AMC = Read_Trim(0x000001AC);  //ADC_AMC1У��ֵ��1������
        ADC_DC = Read_Trim(0x000001A8);   //ADC_DC1У��ֵ ��1������
    } 
    else 
    {                                     //3.6V����
        SYS_AFE_REG0 &= ~(0x01 << 6);     //ADC����ѡ��
        ADC_AMC = Read_Trim(0x000001A4);  //ADC_AMC0У��ֵ��2/3������
        ADC_DC = Read_Trim(0x000001A0);   //ADC_DC0У��ֵ ��2/3������
    }
    SYS_AFE_REG2 = (t_reg << 8);          //����ADC����ʱ��
    SYS_AFE_REG1 |= ADC_InitStruct->REFOUT_EN << 6;

    SYS_WR_PROTECT = 0;                   // ����ϵͳ�Ĵ���д���� 
}
/**
 *@brief @b ��������:   void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 *@brief @b ��������:   ADC�ṹ���ʼ��
 *@see���������ݣ�      ��
 *@param���������      ADC_InitTypeDef *ADC_InitStruct
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
		   ADC_InitTypeDef ADC_InitStructure;
		   ADC_StructInit(&ADC_InitStructure); //��ʼ���ṹ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG     <td>����
 * </table>
 */

void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->ADC_SAMP_CLK = 0;
    ADC_InitStruct->IE = 0;
    ADC_InitStruct->SEL_En = 0;
    ADC_InitStruct->FSM_RESET = 0;
    ADC_InitStruct->Align = 0;
    ADC_InitStruct->Trigger_Mode = 0;
    ADC_InitStruct->Trigger_Cnt = 0;
    ADC_InitStruct->Trigger_En = 0;

    ADC_InitStruct->FirSeg_Ch = 0;
    ADC_InitStruct->SecSeg_Ch = 0;
    ADC_InitStruct->ThrSeg_Ch = 0;
    ADC_InitStruct->FouSeg_Ch = 0;

    ADC_InitStruct->ADC_GEN_En = 0;
    ADC_InitStruct->ADC_GEN_HTH = 0;
    ADC_InitStruct->ADC_GEN_LTH = 0;
    ADC_InitStruct->REFOUT_EN = 0;

    ADC_InitStruct->ADC_RANGE = 0;
}
/**
 *@brief @b ��������:   void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b ��������:   ADC�жϱ�־λ����
 *@see���������ݣ�      ��
 *@param���������
 * <table>              <tr><td>ADCx��                   <td> ADC
 *                      <tr><td>INT_flag:                <td> ADC�жϱ�־
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>����ֵ�жϱ�־λ \n
 * 						<tr><th>ADC_CONFLICT_IRQ_IF      <td>Ӳ��������ͻ��־ \n
 * 						<tr><th>ADC_HERR_IRQ_IF          <td>���������ͻ��־ \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>���Ķ�ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>������ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>�ڶ���ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>��һ��ɨ������жϱ�־ \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADCȫ���жϱ�־λ���������ڳ�ʼ�� \n
 * </table>
 *@param���������   ��
 *@return�� �� ֵ��  ��
 *@note����˵����    д1����
 *@warning          ��
 *@par ʾ�����룺
 *@code
            if(ADC_GetIRQFlag(ADC,ADC_EOS0_IRQ_IF))           // ��һ�β�������ж�
            {
                ADC_ClearIRQFlag(ADC,ADC_EOS0_IRQ_IF);          // �����һ�β�������жϱ�־λ
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
    ADCx->IF = INT_flag;
}

/**
 *@brief @b ��������:   uint16_t ADC_GetIRQFlag(ADC_TypeDef* ADCx, uint16_t INT_flag)
 *@brief @b ��������:   ��ȡADC�жϱ�־
 *@see���������ݣ�      ��
 *@param���������
 * <table>              <tr><td>ADCx��                   <td> ADC
 *                      <tr><td>INT_flag:                <td> ADC�жϱ�־
 * 						<tr><th>ADC_DAT0_OV_IRQ_IF       <td>����ֵ�жϱ�־λ \n
 * 						<tr><th>ADC_CONFLICT_IRQ_IF      <td>Ӳ��������ͻ��־ \n
 * 						<tr><th>ADC_HERR_IRQ_IF          <td>���������ͻ��־ \n
 * 						<tr><th>ADC_EOS3_IRQ_IF          <td>���Ķ�ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS2_IRQ_IF          <td>������ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS1_IRQ_IF          <td>�ڶ���ɨ������жϱ�־ \n
 * 						<tr><th>ADC_EOS0_IRQ_IF          <td>��һ��ɨ������жϱ�־ \n
 * 						<tr><th>ADC_ALL_IRQ_IF           <td>ADCȫ���жϱ�־λ���������ڳ�ʼ�� \n
 * </table>
 *@param���������   ��
 *@return�� �� ֵ��  ����Ӧ��־λ�Ƿ�Ϊ1��1Ϊ��λ��0Ϊδ��λ
 *@note����˵����    ��
 *@warning          ֻ�ж�Ӧ�ж�ʹ�ܺ󣬸�Ϊ���ܶ�ȡ�������Ӧ�ж�δʹ�ܣ���ȡ���һֱΪ0
 *@par ʾ�����룺
 *@code
		    if(ADC_GetIRQFlag(ADC,ADC_EOS0_IRQ_IF))           // ��һ�β�������ж�
            {
                ADC_ClearIRQFlag(ADC,ADC_EOS0_IRQ_IF);          // �����һ�β�������жϱ�־λ
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, uint16_t INT_flag)
{
    u8 ADCIRQFlag = 0;
    if (ADCx->IF & INT_flag)
    {
        ADCIRQFlag = 1;
    }
    else
    {
        ADCIRQFlag = 0;
    }
    return ADCIRQFlag;
}
/**
 *@brief @b ��������:   void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3)
 *@brief @b ��������:   ADC����ͨ������
 *@see���������ݣ�      CHNx
 *@param���������
					   ADCx��03ϵ�й̶�ѡ��ADC;
 *                     CHNumΪö�����ͣ���Ӧ0-3��
 *                     Ch_n0,Ch_n1,Ch_n2,Ch_n3��ADC_CHANNEL_0 ~ ADC_CHANNEL_13;
 *@param���������     ��
 *@return�� �� ֵ��    ��
 *@note����˵����      ��
 *@warning            ��
 *@par ʾ�����룺
 *@code
            ADC_ChannelConfig(ADC,CHN0, ADC_CHANNEL_5 ,ADC_CHANNEL_5, ADC_CHANNEL_5 ,ADC_CHANNEL_5);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3)
{
    if (CHNum == CHN0)
    {
        ADCx->CHN0 = Ch_n0 | Ch_n1 << 4 | Ch_n2 << 8 | Ch_n3 << 12;
    }
    else if (CHNum == CHN1)
    {
        ADCx->CHN1 = Ch_n0 | Ch_n1 << 4 | Ch_n2 << 8 | Ch_n3 << 12;
    }
    else if (CHNum == CHN2)
    {
        ADCx->CHN2 = Ch_n0 | Ch_n1 << 4;
    }
}
/**
 *@brief @b ��������:   s16 ADC_GetConversionValue(DATx DATNum)
 *@brief @b ��������:   ��ADC����ֵ
 *@see���������ݣ�      DATx
 *@param���������      DATx����ȡ��x�β������ֵ
 *@param���������      ��
 *@return�� �� ֵ��     ��Ӧ��x�β������ֵ
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code
		   s16 ADC_samp0 = 0��
		   ADC_samp0 = ADC_GetConversionValue(DAT0);//��ȡADC��0�β������
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
s16 ADC_GetConversionValue(DATx DATNum)
{
    if (DATNum == DAT0)
    {
        return ADC_DAT0;
    }
    else if (DATNum == DAT1)
    {
        return ADC_DAT1;
    }
    else if (DATNum == DAT2)
    {
        return ADC_DAT2;
    }
    else if (DATNum == DAT3)
    {
        return ADC_DAT3;
    }
    else if (DATNum == DAT4)
    {
        return ADC_DAT4;
    }
    else if (DATNum == DAT5)
    {
        return ADC_DAT5;
    }
    else if (DATNum == DAT6)
    {
        return ADC_DAT6;
    }
    else if (DATNum == DAT7)
    {
        return ADC_DAT7;
    }
    else if (DATNum == DAT8)
    {
        return ADC_DAT8;
    }
    else if (DATNum == DAT9)
    {
        return ADC_DAT9;
    }
    return 0;
}
/**
 *@brief @b ��������:   void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state)
 *@brief @b ��������:   ADC�����������ʹ��
 *@see���������ݣ�      FuncState
 *@param���������      ADCx��08ϵ�й̶�ѡ��ADC0
 *                     state��ENABLE������DISABLE������
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ADC0_SWTд0x5AA5������һ�Σ���ɺ��Զ����㣬�ȴ��´��������
 *@warning             ��
 *@par ʾ�����룺
 *@code
		  ADC_SoftTrgEN(ADC0��ENABLE);//�������һ��ADC����
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>Zhu Jie      <td>����
 * </table>
 */
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state)
{
    if (state == ENABLE)
    {
        ADC->SWT = 0x5AA5;
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
