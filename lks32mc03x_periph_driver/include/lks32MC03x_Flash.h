 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� LKS32MC03x_flash.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� FLASH������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
#ifndef __LKS32MC03x_FLASH__
#define __LKS32MC03x_FLASH__
#include "lks32mc03x_lib.h"

extern volatile u32 erase_flag;
extern volatile u32 progm_flag;
void EraseSector(u32 adr);
int ProgramPage(u32 adr, u32 sz, u8 *buf);
void Read_More_Flash(u32 adr, u32 sz, u32 *buf);
u32 Read_Flash(uint32_t adr);
 
#endif

