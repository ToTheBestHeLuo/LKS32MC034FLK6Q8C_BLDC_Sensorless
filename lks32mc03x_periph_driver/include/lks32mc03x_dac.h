/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_dac.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� DAC������������ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��18�� <td>1.0     <td>Zhu Jie    <td>����
 * </table>
 */
#ifndef _LKS32MC03x_DAC_H_
#define _LKS32MC03x_DAC_H_

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
typedef struct
{	
	  uint8_t DACOUT_EN;                 /**< DAC���ʹ�ܣ�DISABLE����ʹ�ܣ�ENABLE��ʹ�ܡ� */
    uint8_t DAC_VERSION;               /**< 03оƬ�汾�ţ�1��ʾA�汾��2��ʾB�汾��3��ʾC�汾���������ã����� */
	  uint8_t DAC_GAIN;                  /**< DAC����ѡ��2��1.2V��0��3.0V; 1, 4.8V��ע��03A�汾ֻ��3.0Vһ�����̣�B�汾��3.0V��4.8V�������̣�C�汾��1.2V��3.0V��4.8V�������� */ 
}DAC_InitTypeDef;

typedef struct
{
	  uint8_t VersionAndDACGain;         /**< оƬ�ͺź�DAC���� 1��Ӧ1.2V���� 2��Ӧ3.0V���� 3��Ӧ4.8V���� */
	  int16_t DAC_AMC;                   /**< DAC����У׼ֵ */
	  int16_t DAC_DC;                    /**< DACƫ��У׼ֵ */                   
}DAC_CheckTypeDef;

#define DAC_RANGE_1V2                  2                       /**< DAC 1.2V���� */
#define DAC_RANGE_3V0                  0                       /**< DAC 3.0V���� */
#define DAC_RANGE_4V8                  1                       /**< DAC 4.8V���� */

void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);/* DAC�ṹ���ʼ�� */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct);      /* DAC��ʼ�� */
void DAC_OutputValue(uint32_t DACValue);             /* DAC�����ֵ����--������ */
void DAC_OutputVoltage(uint16_t DACVoltage);         /* DAC���ģ������ֵ����--ģ���� */
void DAC_Output(DAC_InitTypeDef* DAC_InitStruct);    /* DAC�����IO��ʹ������ */
#endif

