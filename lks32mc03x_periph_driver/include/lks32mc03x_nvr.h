/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_nvr.h\n
 * 文件标识： 无 \n
 * 内容摘要： NVR驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月12日 <td>1.0     <td>Yangzj      <td>创建
 * </table>
 */
 // 建议在初始化的过程中调用
/**
 *@brief 读取芯片模块校正值函数
 *@par 示例代码
 *@code
      SYS_AFE_REG5 = (Read_Trim(0x00000198)>>16) & 0xffff; 
 *@endcode
 */
unsigned int Read_Trim(unsigned int addr);              //有效地址范围((addr >= 0x00000190) && (addr <= 0x0000001FF)) || ((addr >= 0x0000024C) && (addr <= 0x000000258))
void Prog_Trim(unsigned int addr, unsigned int data);   //有效地址范围((addr >= 0x000001E0) && (addr <= 0x0000001FF))
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
