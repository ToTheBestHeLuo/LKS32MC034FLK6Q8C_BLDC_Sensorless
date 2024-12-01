/**
 * @file 
 * @copyright (C)2021, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_uart.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� UART������������ \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
#include "lks32mc03x_uart.h"

/**
 *@brief @b ��������:   void UART_Init(UART_TypeDef* UARTx, EUART_InitTypeDef* UART_InitStruct)
 *@brief @b ��������:   UART��ʼ������
 *@see���������ݣ�      SYS_ModuleClockCmd()
 *@param���������      UART_TypeDef��UART0 , UART_InitTypeDef
 *@param���������      ��
 *@return�� �� ֵ��     ��
 *@note����˵����       ���ڲ����ʼ���ʹ��UART_MCU_MCLKϵͳʱ�ӽ��м��㣬ʹ��ǰ��Ҫȷ��ϵͳʱ��Ƶ��
 *@warning             ��
 *@par ʾ�����룺
 *@code    
         UART_InitTypeDef UART_InitStruct;
         UART_StructInit(&UART_InitStruct);
         UART_InitStruct.BaudRate  = 9600;                // ���ò�����9600 
         UART_InitStruct.WordLength= UART_WORDLENGTH_8b;  // �������ݳ���8λ 
         UART_InitStruct.StopBits  = UART_STOPBITS_1b;    // ֹͣλ����1λ 
         UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;  // �ȷ���LSB 
         UART_InitStruct.ParityMode= UART_Parity_NO;      // ����żУ�� 
         UART_InitStruct.RXD_INV   = DISABLE;             // RXD��ƽ������� 
         UART_InitStruct.TXD_INV   = DISABLE;             // TXD��ƽ�������
         UART_InitStruct.IRQEna    = UART_IRQEna_SendOver | UART_IRQEna_RcvOver;
         UART_Init(UART0, &UART_InitStruct);

  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14��   <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
   uint32_t DIVHDATA;
   uint32_t DIVLDATA;
   uint32_t parity;
   uint32_t parityEna;

   SYS_ModuleClockCmd(SYS_Module_UART, ENABLE);

    DIVHDATA = (u32)(((MCU_MCLK/2)/UART_InitStruct->BaudRate)/256);
	  DIVLDATA = (u32)((MCU_MCLK/2)/UART_InitStruct->BaudRate)-(DIVHDATA*256)-1;

	 SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
   SYS_CLK_DIV2 = 1;
	 SYS_WR_PROTECT = 0;
   UARTx->DIVL = DIVLDATA;
   UARTx->DIVH = DIVHDATA;

   if (UART_InitStruct->ParityMode == UART_Parity_EVEN)
   {
      parityEna = ENABLE;
      parity = 0;
   }
   else if (UART_InitStruct->ParityMode == UART_Parity_ODD)
   {
      parityEna = ENABLE;
      parity = 1;
   }
   else
   {
      parityEna = DISABLE;
      parity = 0;
   }
   UARTx->CTRL = UART_InitStruct->WordLength | (UART_InitStruct->StopBits << 1) | (UART_InitStruct->FirstSend << 2) | (parity << 3) | (parityEna << 4) | (UART_InitStruct->MultiDropEna << 5);

   UARTx->INV = (UART_InitStruct->RXD_INV) | UART_InitStruct->TXD_INV << 1;

   UARTx->ADR = UART_InitStruct->Match485Addr;
   UARTx->RE = UART_InitStruct->DMARE;
   UARTx->IE = UART_InitStruct->IRQEna;
}

/**
 *@brief @b ��������:   void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
 *@brief @b ��������:   UART�ṹ���ʼ������
 *@see���������ݣ�   ��
 *@param���������   UART_InitTypeDef
 *@param���������  ��
 *@return�� �� ֵ�� ��
 *@note����˵����   �� 
 *@warning         �� 
 *@par ʾ�����룺
 *@code    
           UART_InitTypeDef UART_InitStruct;
           UART_StructInit(&UART_InitStruct);  //��ʼ��UART������ýṹ����� 
  @endcode  
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
   UART_InitStruct->BaudRate = 9600;
   UART_InitStruct->WordLength = UART_WORDLENGTH_8b;
   UART_InitStruct->StopBits = UART_STOPBITS_1b;
   UART_InitStruct->FirstSend = UART_FIRSTSEND_LSB;
   UART_InitStruct->ParityMode = UART_Parity_NO;

   UART_InitStruct->MultiDropEna = DISABLE;
   UART_InitStruct->DMARE = DISABLE;

   UART_InitStruct->Match485Addr = 0;
   UART_InitStruct->IRQEna = 0;
   UART_InitStruct->RXD_INV = DISABLE;
   UART_InitStruct->TXD_INV = DISABLE;
	 
}

/**
 *@brief @b ��������:   void UART_SENDDATA(UART_TypeDef *UARTx, uint32_t n)
 *@brief @b ��������:   UART��������
 *@see���������ݣ�   UART0
 *@param���������   UART_TypeDef��UART0�� n��Ҫ����1Byte����
 *@param���������   ��
 *@return�� �� ֵ��  ��
 *@note����˵����    �� 
 *@warning          ��
 *@par ʾ�����룺
 *@code  
           UART_SendData(UART0��0x12);//����0����0x12һ�ֽ�����          
  @endcode      
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void UART_SendData(UART_TypeDef *UARTx, uint32_t n)
{
   UARTx->BUFF = n;
}

/**
 *@brief @b ��������:   uint32_t UART_ReadData(UART_TypeDef *UARTx)
 *@brief @b ��������:   UART������������
 *@see���������ݣ�   UART0 
 *@param���������   UART_TypeDef��UART0
 *@param���������   ��
 *@return�� �� ֵ��  ���ش��ڽ��ջ�������1Byte����
 *@note����˵����    �� 
 *@warning          ��
 *@par ʾ�����룺 
 *@code    
           u8 UART_BUFF = 0;
           UART_BUFF = UART_ReadData(UART0);//��ȡ����0����һ�ֽ�����       
  @endcode    
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
uint32_t UART_ReadData(UART_TypeDef *UARTx)
{
   return UARTx->BUFF;
}

/**
 *@brief @b ��������:   uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n)
 *@brief @b ��������:   ����485ͨѶ����Ҫ�������ݵĴӻ���ַ
 *@see���������ݣ�   UART0
 *@param���������   UART_TypeDef��UART0�� n��Ҫ����1Byte��ַ
 *@param���������   ��
 *@return�� �� ֵ��  1������ʧ�ܣ�0�����ͳɹ�
 *@note����˵����    cnt��������ʱ��ֹ���������ڷ������ݺ��������͵�ַ�������,��
                    �жϵȴ����ͻ��������ڽ��е�ַ���ͣ������ʱ�仹δ������ɣ�cnt����ʱ�䣩��
                    ������whileѭ����������ڲ����ʽϵ�cnt������������������ݻ�δ������ɽ���
                    ��һ�����ݷ��ͣ�Ϊ�˱���������ⷢ�Ϳ�������cntֵ��
 *@warning         ��
 *@par ʾ�����룺
 *@code    
           UART_SendAddr_485(UART0,0x55);//����0����485�ӻ����յ�ַΪ0x55
  @endcode                     
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
uint8_t UART_SendAddr_485(UART_TypeDef *UARTx, uint8_t n)
{
	  uint32_t m = 0x100;
	  uint32_t cnt = 0xffffff;
		m |= n;
		UARTx->BUFF = m;
    while (!(UARTx->STT & BIT0)) /*���ͻ������ǿ�*/
    {
        if (cnt > 0)
        {
            cnt--;
            __nop();
        }
        else
        {
            return 1; /*����ʧ��*/
        }
    }
    return 0; /*���ͳɹ�*/
}

