/**
 * @file 
 * @copyright (C)2018, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_tmp.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� оƬ�����¶ȴ���������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��08��25�� <td>1.0     <td>William Zhang      <td>����
 * </table>
 */

#ifndef _LKS32MC03x_TMP_H_
#define _LKS32MC03x_TMP_H_


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief оƬ�����¶ȴ�������ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */
typedef struct
{
   u16 nCofA;      /**< �¶�ϵ��A*/
   u16 nOffsetB;   /**< �¶�ϵ��ƫ��*/
} Stru_TempertureCof_Def;


void TempSensor_Init(void);
s16 GetCurrentTemperature(s16 ADC_value);

#endif /*_CONNIE_TMP_H_ */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
