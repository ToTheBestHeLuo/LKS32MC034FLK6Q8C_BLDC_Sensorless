 /**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_hall.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� HALL������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14��  <td>1.0      <td>HuangMG      <td>����
 * </table>
 */
#include "lks32mc03x_hall.h"

/**
*@brief @b ��������:   void HALL_Init(HALL_InitTypeDef* HALL_InitStruct)
*@brief @b ��������:   HALL��ʼ������
*@see���������ݣ�      SYS_ModuleClockCmd()
*@param���������      HALL_InitTypeDef HALL_InitStruct
*@param���������      ��
*@return�� �� ֵ��     ��
*@note����˵����       ��
*@warning             ��
*@par ʾ�����룺
*@code
           HALL_InitTypeDef HALL_InitStruct;
           HALL_StructInit(&HALL_InitStruct);             // ��ʼ���ṹ��
           HALL_InitStruct.HALL_Ena = ENABLE;             // ģ��ʹ��   
           HALL_InitStruct.ClockDivision = HALL_CLK_DIV1; // ����Hallģ��ʱ�ӷ�Ƶϵ�� 
           HALL_InitStruct.CountTH = 9600000;             // Hallģ�����ģֵ����������ģֵ�������ʱ�ж� 
           HALL_InitStruct.FilterLen = 512;               // Hall�ź������˲����� 512��ʱ������ 
           HALL_InitStruct.Filter75_Ena = ENABLE;         // Hall�ź��˲���ʽ��7��5ģʽ����ȫ1��Чģʽ 
           HALL_InitStruct.Capture_IRQ_Ena = ENABLE;      // ��׽�ж�ʹ�� 
           HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;     // ��ʱ�ж�ʹ�� 
           HALL_InitStruct.softIE = DISABLE;              // ����ж�ʹ�� 
           HALL_Init(&HALL_InitStruct);
 @endcode
*@par �޸���־:
* <table>
* <tr><th>Date	        <th>Version    <th>Author      <th>Description
* <tr><td>2021��10��14�� <td>1.0       <td>HuangMG           <td>����
* </table>
*/
void HALL_Init(HALL_InitTypeDef *HALL_InitStruct)
{

   SYS_ModuleClockCmd(SYS_Module_HALL, ENABLE); //HALLʱ��ʹ��
   HALL_CFG = (HALL_InitStruct->FilterLen) | (HALL_InitStruct->ClockDivision << 16) 
              | (HALL_InitStruct->Filter75_Ena << 20) | (HALL_InitStruct->HALL_Ena << 24) 
              | (HALL_InitStruct->HALL_CHGDMA_Ena << 25) | (HALL_InitStruct->HALL_OVDMA_Ena << 26) 
              | (HALL_InitStruct->Capture_IRQ_Ena << 28) | (HALL_InitStruct->OverFlow_IRQ_Ena << 29) 
              | (HALL_InitStruct->softIE << 30);
   HALL_TH = HALL_InitStruct->CountTH;
   HALL_INFO = 0;
}

/**
*@brief @b ��������:   void HALL_StructInit(HALL_InitTypeDef* HALL_InitStruct)
*@brief @b ��������:   HALL�ṹ���ʼ��
*@see���������ݣ�       ��
*@param���������       HALL_InitTypeDef  HALL_InitStruct
*@param���������       ��
*@return�� �� ֵ��      ��
*@note����˵����        ��
*@warning              ��
*@par ʾ�����룺
*@code		   
           HALL_InitTypeDef HALL_InitStruct;
           HALL_StructInit(&HALL_InitStruct); //��ʼ���ṹ��
 @endcode
*@par �޸���־:
* <table>
* <tr><th>Date	        <th>Version  <th>Author  <th>Description
* <tr><td>2021��10��14�� <td>1.0      <td>HuangMG     <td>����
* </table>
*/
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct)
{
   HALL_InitStruct->FilterLen = 1023;
   HALL_InitStruct->ClockDivision = HALL_CLK_DIV1;
   HALL_InitStruct->Filter75_Ena = ENABLE;
   HALL_InitStruct->HALL_Ena = ENABLE;
   HALL_InitStruct->Capture_IRQ_Ena = ENABLE;
   HALL_InitStruct->HALL_CHGDMA_Ena = DISABLE;
   HALL_InitStruct->HALL_OVDMA_Ena = DISABLE;
   HALL_InitStruct->OverFlow_IRQ_Ena = DISABLE;
   HALL_InitStruct->CountTH = 1000;
   HALL_InitStruct->softIE = DISABLE;
}

 /**
 *@brief @b ��������:   uint32_t HALL_GetFilterValue(void)
 *@brief @b ��������:   ȡ��HALLֵ���˲����
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      �����˲���HALL�źŽ��ֵ��ǰ��λ��Ч������λ��Ϊ0
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetFilterValue();//��ȡ�����˲���HALL���ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0      <td>HuangMG     <td>����
 * </table>
 */