/**
 *@brief @b ��������:   uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n)
 *@brief @b ��������:   ����485ͨѶ�е�������Ϣ
 *@see���������ݣ�   UART0
 *@param���������   UART_TypeDef��UART0�� n��Ҫ����1Byte����
 *@param���������   ��
 *@return�� �� ֵ��  1������ʧ�ܣ�0�����ͳɹ�
 *@note����˵����    cnt��������ʱ��ֹ���������ڷ������ݺ��������͵�ַ�������,��
                    �жϵȴ����ͻ��������ڽ��е�ַ���ͣ������ʱ�仹δ������ɣ�cnt����ʱ�䣩��
                    ������whileѭ����������ڲ����ʽϵ�cnt������������������ݻ�δ������ɽ���
                    ��һ�����ݷ��ͣ�Ϊ�˱���������ⷢ�Ϳ�������cntֵ��
 *@warning          ��
 *@par ʾ�����룺
 *@code    
           UART_SendData_485(UART0,0x12);//����0����485����Ϊ0x12
  @endcode 
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
uint8_t UART_SendData_485(UART_TypeDef *UARTx, uint8_t n)
{
    uint32_t cnt = 0xffffff;
    UARTx->BUFF = n;
    while (!(UARTx->STT & BIT0)) /*���ͻ������ǿ�*/
    {
        if (cnt > 0)
        {
            cnt--;
            __nop();
        }
        else
        {
            return 1; /*����ʧ��*/
        }
    }
    return 0; /*���ͳɹ�*/
}

