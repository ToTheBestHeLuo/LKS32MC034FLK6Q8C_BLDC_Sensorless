  /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_flash.c\n
 * 文件标识： 无 \n
 * 内容摘要： FLASH外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0    <td>HMG      <td>创建
 * </table>
 */
#include "lks32mc03x_flash.h"
/**
 * @brief flash擦除操作启动变量
 */
volatile u32 erase_flag = 0;
/**
 * @brief flash编程操作启动变量
 */
volatile u32 progm_flag = 0;

 /**
 *@brief @b 函数名称:   void EraseSector(u32 adr)
 *@brief @b 功能描述:   Flash按扇区擦除操作
 *@see被引用内容：       无
 *@param输入参数：      
                        adr：       扇区地址  (一个扇区512字节) \n
                        erase_flag：调用函数前必须赋值0x9A0D361F，否则不执行擦除，用来防程序跑飞
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
           erase_flag = 0x9A0D361F;//擦除解锁
           EraseSector(0x00000000);//擦除操作
           erase_flag = 0x00;//擦除上锁
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG      <td>创建
 * </table>
 */
void EraseSector(u32 adr)
{
  u32 key1, key2, key3;

  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
	SYS_WR_PROTECT = 0x7a83; /* 开启写使能*/
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
	SYS_WR_PROTECT = 0x0; /* 关闭写使能*/
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
}
 /**
 *@brief @b 函数名称:   int ProgramPage(u32 adr, u32 sz, u8 *buf)
 *@brief @b 功能描述:   Flash编程操作
 *@see被引用内容：       无
 *@param输入参数：      
                        adr：扇区地址   \n
                        sz : 编程字节数量(0~512字节) \n
                        buf: 要编程的数据数组指针 \n
                        progm_flag：调用函数前必须赋值0x9AFDA40C，否则不执行编程，用来防程序跑飞 
 *@param输出参数：      无
 *@return返 回 值：     1：编程成功；  0: 编程失败
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
           u8 Flash_Buff[2] = {0x12,0x23};
           erase_flag = 0x9A0D361F;//擦除解锁
           EraseSector(0x00000000);//擦除flash的main区域即存储程序区域
           erase_flag = 0x00;//擦除上锁

           progm_flag = 0x9AFDA40C;//编程解锁
           ProgramPage(0x00000000,2,Flash_Buff);//编程flash的main区域即存储程序区域
           erase_flag = 0x00;      //编程上锁
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>HMG      <td>创建
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
  SYS_WR_PROTECT = 0x7a83; /* 开启写使能*/
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
  SYS_WR_PROTECT = 0x0; /* 关闭写使能*/
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
  progm_flag = 0;
  return (t_rlt);
}

 /**
 *@brief @b 函数名称:   u32 Read_Flash(uint32_t adr)
 *@brief @b 功能描述:   读取FLASH数据函数
 *@see被引用内容：       无
 *@param输入参数：      
                        adr：       扇区地址  (一个扇区512字节) \n
 *@param输出参数：      无
 *@return返 回 值：     读取的数据值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
           Flash_main = Read_Flash(0x00000000);//获取flash的main区域0x00000000地址一个word数据
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0       <td>HMG         <td>创建
 * </table>
 */
u32 Read_Flash(uint32_t adr)
{
  uint32_t data;
  FLASH_CFG &= ~BIT11; //恢复MIAN操作
  FLASH_ADDR = adr;
  data = FLASH_RDATA;
  return data;
}

 /**
 *@brief @b 函数名称:   void Read_More_Flash(u32 adr, u32 sz, u32 *buf)
 *@brief @b 功能描述:   读取FLASH多地址数据函数
 *@see被引用内容：       无
 *@param输入参数：      
                        adr:扇区地址  (一个扇区512字节) \n
                        buf:读取数据存储的地址 \n
                        sz :读取sz个字
 *@param输出参数：      无
 *@return返 回 值：     读取的数据值
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
           u32 Flash_Read_Buff[4] = {0}; 
           Read_More_Flash(0x00000000 ,4,Flash_Read_Buff);//获取flash的main区域0x00000000地址4个word数据
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0      <td>HMG          <td>创建
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
