 /**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_i2c.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� I2C������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	         <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��09�� <td>1.0     <td>YangZJ       <td>����
 * </table>
 */
 #include "lks32mc03x_i2c.h"

static volatile u8 i2c_dma_state = 0;   /**< I2C����״̬ */

/**
 *@brief @b ��������:   void I2C_Init(I2C_InitTypeDef *this)
 *@brief @b ��������:   I2C��ʼ��
 *@see���������ݣ�       SYS_ModuleClockCmd()  SYS_SoftResetModule();
 *@param���������       I2C_InitTypeDef *I2C_InitStruct
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          I2C_InitTypeDef I2C_InitStruct;
          I2C_StructInit(&I2C_InitStruct);                //  ��ʼ���ṹ��
          I2C_InitStruct.ADRCMP           =   DISABLE ;   //  I2C Ӳ����ַ�Ƚ�ʹ�ܿ��أ�ֻ���� DMA ģʽ�¿�������Ч��
          I2C_InitStruct.MST_MODE         =   ENABLE  ;   //  I2C ��ģʽʹ��
          I2C_InitStruct.SLV_MODE         =   DISABLE ;   //  I2C ��ģʽʹ��
          I2C_InitStruct.DMA              =   ENABLE  ;   //  I2C DMA����ʹ��
          I2C_InitStruct.BaudRate         =   100000 ;    //  I2C ������
          I2C_InitStruct.IE               =   ENABLE  ;   //  I2C �ж�ʹ��
          I2C_InitStruct.TC_IE            =   ENABLE  ;   //  I2C ���ݴ�������ж�ʹ��
          I2C_InitStruct.BUS_ERR_IE       =   DISABLE ;   //  I2C ���ߴ����¼��ж�ʹ��
          I2C_InitStruct.STOP_IE          =   DISABLE ;   //  I2C STOP �¼��ж�ʹ��
          I2C_InitStruct.BURST_NACK       =   ENABLE  ;   //  I2C ���䣬NACK �¼��ж�ʹ��
          I2C_InitStruct.BURST_ADDR_CMP   =   DISABLE ;   //  I2C ���䣬Ӳ����ַƥ���ж�ʹ��
          I2C_Init(&I2C_InitStruct);
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0       <td>YangZJ           <td>����
 * </table>
 */
void I2C_Init(I2C_InitTypeDef *this)
{
    SYS_ModuleClockCmd(SYS_Module_I2C,ENABLE);
    SYS_SoftResetModule(SYS_Module_I2C);

    {
        u32 BaudRate;
        BaudRate = ((u32)48000000+((this->BaudRate*17)>>1)) / (this->BaudRate*17) - 1;
        SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
        SYS_CLK_DIV0 = BaudRate;
        SYS_WR_PROTECT = 0;    //���ϵͳ�Ĵ���д����
    }
    
    I2C -> ADDR  = (this -> ADRCMP << 7);
    I2C -> CFG   = (this -> IE          << 7) | (this -> TC_IE       << 6) | 
                   (this -> BUS_ERR_IE  << 5) | (this -> STOP_IE     << 4) |
                   (this -> MST_MODE    << 1) | (this -> SLV_MODE);
    I2C -> SCR   = 0;
    I2C -> DATA  = 0;
    I2C -> MSCR  = 0;
    I2C -> BCR   = (this -> BURST_NACK     << 7) | (this -> BURST_ADDR_CMP << 6) |
                   (this -> DMA    << 5);
    I2C -> BSIZE = 0;
    if(this->DMA)
    {
        i2c_dma_init();
    }
}

/**
 *@brief @b ��������:   void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
 *@brief @b ��������:   I2C�ṹ���ʼ��
 *@see���������ݣ�       ��
 *@param���������       I2C_InitTypeDef *I2C_InitStruct
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      I2C_InitTypeDef I2C_InitStruct;
              I2C_StructInit(&I2C_InitStruct);  //��ʼ���ṹ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0      <td>YangZJ      <td>����
 * </table>
 */ 
void I2C_StructInit(I2C_InitTypeDef *this)
{
    this->ADRCMP           =   DISABLE    ;   //  I2C Ӳ����ַ�Ƚ�ʹ�ܿ��أ�ֻ���� DMA ģʽ�¿�������Ч��
    this->MST_MODE         =   DISABLE    ;   //  I2C ��ģʽʹ��
    this->SLV_MODE         =   DISABLE    ;   //  I2C ��ģʽʹ��
    this->DMA              =   DISABLE    ;   //  I2C DMA����ʹ��
    this->BaudRate         =   100000     ;   //  I2C ������
    this->IE               =   DISABLE    ;   //  I2C �ж�ʹ��
    this->TC_IE            =   DISABLE    ;   //  I2C ���ݴ�������ж�ʹ��
    this->BUS_ERR_IE       =   DISABLE    ;   //  I2C ���ߴ����¼��ж�ʹ��
    this->STOP_IE          =   DISABLE    ;   //  I2C STOP �¼��ж�ʹ��
    this->BURST_NACK       =   DISABLE    ;   //  I2C ���䣬NACK �¼��ж�ʹ��
    this->BURST_ADDR_CMP   =   DISABLE    ;   //  I2C ���䣬Ӳ����ַƥ���ж�ʹ��
}

