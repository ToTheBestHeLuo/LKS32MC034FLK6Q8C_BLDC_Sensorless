/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_opa.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� OPA�˷������������� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
#include "lks32mc03x_opa.h"

/**
 *@brief @b ��������:   void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b ��������:   OPA��ʼ������
 *@see���������ݣ�       ��
 *@param���������       enumOPA opa , OPA_InitTypeDef *OPA_InitStruct 
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
    OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);//��ʼ���ṹ��
    OPA_InitStruct.OPA_CLEna = ENABLE;       //ʹ��OPA
    OPA_InitStruct.OPA_Gain = PGA_GAIN_4P25; //OPA�ڲ��������ѡ��170��40
    OPA_InitStruct.OPA_B_EN = OPA0_IN_IP_B;  //OPA0ʹ�� OPA0_IN_B/OPA0_IP_B ��Ϊ�������
    OPA_Init(OPA, &OPA_InitStruct);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��20�� <td>1.0       <td>HuangMG           <td>����
 * </table>
 */
void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct)
{
	uint32_t tmp1;
	SYS_WR_PROTECT = 0x7a83;   /* ���ϵͳ�Ĵ���д���� */
	tmp1 = SYS_AFE_REG0;
	
	if (opa == OPA)
	{
		tmp1 &= ~(BIT0 | BIT1 | BIT5 | BIT9);
		tmp1 |= OPA_InitStruct->OPA_Gain;

		tmp1 |= OPA_InitStruct->OPA_B_EN << 5;
		
		tmp1 |= OPA_InitStruct->OPA_CLEna << 9;	
	}

	SYS_AFE_REG0 = tmp1;
	SYS_WR_PROTECT = 0x0;   /* ����ϵͳ�Ĵ���д���� */
}

/**
 *@brief @b ��������:   void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
 *@brief @b ��������:   OPA�ṹ���ʼ��
 *@see���������ݣ�       ��
 *@param���������       OPA_InitTypeDef *OPA_InitStruct 
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			    OPA_InitTypeDef OPA_InitStruct;
				OPA_StructInit(&OPA_InitStruct);       //��ʼ���ṹ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��20�� <td>1.0       <td>HuangMG           <td>����
 * </table>
 */
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
{
   OPA_InitStruct->OPA_Gain = PGA_GAIN_4P25;
	 OPA_InitStruct->OPA_B_EN = OPA0_IN_IP;
   OPA_InitStruct->OPA_CLEna = DISABLE;
}

/**
 *@brief @b ��������:   void OPA_OUT(enumOPA opa, FuncState state)
 *@brief @b ��������:   OPA�ⲿ�����������ⲿP0.7����
 *@see���������ݣ�       ��
 *@param���������       enumOPA opa, FuncState state
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			   OPA_OUT(OPA,ENABLE); //��OPA���ͨ���ⲿP0.7�����ͳ�
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��20�� <td>1.0       <td>HuangMG        <td>����
 * </table>
 */
void OPA_OUT(enumOPA opa, FuncState state)
{
	SYS_WR_PROTECT = 0x7a83;   /* ���ϵͳ�Ĵ���д���� */
  if(state != DISABLE)
	{
		if(opa == OPA)
		{		
		  SYS_AFE_REG0 |= 0x01<<2;
		}	
  }else{
		  SYS_AFE_REG0 &= ~(0x1<<2);
	}
	SYS_WR_PROTECT = 0x0;   /* ����ϵͳ�Ĵ���д���� */
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
