/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_nvr.h\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� NVR����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��12�� <td>1.0     <td>Yangzj      <td>����
 * </table>
 */
 // �����ڳ�ʼ���Ĺ����е���
/**
 *@brief ��ȡоƬģ��У��ֵ����
 *@par ʾ������
 *@code
      SYS_AFE_REG5 = (Read_Trim(0x00000198)>>16) & 0xffff; 
 *@endcode
 */
unsigned int Read_Trim(unsigned int addr);              //��Ч��ַ��Χ((addr >= 0x00000190) && (addr <= 0x0000001FF)) || ((addr >= 0x0000024C) && (addr <= 0x000000258))
void Prog_Trim(unsigned int addr, unsigned int data);   //��Ч��ַ��Χ((addr >= 0x000001E0) && (addr <= 0x0000001FF))
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