/**
 *@brief @b ��������:   u8 Read_I2c_Bus_State(u16 n)
 *@brief @b ��������:   ��I2C����״̬
 *@see���������ݣ�       ��
 *@param���������       n
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      Read_I2c_Bus_State(1);  
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0      <td>YangZJ      <td>����
 * </table>
 */
u8 Read_I2c_Bus_State(u16 n)
{
    if(I2C->SCR&n)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}

 /**
 *@brief @b ��������:   void Clear_I2c_Bus_State(u16 n)
 *@brief @b ��������:   I2C����״̬��λ
 *@see���������ݣ�       ��
 *@param���������       n
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      Clear_I2c_Bus_State(1);  
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0      <td>YangZJ      <td>����
 * </table>
 */
void Clear_I2c_Bus_State(u16 n)
{
    I2C_SCR &= ~n;
}

/**
 *@brief @b ��������:   void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t n)
 *@brief @b ��������:   I2C��������
 *@see���������ݣ�       ��
 *@param���������       I2Cx:I2C , n:Ҫ������һ�ֽ�����
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
		      I2C_SendData(I2C,0x12);  //����0x12����
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0      <td>YangZJ      <td>����
 * </table>
 */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t n)
{
    I2Cx->DATA = n;
}

/**
*@brief @b ��������:   uint8_t I2C_ReadData(I2C_TypeDef *I2Cx)
*@brief @b ��������:   I2C������������
*@see���������ݣ�       ��
*@param���������       I2Cx:I2C
*@param���������       ��
*@return�� �� ֵ��      I2C���յ�һ�ֽ�����
*@note����˵����        ��
*@warning              ��
*@par ʾ�����룺
*@code
         u8 I2C_Value = 0;		      
         I2C_Value = I2C_ReadData(I2C);  //I2C���յ�һ�ֽ�����
 @endcode
*@par �޸���־:
* <table>
* <tr><th>Date	        <th>Version  <th>Author  <th>Description
* <tr><td>2022��05��21�� <td>1.0      <td>YangZJ      <td>����
* </table>
*/
uint8_t I2C_ReadData(I2C_TypeDef *I2Cx)
{
    return I2Cx->DATA;
}

/**
 *@brief @b ��������:   static void i2c_dma_delay_over()
 *@brief @b ��������:   I2C���ͽ��յȴ�����
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          i2c_dma_delay_over(); 
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0      <td>YangZJ    <td>����
 * </table>
 */
static void i2c_dma_delay_over()
{
	u32 t = 10000000;
	while (i2c_dma_state)       // �ȴ�I2C�������
	{
		t--;
		if(t==0)
		{// ���������
			return;
		}
	}
    i2c_dma_state = 0;
    while(I2C->MSCR & BIT3)     // �ȴ�I2C���߿���
    {
		t--;
		if(t==0)
		{// ���������
			return;
		}
    }
}

/**
 *@brief @b ��������:   void i2c_dma_state_over()
 *@brief @b ��������:   I2C������ɺ���
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          void I2C0_IRQHandler    (void)
          {
              I2C->SCR = 0;
              i2c_dma_state_over();  // iic�������
          } 
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0      <td>YangZJ    <td>����
 * </table>
 */ 
void i2c_dma_state_over()  // I2C�������
{
    i2c_dma_state = 0;
}

/**
 *@brief @b ��������:   static void i2c_dma_state_start()
 *@brief @b ��������:   I2C��ʼ����
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          i2c_dma_state_start(); 
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0     <td>YangZJ     <td>����
 * </table>
 */
static void i2c_dma_state_start() // I2C��ʼ����
{
    i2c_dma_state = 1;
}

/**
 *@brief @b ��������:   void i2c_dma_tx(u8 addr, u8 *data, u8 len)
 *@brief @b ��������:   I2C���ݷ��ͺ���
 *@see���������ݣ�       ��
 *@param���������       
 *                      addr��IIC���͵�ַ
 *                      data���������ݻ�����
 *                      len���������ݳ���
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          u8 i2c_Buff[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
          i2c_dma_tx(0x23 , i2c_Buff , 8);//������0x23��ַ�Ĵӻ�8���ֽ�i2c_Buff����
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0     <td>YangZJ     <td>����
 * </table>
 */
