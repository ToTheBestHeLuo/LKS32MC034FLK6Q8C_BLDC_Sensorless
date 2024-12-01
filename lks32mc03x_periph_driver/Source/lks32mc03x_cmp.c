 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_cmp.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� cmp������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09��  <td>1.0    <td>YangZJ      <td>����
 * </table>
 */
 #include "lks32mc03x_cmp.h"

/**
 *@brief @b ��������:   CMP_Init(CMP_InitTypeDef* this)
 *@brief @b ��������:   CMP��ʼ��
 *@see�����ú�����      SYS_AnalogModuleClockCmd()
 *@param���������      CMP_InitTypeDef
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code   
    CMP_InitTypeDef CMP_InitStruct;
    CMP_StructInit(&CMP_InitStruct);
    CMP_InitStruct.CLK10_EN             = DISABLE         ;   // �Ƚ��� 1/0 �˲�ʱ��ʹ��
    CMP_InitStruct.FIL_CLK10_DIV16      = 0               ;   // �Ƚ��� 1/0 �˲�ϵ��       0-0xF
    CMP_InitStruct.FIL_CLK10_DIV2       = 0               ;   // �Ƚ��� 1/0 �˲���λϵ��   0-0x7   ���շ�Ƶϵ��Ϊ (DIV16+1)<<DIV2
    CMP_InitStruct.CMP_FT               = DISABLE         ;   // �Ƚ������ٱȽ�ʹ��
    CMP_InitStruct.CMP_HYS              = 0               ;   // �Ƚ����ز�ѡ��            0���ز�20mV 1���ز�0mV
    
    CMP_InitStruct.CMP1_SELP            = CMP_SELP_IP0    ;   // �Ƚ��� 1 �ź�����ѡ�� �� CMP1_SELP_CMP1_IP0 �Ƚ�������
    CMP_InitStruct.CMP1_SELN            = CMP_SELN_IN     ;   // �Ƚ��� 1 �źŸ���ѡ��
    CMP_InitStruct.CMP1_POL             = 0               ;   // �Ƚ��� 1 ����ѡ��     0���ߵ�ƽ��Ч 1���͵�ƽ��Ч ֻӰ��Ƚ����ж�
    CMP_InitStruct.CMP1_IE              = DISABLE         ;   // �Ƚ��� 1 �ж�ʹ��
    CMP_InitStruct.CMP1_RE              = DISABLE         ;   // �Ƚ��� 1 DMA ����ʹ��
    CMP_InitStruct.CMP1_IRQ_TRIG        = DISABLE         ;   // �Ƚ��� 1 ���ش���ʹ��
    CMP_InitStruct.CMP1_IN_EN           = DISABLE         ;   // �Ƚ��� 1 �ź�����ʹ�� Ӱ��Ƚ�������ģ���źţ�ģ�ⲿ�ֲ���Ӱ��
    CMP_InitStruct.CMP1_CHN3P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 1 ����
    CMP_InitStruct.CMP1_CHN2P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 1 ����
    CMP_InitStruct.CMP1_CHN1P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 1 ����
    CMP_InitStruct.CMP1_CHN0P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 1 ����
    CMP_InitStruct.CMP1_W_PWM_POL       = DISABLE         ;   // �Ƚ��� 1 ���� PWM �źż���ѡ��  0:�ߵ�ƽ��Ч��1:��
    CMP_InitStruct.CMP0_SELP            = CMP_SELP_IP0    ;   // �Ƚ��� 0 �ź�����ѡ��
    CMP_InitStruct.CMP0_SELN            = CMP_SELN_IN     ;   // �Ƚ��� 0 �źŸ���ѡ��
    CMP_InitStruct.CMP0_POL             = 0               ;   // �Ƚ��� 0 ����ѡ��     0���ߵ�ƽ��Ч 1���͵�ƽ��Ч ֻӰ��Ƚ����ж�
    CMP_InitStruct.CMP0_IE              = DISABLE         ;   // �Ƚ��� 0 �ж�ʹ��
    CMP_InitStruct.CMP0_RE              = DISABLE         ;   // �Ƚ��� 0 DMA ����ʹ��
    CMP_InitStruct.CMP0_W_PWM_POL       = DISABLE         ;   // �Ƚ��� 0 ���� PWM �źż���ѡ��
    CMP_InitStruct.CMP0_IRQ_TRIG        = DISABLE         ;   // �Ƚ��� 0 ���ش���ʹ��
    CMP_InitStruct.CMP0_IN_EN           = DISABLE         ;   // �Ƚ��� 0 �ź�����ʹ��
    CMP_InitStruct.CMP0_CHN3P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 0 ����
    CMP_InitStruct.CMP0_CHN2P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 0 ����
    CMP_InitStruct.CMP0_CHN1P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 0 ����
    CMP_InitStruct.CMP0_CHN0P_WIN_EN    = DISABLE         ;   // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 0 ����
    CMP_Init(&CMP_InitStruct);
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>Yangzj       <td>����
  *@par �޸���־:����CMP�ź���Դѡ��
 * </table>
  * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��17�� <td>1.1     <td>Yangzj       <td>����
  *@par �޸���־:�޸�ģ��ʹ��
 * </table>
  * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��25�� <td>1.2     <td>Yangzj       <td>����
  *@par �޸���־:�޸��˲�����
 * </table>
  * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��26�� <td>1.3     <td>Yangzj       <td>����
 * </table>
 */
