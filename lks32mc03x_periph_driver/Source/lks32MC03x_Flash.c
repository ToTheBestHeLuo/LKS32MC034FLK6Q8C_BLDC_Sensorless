  /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_flash.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� FLASH������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0    <td>HMG      <td>����
 * </table>
 */
#include "lks32mc03x_flash.h"
/**
 * @brief flash����������������
 */
volatile u32 erase_flag = 0;
/**
 * @brief flash��̲�����������
 */
volatile u32 progm_flag = 0;

 /**
 *@brief @b ��������:   void EraseSector(u32 adr)
 *@brief @b ��������:   Flash��������������
 *@see���������ݣ�       ��
 *@param���������      
                        adr��       ������ַ  (һ������512�ֽ�) \n
                        erase_flag�����ú���ǰ���븳ֵ0x9A0D361F������ִ�в����������������ܷ�
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           erase_flag = 0x9A0D361F;//��������
           EraseSector(0x00000000);//��������
           erase_flag = 0x00;//��������
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */
void EraseSector(u32 adr)
{
  u32 key1, key2, key3;

  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
	SYS_WR_PROTECT = 0x7a83; /* ����дʹ��*/
  if (erase_flag == 0x9A0D361F)
  { //get flash_cfg addr
		
    SYS_FLSE = 0x8FCA;
    key1 = 0xB00C060A;
    key2 = 0x2A003015;
    key3 = erase_flag ^ key1 ^ key2;
    REG32(key3) &= ~0x80008000;
    FLASH_ADDR = adr;
    REG32(key3) |= (0x80000000);
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;
  }

  if (erase_flag == 0x9A0D361F)
  { //get flash_erase addr
    SYS_FLSE = 0x8FCA;
    key1 = 0xB001341A;
    key2 = 0x2A0D0215;
    key3 = erase_flag ^ key1 ^ key2;
    REG32(key3) = 0x7654DCBA; //trig sector erase, FLASH_ERASE
    FLASH_CFG &= ~0x80000000;
    erase_flag = 0x00000000;
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;
  }
  SYS_FLSE = 0x0;
  FLASH_CFG &= ~0x80000000;
  erase_flag = 0x00000000;
	SYS_WR_PROTECT = 0x0; /* �ر�дʹ��*/
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
}
 /**
 *@brief @b ��������:   int ProgramPage(u32 adr, u32 sz, u8 *buf)
 *@brief @b ��������:   Flash��̲���
 *@see���������ݣ�       ��
 *@param���������      
                        adr��������ַ   \n
                        sz : ����ֽ�����(0~512�ֽ�) \n
                        buf: Ҫ��̵���������ָ�� \n
                        progm_flag�����ú���ǰ���븳ֵ0x9AFDA40C������ִ�б�̣������������ܷ� 
 *@param���������      ��
 *@return�� �� ֵ��     1����̳ɹ���  0: ���ʧ��
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           u8 Flash_Buff[2] = {0x12,0x23};
           erase_flag = 0x9A0D361F;//��������
           EraseSector(0x00000000);//����flash��main���򼴴洢��������
           erase_flag = 0x00;//��������

           progm_flag = 0x9AFDA40C;//��̽���
           ProgramPage(0x00000000,2,Flash_Buff);//���flash��main���򼴴洢��������
           erase_flag = 0x00;      //�������
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HMG      <td>����
 * </table>
 */

int ProgramPage(u32 adr, u32 sz, u8 *buf)
{
  /* Add your Code */
  volatile u32 Addr, size;
  volatile u8 *p;
  volatile u8 t_rlt = 1;
  u32 key1, key2, key3;
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
  SYS_WR_PROTECT = 0x7a83; /* ����дʹ��*/
  if (progm_flag == 0x9AFDA40C)
  {
    SYS_FLSP = 0x8F35;
    //get flash_cfg addr
    key1 = 0x6A5C040F;
    key2 = 0xF0A0A003;
    key3 = progm_flag ^ key1 ^ key2;
    REG32(key3) &= ~0x80008000;
    FLASH_ADDR = adr;
    REG32(key3) |= (0x08000000);
    progm_flag = 0;
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;

    p = buf;
    size = (sz + 3) & ~3; // align the word
    Addr = adr;
    while (size)
    {
      FLASH_ADDR = (Addr & ~0x00000003);                                        // address alignment
      FLASH_WDATA = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24); // write data to flash

      p += 4;
      size -= 4; // Go to next word
      Addr += 4;
    }

    p = buf;
    size = (sz + 3) & ~3; // align the word
    Addr = adr;
    while (size)
    {
      u32 t_RData;
      FLASH_ADDR = (Addr & ~0x00000003); // address alignment
      t_RData = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24);
      if (t_RData != FLASH_RDATA)
      {
        t_rlt = 0;
      }

      p += 4;
      size -= 4;
      Addr += 4;
    }
  }
  SYS_FLSP = 0x0;
  FLASH_CFG &= ~0x08000800;
  SYS_WR_PROTECT = 0x0; /* �ر�дʹ��*/
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
  progm_flag = 0;
  return (t_rlt);
}

 /**
 *@brief @b ��������:   u32 Read_Flash(uint32_t adr)
 *@brief @b ��������:   ��ȡFLASH���ݺ���
 *@see���������ݣ�       ��
 *@param���������      
                        adr��       ������ַ  (һ������512�ֽ�) \n
 *@param���������      ��
 *@return�� �� ֵ��     ��ȡ������ֵ
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           Flash_main = Read_Flash(0x00000000);//��ȡflash��main����0x00000000��ַһ��word����
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0       <td>HMG         <td>����
 * </table>
 */
u32 Read_Flash(uint32_t adr)
{
  uint32_t data;
  FLASH_CFG &= ~BIT11; //�ָ�MIAN����
  FLASH_ADDR = adr;
  data = FLASH_RDATA;
  return data;
}

 /**
 *@brief @b ��������:   void Read_More_Flash(u32 adr, u32 sz, u32 *buf)
 *@brief @b ��������:   ��ȡFLASH���ַ���ݺ���
 *@see���������ݣ�       ��
 *@param���������      
                        adr:������ַ  (һ������512�ֽ�) \n
                        buf:��ȡ���ݴ洢�ĵ�ַ \n
                        sz :��ȡsz����
 *@param���������      ��
 *@return�� �� ֵ��     ��ȡ������ֵ
 *@note����˵����       ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
           u32 Flash_Read_Buff[4] = {0}; 
           Read_More_Flash(0x00000000 ,4,Flash_Read_Buff);//��ȡflash��main����0x00000000��ַ4��word����
  @endcode   
 *@par �޸���־:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��10��14�� <td>1.0      <td>HMG          <td>����
 * </table>
 */
void Read_More_Flash(u32 adr, u32 sz, u32 *buf)
{
  volatile u32 Addr = 0;
  volatile u32 size = 0;
  volatile u32 *p;
  size = sz;
  Addr = adr;
  p = buf;
  while (size)
  {
    *p = Read_Flash(Addr);
    while (!(FLASH_READY & BIT0))
      ;
    size -= 1;
    Addr += 4;
    p += 1;
  }
}