/**
 *@brief @b ��������:   uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx , uint32_t tempFlag)
 *@brief @b ��������:   ��ȡUART�жϱ�־
 *@see���������ݣ�   UART0
 *@param���������   UART_TypeDef��UART0 \n 
                    tempFlag������ѡ��
 *<table>           <tr><td> �궨��               <td>˵��
                    <tr><th>UART_IF_SendOver     <td>��������ж� 
                    <tr><th>UART_IF_RcvOver      <td>��������ж� 
                    <tr><th>UART_IF_SendBufEmpty <td>���ͻ��������ж� 
                    <tr><th>UART_IF_StopError    <td>ֹͣλ����  
                    <tr><th>UART_IF_CheckError   <td>У����� 
 *</table>               
 *@param���������   ��
 *@return�� �� ֵ��  ��
 *@note����˵����    ��
 *@warning          ֻ�ж�Ӧ�ж�ʹ�ܺ󣬸�Ϊ���ܶ�ȡ�������Ӧ�ж�δʹ�ܣ���ȡ���һֱΪ0
 *@par ʾ�����룺
 *@code    
           if(UART_GetIRQFlag(UART0,UART_IF_SendOver))//��ȡ��������жϱ�־λ
           {
             UART_ClearIRQFlag(UART0,UART_IF_SendOver)//�����������жϱ�־λ
           }
  @endcode 
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx , uint32_t tempFlag)
{
	if((UARTx->IF) & tempFlag & (UARTx->IE))
	{
	  return 1;
	}
	  return 0;
}

/**
 *@brief @b ��������:   void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t nFlag)
 *@brief @b ��������:   ���UART�жϱ�־
 *@see���������ݣ�   UART0
 *@param���������   UART_TypeDef��UART0 \n 
                    tempFlag������ѡ��
 *<table>           <tr><td> �궨��               <td>˵��
                    <tr><th>UART_IF_SendOver     <td>��������ж� 
                    <tr><th>UART_IF_RcvOver      <td>��������ж� 
                    <tr><th>UART_IF_SendBufEmpty <td>���ͻ��������ж� 
                    <tr><th>UART_IF_StopError    <td>ֹͣλ����  
                    <tr><th>UART_IF_CheckError   <td>У����� 
 *</table>              
 *@param���������   ��
 *@return�� �� ֵ��  ��
 *@note����˵����    ��
 *@warning          ��
 *@par ʾ�����룺
 *@code    
           if(UART_GetIRQFlag(UART0,UART_IF_SendOver))//��ȡ��������жϱ�־λ
           {
              UART_ClearIRQFlag(UART0,UART_IF_SendOver)//�����������жϱ�־λ
           }
  @endcode 
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��10��14�� <td>1.0     <td>HuangMG      <td>����
 * </table>
 */
void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag)
{
   UARTx->IF = tempFlag;
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