uint32_t HALL_GetFilterValue(void)
{
   return (HALL_INFO & 0x07);
}

/**
 *@brief @b ��������:   uint32_t HALL_GetCaptureValue(void)
 *@brief @b ��������:   ȡ��HALLֵ��δ�˲��������������ԭʼHALL״ֵ̬
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      δ�˲���HALL�źŽ��ֵ��ǰ��λ��Ч������λ��Ϊ0
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetCaptureValue();//��ȡδ�˲���HALL���ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0      <td>HuangMG     <td>����
 * </table>
 */ 
uint32_t HALL_GetCaptureValue(void)
{
   return (HALL_INFO >> 8) & 0x07;
}

 /**
 *@brief @b ��������:   uint32_t HALL_WIDCount(void)
 *@brief @b ��������:   ��ȡHALL�źű仯�¼�ʱ��HALL����ֵ
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��ȡ����HALL�ź��κ�һ���źŷ����仯�¼�ʱ�̵�HALL�������ļ���ֵ
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      uint32_t HALL_Value = 0;
            HALL_Value = HALL_WIDCount();//��ȡHALL�źű仯�¼�ʱHALL����ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2016��04��19�� <td>1.0      <td>cfwu     <td>����
 * </table>
 */
uint32_t HALL_WIDCount(void)
{
    return HALL->WIDTH;
}

/**
 *@brief @b ��������:   uint32_t HALL_GetCount(void)
 *@brief @b ��������:   ��ȡʵʱHALL������ֵ
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ʵʱHALL������ֵ
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      uint32_t HALL_Value = 0;
            HALL_Value = HALL_GetCount();//��ȡʵʱHALL������ֵ
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0      <td>HuangMG     <td>����
 * </table>
 */
uint32_t HALL_GetCount(void)
{
   return HALL_CNT;
}

/**
 *@brief @b ��������:   uint32_t HALL_GetIRQFlag(uint32_t tempFlag)
 *@brief @b ��������:   ��ȡHALL�жϱ�־
 *@see���������ݣ�       ��
 *@param���������       
                        tempFlag: \n
 * <table>              <tr><th>HALL_CAPTURE_EVENT   <td>HALL�źű仯�ж� \n
 *                      <tr><th>HALL_OVERFLOW_EVENT  <td>HALL��������ж�
 * </table>
 *@param���������       ��
 *@return�� �� ֵ��      HALL�жϱ�־ Ϊ1����Ӧ��־λ��λ��Ϊ0����Ӧ��־λδ��λ
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		    if(HALL_GetIRQFlag(HALL_CAPTURE_EVENT))//��ȡHALL�źű仯�жϱ�־λ
            {    
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��5��20��  <td>1.0     <td>HuangMG     <td>����
 * </table>
 */
uint32_t HALL_GetIRQFlag(uint32_t tempFlag)
{
    return (HALL_INFO & tempFlag);
}

/**
 *@brief @b ��������:   uint32_t HALL_ClearIRQFlag(uint32_t tempFlag)
 *@brief @b ��������:   ���HALL�жϱ�־λ
 *@see���������ݣ�       ��
 *@param���������       
                        tempFlag: \n
 * <table>              <tr><th>HALL_CAPTURE_EVENT   <td>HALL�źű仯�ж� \n
 *                      <tr><th>HALL_OVERFLOW_EVENT  <td>HALL��������ж�
 * </table>
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		    if(HALL_GetIRQFlag(HALL_CAPTURE_EVENT))//��ȡHALL�źű仯�жϱ�־λ
            {    
                HALL_ClearIRQFlag(HALL_CAPTURE_EVENT);//���HALL�źű仯�жϱ�־λ
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��5��20��  <td>1.0     <td>HuangMG     <td>����
 * </table>
 */
void HALL_ClearIRQFlag(uint32_t tempFlag)
{
    HALL_INFO = tempFlag;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