void CMP_Init(CMP_InitTypeDef *this)
{
    // Comparator��ʼ��
    SYS_WR_PROTECT = 0x7A83;
    SYS_AFE_REG1   = (SYS_AFE_REG1 & (BIT15 | BIT6 | BIT1 | BIT0)) |
                     (this -> CMP1_SELP         << 12) | (this -> CMP_FT            << 11) |
                     (this -> CMP0_SELP         <<  8) | (this -> CMP_HYS           <<  7) |
                     (this -> CMP1_SELN         <<  4) | (this -> CMP0_SELN         <<  2);
    /* CMP_HYS �Ƚ����ͻع��ܣ�Ĭ��20mV*/
    SYS_WR_PROTECT = 0;
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP1,this->CMP1_EN);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP0,this->CMP0_EN);
    
    // CMP��ʼ��
    if(this->CMP1_IN_EN || this->CMP0_IN_EN)
    {
        SYS_ModuleClockCmd(SYS_Module_CMP,ENABLE);
    }
    else
    {
        SYS_ModuleClockCmd(SYS_Module_CMP,DISABLE);
    }
    CMP -> IE      = (this -> CMP1_RE           <<  9) | (this -> CMP0_RE           <<  8) |
                     (this -> CMP1_IE           <<  1) | (this -> CMP0_IE);
    if(this->CLK10_EN == DISABLE)
    {
        if(this->CMP1_IN_EN || this->CMP0_IN_EN)
        {
            CMP->TCLK = BIT3;
        }
        else
        {
            CMP->TCLK = 0;
        }
    }
    else
    {
        CMP->TCLK  = (this -> FIL_CLK10_DIV16   <<  4) | (this -> CLK10_EN          <<  3) |
                     (this -> FIL_CLK10_DIV2);
    }
    CMP -> CFG     = (this -> CMP1_W_PWM_POL    <<  7) | (this -> CMP1_IRQ_TRIG     <<  6) |
                     (this -> CMP1_IN_EN        <<  5) | (this -> CMP1_POL          <<  4) |
                     (this -> CMP0_W_PWM_POL    <<  3) | (this -> CMP0_IRQ_TRIG     <<  2) |
                     (this -> CMP0_IN_EN        <<  1) | (this -> CMP0_POL);           
    CMP -> BLCWIN  = (this -> CMP1_CHN3P_WIN_EN <<  7) | (this -> CMP1_CHN2P_WIN_EN <<  6) |
                     (this -> CMP1_CHN1P_WIN_EN <<  5) | (this -> CMP1_CHN0P_WIN_EN <<  4) |
                     (this -> CMP0_CHN3P_WIN_EN <<  3) | (this -> CMP0_CHN2P_WIN_EN <<  2) |
                     (this -> CMP0_CHN1P_WIN_EN <<  1) | (this -> CMP0_CHN0P_WIN_EN);
    CMP -> IF = 3;
}

/**
 *@brief @b ��������:   void CMP_StructInit(CMP_InitTypeDef *this)
 *@brief @b ��������:   ADC�ṹ���ʼ��
 *@see�����ú�����       ��
 *@param���������       CMP_InitTypeDef
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
            CMP_StructInit CMP_InitStructure;
		    CMP_StructInit(&CMP_InitStructure); //��ʼ���ṹ��
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>Yangzj       <td>����
 * </table>
 *@par �޸���־:����CMP�ź���Դ��ʼ��   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��17�� <td>1.1     <td>Yangzj       <td>����
 * </table>
 */