void i2c_dma_tx(u8 addr, u8 *data, u8 len)
{
	len = (len)?len:1;
	len = (len>16)?16:len;      // �������ƣ�1-16
	i2c_dma_delay_over();       // �ȴ�I2C���
	I2C->ADDR = addr & 0x7f;    // ���豸��ַ
	I2C->SCR = BIT2;           // I2C���䷽��
  I2C->BSIZE = len-1;         // I2C�������ݳ���
  DMA_CH3->DMA_CCR = 0;
	DMA_CH3->DMA_CTMS = 16;     // DMA���˵����ݳ��ȣ�ʵ�ʴ������ݳ���ΪI2C->BSIZE+1,����I2C���ݴ��䳤�ȼ���
	DMA_CH3->DMA_SADR = (u32)data;          // DMAԴ��ַ
	DMA_CH3->DMA_DADR = (u32)&(I2C->DATA);  // DMAĿ�ĵ�ַ
  DMA_CH3->DMA_CCR  = BIT6|BIT1|BIT0;     // ����DMA���䷽��ʹ��DMA
  i2c_dma_state_start();
	I2C->MSCR = 1;								// ����I2C��������
}

/**
 *@brief @b ��������:   void i2c_dma_rx(u8 addr, u8 *data, u8 len)
 *@brief @b ��������:   I2C���ݽ��պ���
 *@see���������ݣ�       ��
 *@param���������       
 *                      addr��IIC���͵�ַ
 *                      data���������ݻ�����
 *                      len���������ݳ���
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          u8 i2c_Buff[8] = {0x00};
          i2c_dma_rx(0x23 , i2c_Buff , 8);//������0x23��ַ�Ĵӻ�8���ֽڴ洢��i2c_Buff������
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0     <td>YangZJ     <td>����
 * </table>
 */
void i2c_dma_rx(u8 addr, u8 *data, u8 len)
{
	len = (len)?len:1;
	len = (len>16)?16:len;      // �������ƣ�1-16
	i2c_dma_delay_over();       // �ȴ�I2C���
	I2C->ADDR = addr & 0x7f;    // ���豸��ַ
	I2C->SCR = BIT4;          // I2C���䷽��
  I2C->BSIZE = len-1;         // I2C�������ݳ���
  DMA_CH3->DMA_CCR = 0;
	DMA_CH3->DMA_CTMS = 16;     // DMA���˵����ݳ��ȣ�ʵ�ʴ������ݳ���ΪI2C->BSIZE+1,����I2C���ݴ��䳤�ȼ���
	DMA_CH3->DMA_SADR = (u32)&(I2C->DATA);  // DMAԴ��ַ
	DMA_CH3->DMA_DADR = (u32)data;          // DMAĿ�ĵ�ַ
  DMA_CH3->DMA_CCR  = BIT4|BIT1|BIT0;     // ����DMA���䷽��ʹ��DMA
  i2c_dma_state_start();
	I2C->MSCR = 1;								// ����I2C��������
}

/**
 *@brief @b ��������:   void i2c_dma_init(void)
 *@brief @b ��������:   DMAӲ����ʼ��
 *@see���������ݣ�       ��
 *@param���������       ��
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
          i2c_dma_init();//I2C�����DMAģ��Ӳ����ʼ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022��05��21�� <td>1.0     <td>YangZJ     <td>����
 * </table>
 */
void i2c_dma_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;

    DMA_InitStruct.DMA_IRQ_EN       = DISABLE;  /* DMA �ж�ʹ�� */
    DMA_InitStruct.DMA_RMODE        = DISABLE;  /* ���ִ���ʹ�� */
    DMA_InitStruct.DMA_CIRC         = DISABLE;  /* ѭ��ģʽʹ�� */
    DMA_InitStruct.DMA_SINC         = DISABLE;  /* Դ��ַ����ʹ�� */
    DMA_InitStruct.DMA_DINC         = DISABLE;  /* Ŀ�ĵ�ַ����ʹ�� */
    DMA_InitStruct.DMA_SBTW         = 0;        /* Դ��ַ����λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_DBTW         = 0;        /* Ŀ�ĵ�ַ����λ�� 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN       = DMA_I2C_REQ_EN;   /* ͨ�� x Ӳ�� DMA ����ʹ�ܣ�����Ч */
    DMA_InitStruct.DMA_SADR         = 0;        /* DMA ͨ�� x Դ��ַ */
    DMA_InitStruct.DMA_DADR         = 0;        /* DMA ͨ�� x Ŀ�ĵ�ַ */
    
    DMA_Init(DMA_CH3, &DMA_InitStruct);
	  DMA_CHx_EN(DMA_CH3,DISABLE,1);              /* �ر�DMAʹ�ܣ�DMA ͨ�� 1 ���ݰ��˴��� */
    DMA_IF=0xff;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
