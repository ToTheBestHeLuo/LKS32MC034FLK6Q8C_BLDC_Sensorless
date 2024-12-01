 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief �ļ����ƣ� lks32mc03x_spi.c\n
 * �ļ���ʶ�� �� \n
 * ����ժҪ�� SPI����ͷ�ļ� \n
 * ����˵���� �� \n
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021��11��10�� <td>1.0     <td>Yangzj       <td>����
 * </table>
 */
#include "lks32mc03x_spi.h"

/**
 *@brief @b ��������:   void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
 *@brief @b ��������:   SPI��ʼ������
 *@see���������ݣ�       SYS_ModuleClockCmd()
 *@param���������       SPIx��SPI , SPI_InitTypeDef *SPI_InitStruct
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code           
            SPI_InitTypeDef SPI_InitStruct;
            SPI_StructInit(&SPI_InitStruct);              //SPI�ṹ���ʼ��
            SPI_InitStruct.Duplex = SPI_Full;             //˫��ģʽ����
            SPI_InitStruct.Mode = SPI_Master;             //master����ģʽ
            SPI_InitStruct.EN = ENABLE;                   //ʹ��SPIģ��
            SPI_InitStruct.TRANS_MODE = SPI_MCU_CARRY;    //ѡ��SPI���Ʒ�ʽ����MCU�������ݵ�SPI
            SPI_InitStruct.TRANS_TRIG = 0;                //�ڲ��Զ���������
            SPI_InitStruct.ENDIAN = SPI_FIRSTSEND_MSB;    //���ֽ��ȷ��� MSB
            SPI_InitStruct.CPHA = 0;                      //��һ����Ϊ��������ʱ��
            SPI_InitStruct.CPOL = 0;                      //CLKĬ�ϸߵ�ƽ
            SPI_InitStruct.BAUD = 31;                     //�����ٶ�96MHZ/(2*(31+1))= 1.548MHZ
            SPI_InitStruct.BITSIZE = 0x08;                //��������ֽ�
            SPI_InitStruct.IRQEna = DISABLE;              //�ر�SPI���ж�
            SPI_Init(SPI, &SPI_InitStruct);               //SPI��ʼ������
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0        <td>YangZJ          <td>����
 * </table>
 */

void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_SPI, ENABLE);
    SPIx->CFG = 0;
    SPIx->IE   =   (SPI_InitStruct->TRANS_TRIG << 3) | (SPI_InitStruct->IRQEna );
    SPIx->BAUD =   (SPI_InitStruct->BAUD)            | (SPI_InitStruct->TRANS_MODE << 7);
    SPIx->SIZE =   SPI_InitStruct->BITSIZE;
    SPIx->CFG  =   (SPI_InitStruct->EN)              | (SPI_InitStruct->ENDIAN     << 1) |
                   (SPI_InitStruct->CPOL       << 2) | (SPI_InitStruct->CPHA       << 3) |
                   (SPI_InitStruct->Mode       << 4) | (SPI_InitStruct->CS         << 5) |
                   (SPI_InitStruct->Duplex     << 6);

}

/**
 *@brief @b ��������:   void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
 *@brief @b ��������:   SPI�ṹ���ʼ��
 *@param���������       SPI_InitTypeDef *SPI_InitStruct
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			SPI_InitTypeDef SPI_InitStruct;
            SPI_StructInit(&SPI_InitStruct);              //SPI�ṹ���ʼ��
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0       <td>YangZJ          <td>����
 * </table>
 */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{

    SPI_InitStruct -> Duplex     = SPI_Full;
    SPI_InitStruct -> CS         = 0;
    SPI_InitStruct -> Mode       = SPI_Slave;
    SPI_InitStruct -> CPOL       = 0;
    SPI_InitStruct -> CPHA       = 0;
    SPI_InitStruct -> ENDIAN     = 0;
    SPI_InitStruct -> EN         = 0;
                      
    SPI_InitStruct -> IRQEna     = DISABLE;
    SPI_InitStruct -> TRANS_TRIG = 0;
                      
    SPI_InitStruct -> TRANS_MODE = 0;
    SPI_InitStruct -> BAUD       = 3;
                      
    SPI_InitStruct -> BITSIZE    = 0; 
}

