
/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_dsp.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� DSP����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��04��18�� <td>1.0     <td> Zhu Jie      <td>����
 * </table>
 */
 
#ifndef __LKS32MC03x_DSP_H
#define __LKS32MC03x_DSP_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

/** 
 *@brief ��������ṹ����
 */
typedef struct
{
	  s32 Dividend;     /**< ������ */
	  s32 Divisor;      /**< ����   */
    s32 Quotient;       /**< ��     */
    s32 Remainder;      /**< ����   */
} stru_DiviComponents;

void DSP_Cmd(FuncState state);                          /* DSPʹ�ܺ͹ر� */
void DSP_CalcDivision(stru_DiviComponents *stru_Divi);  /* DSP�������� */
uint32_t DSP_GetSqrt(u32 Data); /*DSPȡ�ÿ����� sprt(Data)*/

#endif 

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
