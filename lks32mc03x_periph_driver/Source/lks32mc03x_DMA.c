
 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC03x_DMA.c\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>Yangzj      <td>创建
 * </table>
 */
#include "lks32mc03x_DMA.h"
#include "string.h"

 /**
 *@brief @b 函数名称:   void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       DMA_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DMA_InitTypeDef DMA_InitStructure;
		   DMA_StructInit(&DMA_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>Yangzj     <td>创建
 * </table>
 */
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
{
    memset(DMAInitStruct, 0, sizeof(DMA_InitTypeDef));
}

 /**
 *@brief @b 函数名称:   void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA初始化函数
 *@see被引用内容：       无
 *@param输入参数：       DMAx , ADC_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code    
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.DMA_IRQ_EN = DISABLE ;             // DMA 传输完成中断使能
    DMA_InitStruct.DMA_CIRC = DISABLE;                // DMA传输模式：循环模式，高有效 
    DMA_InitStruct.DMA_SINC = ENABLE;                 // 源地址递增,  高有效,地址按照 SBTW 对应大小递增 1/2/4
    DMA_InitStruct.DMA_DINC = DISABLE;                // 目的地址递增,高有效,地址按照 DBTW 对应大小递增 1/2/4
    DMA_InitStruct.DMA_SBTW = DMA_BYTE_TRANS;         // 源访问位宽， 0:byte, 1:half-word, 2:word 
    DMA_InitStruct.DMA_DBTW = DMA_BYTE_TRANS;         // 目的访问位宽， 0:byte, 1:half-word, 2:word 
    DMA_InitStruct.DMA_REQ_EN = DMA_SPI_TX_REQ_EN;    // 通道 UART_TX DMA请求使能，高有效 
    DMA_InitStruct.DMA_RMODE = ENABLE;                // 0:单轮传输，一轮连续传输多次 或 1:多轮，每轮进行一次数据传输 
    DMA_InitStruct.DMA_SADR = (u32)Txaddr;            // DMA 通道 x 源地址 
    DMA_InitStruct.DMA_DADR = (u32)&SPI_TX_DATA;      // DMA 通道 x 目的地址 
    DMA_Init(DMA_CH0, &DMA_InitStruct);

  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年10月14日 <td>1.0     <td>Yangzj       <td>创建
 * </table>
 */
void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
{
    /* 通道配置寄存器 赋值*/
    DMAx->DMA_CCR  = 0;
    DMAx->DMA_SADR = DMAInitStruct->DMA_SADR;   /* 外设地址寄存器 */
    DMAx->DMA_DADR = DMAInitStruct->DMA_DADR;   /* 内存地址寄存器 */
    DMAx->DMA_REN  = DMAInitStruct->DMA_REQ_EN;
    DMAx->DMA_CCR  = (DMAInitStruct -> DMA_SBTW  << 10) | (DMAInitStruct -> DMA_DBTW  <<8) |
                     (DMAInitStruct -> DMA_SINC  <<  6) | (DMAInitStruct -> DMA_DINC  <<4) |
                     (DMAInitStruct -> DMA_CIRC  <<  3) | (DMAInitStruct -> DMA_RMODE <<1);
      
    if(DMAInitStruct->DMA_IRQ_EN)
    switch((u32)DMAx)
    {
        case (u32)DMA_CH0:
            DMA_IE |= BIT0;
            break;
        case (u32)DMA_CH1:
            DMA_IE |= BIT1;
            break;
        case (u32)DMA_CH2:
            DMA_IE |= BIT2;
            break;
        case (u32)DMA_CH3:
            DMA_IE |= BIT3;
            break;
    }
    DMA_CTRL  = 0x0001;  /*DMA整体使能*/
}  

/**
 *@brief @b 函数名称:   void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN,u32 set)
 *@brief @b 功能描述:   使能DMA通道
 *@see被引用内容：       DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param输入参数：       DMAx：DMA通道选择 \n 
                        Channel_EN：ENABLE：使能DMA通道，DISABLE：关闭DMA通道使能 \n
                        set: DMA通道 x 数据搬运轮数或次数1~255 \n         
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DMA_CHx_EN(DMA_CH0,ENABLE,1);//使能DMA通道0
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月13日 <td>1.1       <td>HuangMG    <td>创建
 * </table>
 */
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN,u32 set)
{
	 DMAx->DMA_CCR  &= ~BIT0; /*关闭通道使能*/
	 DMAx->DMA_CTMS = set;    /*配置DMA搬运轮数或次数*/
   if(Channel_EN)
	 {
	   DMAx->DMA_CCR  |= BIT0;/*使能DMA搬运*/
	 }
}


/**
 *@brief @b 函数名称:   uint32_t DMA_GetIRQFlag(u32 timer_if)
 *@brief @b 功能描述:   获取DMA中断标志
 *@see被引用内容：       无
 *@param输入参数：      timer_if参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                        <tr><th> CH3_FIF    <td>DMA通道 3 完成中断标志
 *					    <tr><th> CH2_FIF    <td>DMA通道 2 完成中断标志
 *						<tr><th> CH1_FIF	<td>DMA通道 1 完成中断标志
 *						<tr><th> CH0_FIF    <td>DMA通道 0 完成中断标志
 * </table>  
 *@see 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0   
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(CH0_FIF))//获取DMA通道0完成中断标志
		   {	
		   }
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2022年4月13日 <td>1.0      <td>HuangMG    <td>修改
 * </table>
 */
uint32_t DMA_GetIRQFlag(u32 timer_if)
{
   if(DMA_IF & timer_if && DMA_IE)
	 {
	   return 1;
	 }
	 return 0;
}



/**
 *@brief @b 函数名称:   void DMA_ClearIRQFlag(uint32_t tempFlag)
 *@brief @b 功能描述:   清除DMA中断标志
 *@see 被引用内容：     
 *@param 输入参数：      DMAx：DMA通道选择  \n 
                        tempFlag参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                       <tr><th> CH3_FIF    <td>DMA通道 3 完成中断标志
 *					    <tr><th> CH2_FIF    <td>DMA通道 2 完成中断标志
 *						<tr><th> CH1_FIF	<td>DMA通道 1 完成中断标志
 *						<tr><th> CH0_FIF    <td>DMA通道 0 完成中断标志
 * </table>   
 * 
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(CH0_FIF))//获取DMA通道0完成中断标志
		   {	
			  DMA_ClearIRQFlag(CH0_FIF)//清除DMA通道0完成中断标志
		   }
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2022年4月13日   <td>1.0      <td>HuangMG      <td>创建
 * </table>
 */
void DMA_ClearIRQFlag(uint32_t tempFlag)
{
	  DMA_IF = tempFlag;
}