/**
 *@brief @b ��������:   void SPI_SendData(SPI_TypeDef *SPIx, uint8_t n)
 *@brief @b ��������:   SPI��������
 *@see���������ݣ�       ��
 *@param���������       SPIx��SPI , n������һ�ֽ�����
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
			SPI_SendData(SPI,0x12);  //SPI����0x12һ�ֽ�����
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0        <td>YangZJ          <td>����
 * </table>
 */
void SPI_SendData(SPI_TypeDef *SPIx, uint8_t n)
{
	if((SPIx->CFG&(1<<5)) ==1)
	{
    SPIx->TX_DATA = n;
	}
	else
	{
	}
}

/**
 *@brief @b ��������:   uint8_t SPI_ReadData(SPI_TypeDef *SPIx)
 *@brief @b ��������:   SPI������������
 *@see���������ݣ�       ��
 *@param���������       SPI_TypeDef *SPIx
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
            u8 SPI_RXValue = 0;
			SPI_RXValue = SPI_ReadData(SPI);  //SPI����һ�ֽ�����
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021��11��10�� <td>1.0       <td>YangZJ          <td>����
 * </table>
 */
uint8_t SPI_ReadData(SPI_TypeDef *SPIx)
{
    return SPIx->RX_DATA;
}

/**
 *@brief @b ��������:   uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 *@brief @b ��������:   ��ȡSPI�жϱ�־λ
 *@see���������ݣ�       ��
 *@param���������       SPIx��SPI
                        IRQ_Flag��
 * <table>              <tr><th>SPI_IF_TranDone       <td>��������жϱ�־λ \n
 * 						<tr><th>SPI_IF_SSErr          <td>�����쳣�жϱ�־λ \n
 * 						<tr><th>SPI_IF_DataOver       <td>��������жϱ�־λ \n
 * </table>                       
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ֻ�ж�Ӧ�ж�ʹ�ܺ󣬸�Ϊ���ܶ�ȡ�������Ӧ�ж�δʹ�ܣ���ȡ���һֱΪ0
 *@par ʾ�����룺
 *@code
            if(SPI_GetIRQFlag(SPI,SPI_IF_TranDone))//��ȡ��������жϱ�־λ
            {
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��20�� <td>1.0       <td>Zhu Jie       <td>����
 * </table>
 */
uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
{
    u8 SPI_IRQFlag = 0;
	  if(SPIx->IE & IRQ_Flag)
		{
		    SPI_IRQFlag = 1;
		}
		else
		{
		    SPI_IRQFlag = 0;
		}
    return SPI_IRQFlag;
}

/**
 *@brief @b ��������:   void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 *@brief @b ��������:   ���SPI�жϱ�־λ
 *@see���������ݣ�       ��
 *@param���������       SPIx��SPI
                        IRQ_Flag��
 * <table>              <tr><th>SPI_IF_TranDone       <td>��������жϱ�־λ \n
 * 						<tr><th>SPI_IF_SSErr          <td>�����쳣�жϱ�־λ \n
 * 						<tr><th>SPI_IF_DataOver       <td>��������жϱ�־λ \n
 * </table>                       
 *@param���������       ��
 *@return�� �� ֵ��      ��
 *@note����˵����        ��
 *@warning              ��
 *@par ʾ�����룺
 *@code
            if(SPI_GetIRQFlag(SPI,SPI_IF_TranDone))//��ȡ��������жϱ�־λ
            {
                SPI_ClearIRQFlag(SPI,SPI_IF_TranDone);//�����������жϱ�־λ
            }
  @endcode
 *@par �޸���־:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022��04��20�� <td>1.0      <td>Zhu Jie        <td>����
 * </table>
 */
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
{
    SPIx->IE |= IRQ_Flag;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