void CMP_StructInit(CMP_InitTypeDef *this)
{
    // �Ƚ���IO�˲�
    this -> FIL_CLK10_DIV16   = 0 ;                     // �Ƚ��� 1/0 �˲�
    this -> CLK10_EN          = ENABLE ;                // �Ƚ��� 1/0 �˲�ʱ��ʹ��
    this -> FIL_CLK10_DIV2    = 0 ;                     // �Ƚ��� 1/0 �˲�ʱ�ӷ�Ƶ
    this -> CMP_FT            = ENABLE ;                // �Ƚ������ٱȽ�ʹ��
    this -> CMP_HYS           = CMP_HYS_20mV ;          // �Ƚ����ز�ѡ��
        
    //�Ƚ���1
    this -> CMP1_EN           = DISABLE ;               // �Ƚ��� 0 ʹ��
    this -> CMP1_IE           = DISABLE ;               // �Ƚ��� 1 �ж�ʹ��
    this -> CMP1_RE           = DISABLE ;               // �Ƚ��� 1 DMA ����ʹ��
    this -> CMP1_W_PWM_POL    = 0 ;                     // �Ƚ��� 1 ���� PWM �źż���ѡ��
    this -> CMP1_IRQ_TRIG     = DISABLE ;               // �Ƚ��� 1 ���ش���ʹ��
    this -> CMP1_IN_EN        = DISABLE ;               // �Ƚ��� 1 �ź�����ʹ��
    this -> CMP1_POL          = 0 ;                     // �Ƚ��� 1 ����ѡ��
    this -> CMP1_SELP         = CMP_SELP_IP0 ;          // �Ƚ��� 1 �ź�����ѡ��
    this -> CMP1_SELN         = CMP_SELN_IN ;           // �Ƚ��� 1 �źŸ���ѡ��
    this -> CMP1_CHN3P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN2P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN1P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN0P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 1 ����

    //�Ƚ���0
    this -> CMP0_EN           = DISABLE ;               // �Ƚ��� 0 ʹ��
    this -> CMP0_IE           = DISABLE ;               // �Ƚ��� 0 �ж�ʹ��
    this -> CMP0_RE           = DISABLE ;               // �Ƚ��� 0 DMA ����ʹ��
    this -> CMP0_W_PWM_POL    = 0 ;                     // �Ƚ��� 1 ���� PWM �źż���ѡ��
    this -> CMP0_IRQ_TRIG     = DISABLE ;               // �Ƚ��� 1 ���ش���ʹ��
    this -> CMP0_IN_EN        = DISABLE ;               // �Ƚ��� 1 �ź�����ʹ��
    this -> CMP0_POL          = 0 ;                     // �Ƚ��� 1 ����ѡ��
    this -> CMP0_SELP         = CMP_SELP_IP0 ;          // �Ƚ��� 0 �ź�����ѡ��
    this -> CMP0_SELN         = CMP_SELN_IN ;           // �Ƚ��� 0 �źŸ���ѡ��
    this -> CMP0_CHN3P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN2P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN1P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN0P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 0 ����
}
/**
 *@brief @b ��������:   u8 GET_CMP_data(u8 CMPx,u8 GET_CMP_val)
 *@brief @b ��������:   ��ȡ�Ƚ������
 *@see�����ú�����       ��
 *@param���������       CMP0��CMP1����ȡCMP0��CMP1�ȽϽ��
 *@param���������       ��
 *@return�� �� ֵ��      �ȽϽ��0/1
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code    
             GET_CMP_data(CMP1, 1);//��ȡCMP1�ȽϽ��
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��21�� <td>1.0        <td>Yangzj         <td>����
 * <tr><td>2023��4��04�� <td>1.1        <td>Yangzj         <td>�޸�ͨ�����������
 * </table>
 */
u8 GET_CMP_data(u8 CMPx,u8 GET_CMP_val)
{
    if(CMPx == CMP0)
    {
        if(GET_CMP_val)
        {
            if(CMP->DATA&BIT8)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(CMP->DATA&BIT0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else if(CMPx == CMP1)
    {
        if(GET_CMP_val)
        {
            if(CMP->DATA&BIT9)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(CMP->DATA&BIT1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
}
 /**
 *@brief @b ��������:   u8 CMP_GetIRQFlag(u8 CMPx)
 *@brief @b ��������:   ��ȡ�Ƚ����ж�
 *@see�����ú�����       ��
 *@param���������       CMP0��CMP1����ȡCMP0��CMP1�жϱ�־λ
 *@param���������       ��
 *@return�� �� ֵ��      TIM�жϱ�־0/1
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code    
             if(CMP_GetIRQFlag(CMP1))//��ȡCMP1�жϱ�־λ
              {
                CMP_ClearIRQFlag(CMP1);//���CMP1�жϱ�־λ
              }
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��21�� <td>1.0        <td>Yangzj         <td>����
 * </table>
 */
u8 CMP_GetIRQFlag(u8 CMPx)
{
	if(CMPx == CMP0)
    {
        if(CMP_IF&BIT0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(CMPx == CMP1)
    {
        if(CMP_IF&BIT1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

 /**
 *@brief @b ��������:   void CMP_ClearIRQFlag(u8 CMPx)
 *@brief @b ��������:   ���CMP�жϱ�־
 *@see�����ú�����       ��
 *@param���������       CMP0��CMP1�����CMP0��CMP1�жϱ�־λ
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code    
             if(CMP_GetIRQFlag(CMP1))//��ȡCMP1�жϱ�־λ
              {
                CMP_ClearIRQFlag(CMP1);//���CMP1�жϱ�־λ
              }
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��4��11�� <td>1.0       <td>HuangMG         <td>����
 * </table>
 */
void CMP_ClearIRQFlag(u8 CMPx)
{
	if(CMPx == CMP0)
    {
        CMP_IF=BIT0;
    }
    else if(CMPx == CMP1)
    {
        CMP_IF=BIT1;
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
