 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_IWDG.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� ���Ź�����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ      <td>����
 * </table>
 */
#ifndef __LKS32MC03x_IWDG_H
#define __LKS32MC03x_IWDG_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
/** 
 *@brief IWDG�Ĵ����ṹ����
 */
typedef struct
{
    __IO uint32_t PSW; /**<IWDG����Ĵ���*/
    __IO uint32_t CFG; /**<IWDG���üĴ���*/
    __IO uint32_t CLR; /**<IWDG����Ĵ���*/
    __IO uint32_t WTH; /**<IWDG��������ʱ��������ֵ�Ĵ���*/
    __IO uint32_t RTH; /**<IWDG��������ʱ��λ����ֵ�Ĵ���*/
    __IO uint32_t CNT; /**<IWDG��������ǰ����ֵ�Ĵ���*/
} IWDG_TypeDef;
/**
 * IWDG�ṹ�����ַ����
 */
#ifndef IWDG
#define IWDG             ((IWDG_TypeDef *) AON_BASE)
#endif
/** 
 *@brief IWDG��ʼ���ṹ����
 */
typedef struct
{
    u32 DWK_EN;             /**< ������߶�ʱ����ʹ��*/
    u32 WDG_EN;             /**< �������Ź�ʹ��*/
    u32 WTH;                /**< ���Ź���ʱ����ʱ�䣨21λ������������12��λ0��*/
    u32 RTH;                /**< ���Ź���ʱ��λʱ��*/
}IWDG_InitTypeDef;


/** 
 *@brief 
 *�������ƣ�    u32 SECOND2IWDGCNT(float)
 *����������    ���Ź�ʱ�����
 *���������    ʱ�䣬��λS
 *�� �� ֵ��    ���Ź�����ֵ
 *����˵����    RCʱ�Ӿ������ޣ�ȫ�¶ȷ�Χ������20% \n
                0x80Ϊ����ת�����ȡ��
 */
#define SECOND2IWDGCNT(x)   ((u32)(64000*(float)x+0x800)&0x1ff000) /**<���Ź�ʱ�����*/

void IWDG_Init(IWDG_InitTypeDef *);                 // ���Ź���ʼ��
void IWDG_StrutInit(IWDG_InitTypeDef *);            // ���Ź����ýṹ���ʼ��
void IWDG_DISABLE(void);                            // �رտ��Ź�
void IWDG_ENABLE(void);                             // ���Ź�ʹ��
void IWDG_Feed(void);                               // ���Ź�ι��
#endif /*__lks32mc03x_IWDG_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
