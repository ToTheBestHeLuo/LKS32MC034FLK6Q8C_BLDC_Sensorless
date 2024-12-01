 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_opa.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� OPA����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��20�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
 
#ifndef __LKS32MC03x_OPA_H
#define __LKS32MC03x_OPA_H


/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

typedef enum
{
   OPA = 0 /**< OPA0ģ��*/

/** 
 *@brief OPA��ʼ���ṹ��������ʼ��ʱ�붨��þ��������������ַ������
 */	
}enumOPA;

typedef struct
{
     /** 
     * @brief �˷űջ����� \n
     * @see PGA_GAIN_20   \n  
     * @see PGA_GAIN_9P5  \n
     * @see PGA_GAIN_6    \n
     * @see PGA_GAIN_4P25           
     */ 
   uint32_t OPA_Gain;         
   uint32_t OPA_CLEna;        /**< �˷űջ�ʹ��:Enable,Disable*/
	  /** 
     * @brief OPA0�˿�����ѡ�� \n
     * @see OPA0_IN_IP   \n  
     * @see OPA0_IN_IP_B       
     */ 
   uint32_t OPA_B_EN;         
}OPA_InitTypeDef;

/* ------------------------------PGA������ض��� ------------------------------ */
#define PGA_GAIN_20                    0x00                   /**< ��������200:10 */
#define PGA_GAIN_9P5                   0x01                   /**< ��������190:20 */
#define PGA_GAIN_6                     0x02                   /**< ��������180:30 */
#define PGA_GAIN_4P25                  0x03                   /**< ��������170:40 */                                                                                 

#define OPA0_IN_IP                     0x00                   /**< OPA0ʹ�� OPA0_IN/OPA0_IP ��Ϊ�������*/
#define OPA0_IN_IP_B                   0x01                   /**< OPA0ʹ�� OPA0_IN_B/OPA0_IP_B ��Ϊ�������*/

void OPA_Init(enumOPA opa, OPA_InitTypeDef* OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct);
void OPA_OUT(enumOPA opa, FuncState state);

#endif /*__lks32mc08x_OPA_H */



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
