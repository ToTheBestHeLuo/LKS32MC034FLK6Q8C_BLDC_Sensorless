 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC03x_flash.h\n
 * 文件标识： 无 \n
 * 内容摘要： FLASH外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG      <td>创建
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

