 /**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_IWDG.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� IWDG������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */

#include "lks32mc03x_iwdg.h"
#include "basic.h"

/**
 *@brief @b ��������:   void IWDG_Init(IWDG_InitTypeDef *this)
 *@brief @b ��������:   ���Ź���ʼ��
 *@see���������ݣ�       ��
 *@param���������       IWDG_InitTypeDef *this ���Ź����ýṹ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
            IWDG_InitTypeDef IWDG_InitStruct;
            IWDG_StrutInit(&IWDG_InitStruct);
            IWDG_InitStruct.WDG_EN  = ENABLE;      //ʹ�ܿ��Ź�
            IWDG_InitStruct.RTH     = SECOND2IWDGCNT(2.0);//���ÿ��Ź�
            IWDG_InitStruct.DWK_EN  = DISABLE;     // ������߶�ʱ���ѹر�   
            IWDG_InitStruct.WTH     = 0;           // ���Ź���ʱ����ʱ�䣨21λ������������12��λ0��
            IWDG_Init(&IWDG_InitStruct);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void IWDG_Init(IWDG_InitTypeDef *this)
{
    this->RTH = (this->RTH > BIT21) ? BIT21 - 1 : this->RTH;
    this->WTH = (this->WTH > BIT21) ? BIT21 - 1 : this->WTH;
    IWDG->CFG = (this->DWK_EN<<4) | (this ->WDG_EN);
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->RTH = this->RTH;
    if(this->RTH > this->WTH)
    {
        IWDG->WTH = this->RTH-this->WTH;
    }
    else
    {
        IWDG->WTH = 0x001000;
    }
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}

/**
 *@brief @b ��������:   void IWDG_StrutInit(IWDG_InitTypeDef *this)
 *@brief @b ��������:   ���Ź����ýṹ���ʼ��
 *@see���������ݣ�       ��
 *@param���������       IWDG_InitTypeDef *this ���Ź����ýṹ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
                IWDG_InitTypeDef IWDG_InitStruct;
                IWDG_StrutInit(&IWDG_InitStruct);    //��ʼ���ṹ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void IWDG_StrutInit(IWDG_InitTypeDef *this)
{
    this->DWK_EN = DISABLE;             // ������߶�ʱ����ʹ��
    this->WDG_EN = DISABLE;             // �������Ź�ʹ��
    this->WTH = SECOND2IWDGCNT(1);      // ���Ź���ʱ����ʱ��,���ڸ�λʱ�����Ч
    this->RTH = SECOND2IWDGCNT(2);      // ���Ź���ʱ��λʱ�䣨21λ������������12��λ0��
                                        // SECOND2IWDGCNT�����������
}

/**
 *@brief @b ��������:   void IWDG_DISABLE(void)
 *@brief @b ��������:   �رտ��Ź�ģ��
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
                IWDG_DISABLE();    //�رտ��Ź�ģ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void IWDG_DISABLE(void)
{
    IWDG->CFG = 0x3c00;
}

/**
 *@brief @b ��������:   void IWDG_ENABLE(void)
 *@brief @b ��������:   �򿪿��Ź�ģ��
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
                IWDG_ENABLE();    //�򿪿��Ź�ģ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void IWDG_ENABLE(void)
{
    IWDG->CFG = 0x1;
}

/**
 *@brief @b ��������:   void IWDG_Feed(void)
 *@brief @b ��������:   ���Ź�ι��
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
                IWDG_Feed();    //���Ź�ι��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
void IWDG_Feed(void)
{
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
