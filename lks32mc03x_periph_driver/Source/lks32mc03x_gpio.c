 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_gpio.c\n
 * 文件标识： 无 \n
 * 内容摘要： GPIO外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>Yangzj       <td>创建
 * </table>
 */
#include "lks32mc03x_gpio.h"

 /**
 *@brief @b 函数名称:   void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
 *@brief @b 功能描述:   GPIO初始化函数
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_InitStruct: GPIO初始化结构体
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			GPIO_InitTypeDef GPIO_InitStruct;
            //P2.11输入模式
            GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; //GPIO输入模式
            GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIO2, &GPIO_InitStruct);
            //P0.2输出模式    
            GPIO_StructInit(&GPIO_InitStruct);         //初始化结构体
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
            GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_Init(GPIO0, &GPIO_InitStruct);
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0        <td>YangZJ         <td>创建
 * </table>
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, tempreg = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
        if (currentpin == pos)
        {
            if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
            {
                tempreg = GPIOx->PIE; /*使能输入*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
            {
                tempreg = GPIOx->PIE; /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*使能输出*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_ANA)
            {
							  tempreg = GPIOx->PIE; /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;
							
                tempreg = GPIOx->POE; /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IO)
            {
                tempreg = GPIOx->PIE; /*使能输入*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->PIE = tempreg;
							
                tempreg = GPIOx->POE; /*使能输出*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }

            if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
            {
                tempreg = GPIOx->PUE;
                tempreg |= (BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            else if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_NOPULL)
            {
                tempreg = GPIOx->PUE;
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            tempreg = GPIOx->PODE;
            if (GPIO_InitStruct->GPIO_PODEna == (uint32_t)ENABLE)
            {
                tempreg |= (BIT0 << pinpos);
            }
            else
            {
                tempreg &= ~(BIT0 << pinpos);
            }
            GPIOx->PODE = tempreg;
        }
    }
}

 /**
 *@brief @b 函数名称:   void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
 *@brief @b 功能描述:   GPIO结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIO_InitStruct: GPIO初始化结构体
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			GPIO_InitTypeDef GPIO_InitStruct;
            GPIO_StructInit(&GPIO_InitStruct);        //初始化结构体
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin    = GPIO_Pin_NONE;
    GPIO_InitStruct->GPIO_Mode   = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_PuPd   = GPIO_PuPd_NOPULL;
    GPIO_InitStruct->GPIO_PODEna = DISABLE;
}

 /**
 *@brief @b 函数名称:   uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   读取GPIO的指定Pin的输入值
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     指定Pin输入数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_IN_VALUE = 0;
            GPIO_IN_VALUE = GPIO_ReadInputDataBit(GPIO0,GPIO_Pin_0);//读取P0.0输入电平 1为高电平，0为低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDI & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

 /**
 *@brief @b 函数名称:   uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
 *@brief @b 功能描述:   读取GPIO的输入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1）
 *@param输出参数：      无
 *@return返 回 值：     输入数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_IN_VALUE = 0;
            GPIO_IN_VALUE = GPIO_ReadInputData(GPIO0);//读取P0.0~P0.15输入电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDI;
}

 /**
 *@brief @b 函数名称:   uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   读取GPIO的指定Pin的输出值
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_Pin:指定的Pin（GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     指定IO输出数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_OUT_VALUE = 0;
            GPIO_OUT_VALUE = GPIO_ReadOutputDataBit(GPIO0,GPIO_Pin_0);//读取P0.0输出电平 1为高电平，0为低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDO & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

 /**
 *@brief @b 函数名称:   uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
 *@brief @b 功能描述:   读取GPIO的输出数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1）
 *@param输出参数：      无
 *@return返 回 值：     输出数据
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
			u8 GPIO_OUT_VALUE = 0;
            GPIO_OUT_VALUE = GPIO_ReadOutputData(GPIO0);//读取P0.0~P0.15输出电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDO;
}

 /**
 *@brief @b 函数名称:   void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO指定Pin置1
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_SetBits(GPIO0,GPIO_Pin_0);//P0.0输出高电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR = GPIO_Pin;
}

 /**
 *@brief @b 函数名称:   void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 *@brief @b 功能描述:   GPIO指定Pin置0
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_ResetBits(GPIO0,GPIO_Pin_0);//P0.0输出低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR = GPIO_Pin;
}

 /**
 *@brief @b 函数名称:   void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
 *@brief @b 功能描述:   向GPIO指定的Pin写入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        GPIO_Pin:指定的Pin （GPIO_Pin_0~GPIO_Pin_15） \n
                        BitVal:写入的Bit值 （Bit_RESET 或 Bit_SET）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_WriteBit(GPIO0,GPIO_Pin_0,Bit_RESET);//P0.0输出低电平
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin;
    }
}

 /**
 *@brief @b 函数名称:   void GPIO_Write(GPIO_TypeDef* GPIOx, uint32_t Val)
 *@brief @b 功能描述:   向GPIO写入数据
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
                        BitVal:写入的Bit值 （0x00~0xffff）
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
            GPIO_WriteBit(GPIO0,0x01);//P0.0置1,输出高电平，P0.1~P0.15值不变保持上一时刻状态
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val)
{
    GPIOx->PDO = Val;
}

 /**
 *@brief @b 函数名称:   void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF)
 *@brief @b 功能描述:   GPIO复用功能选择
 *@see被引用内容：       无
 *@param输入参数：       
 *                      GPIOx:GPIO对象,参数可选（GPIO0~GPIO1） \n
 *                      GPIO_PadSource:指定的PadSource （GPIO_PinSource_0~GPIO_PinSource_15） \n
 *                      GPIO_AF:指定复用功能 \n
 * 
 * <table>              <tr><td>复用功能名称              <td> 说明                  
 * 						<tr><th>AF0_GPIO                 <td>模拟功能
 * 						<tr><th>AF1_CMP                  <td>比较器结果输出或时钟输出功能
 * 						<tr><th>AF2_HALL                 <td>HALL功能
 * 						<tr><th>AF3_MCPWM                <td>MCPWM功能：通道信号输出或停机信号输入
 * 						<tr><th>AF4_UART                 <td>UART功能
 * 						<tr><th>AF5_SPI                  <td>SPI功能，SPI时钟、片选、数据输出、数据输入 
 * 						<tr><th>AF6_I2C                  <td>I2C功能，I2C时钟、I2C数据 
 * 						<tr><th>AF7_TIMER0               <td>Timer0功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 
 * 						<tr><th>AF8_TIMER1               <td>Timer1功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 
 * 						<tr><th>AF9_ADC_TRIGGER          <td>ADC采样触发信号输出，每发生一次ADC采样，ADC_TRIGGER信号反转一次 
 * </table>                         
 *              
 *@param 输出参数：      无
 *@return 返 回 值：     无
 *@note 其它说明：       无
 *@warning              无
 *@par 示例代码：
 *@code    
            GPIO_PinAFConfig(GPIO1,GPIO_Pin_0，AF4_UART);//P1.0复用为串口功能
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日  <td>1.0       <td>YangZJ          <td>创建
 * </table>
 */
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF)
{
    uint32_t temp;
    switch (GPIO_PinSource)
    {
    /*F3210*/
    case 0:
    {
        temp = GPIOx->F3210 & 0xFFF0;  /*get F321*/
        GPIOx->F3210 = temp + GPIO_AF; /*F321 + F0*/
        break;
    }
    case 1:
    {
        temp = GPIOx->F3210 & 0xFF0F;
        GPIOx->F3210 = temp + (GPIO_AF << 4);
        break;
    }
    case 2:
    { /* 2020.8.13 Repair bug HL */
        temp = GPIOx->F3210 & 0xF0FF;
        GPIOx->F3210 = temp + (GPIO_AF << 8);
        break;
    }
    case 3:
    {
        temp = GPIOx->F3210 & 0x0FFF;
        GPIOx->F3210 = temp + (GPIO_AF << 12);
        break;
    }
    /*F7654*/
    case 4:
    {
        temp = GPIOx->F7654 & 0xFFF0;
        GPIOx->F7654 = temp + GPIO_AF;
        break;
    }
    case 5:
    {
        temp = GPIOx->F7654 & 0xFF0F;
        GPIOx->F7654 = temp + (GPIO_AF << 4);
        break;
    }
    case 6:
    {
        temp = GPIOx->F7654 & 0xF0FF;
        GPIOx->F7654 = temp + (GPIO_AF << 8);
        break;
    }
    case 7:
    {
        temp = GPIOx->F7654 & 0x0FFF;
        GPIOx->F7654 = temp + (GPIO_AF << 12);
        break;
    }
    /*FBA98*/
    case 8:
    {
        temp = GPIOx->FBA98 & 0xFFF0;
        GPIOx->FBA98 = temp + GPIO_AF;
        break;
    }
    case 9:
    {
        temp = GPIOx->FBA98 & 0xFF0F;
        GPIOx->FBA98 = temp + (GPIO_AF << 4);
        break;
    }
    case 10:
    {
        temp = GPIOx->FBA98 & 0xF0FF;
        GPIOx->FBA98 = temp + (GPIO_AF << 8);
        break;
    }
    case 11:
    {
        temp = GPIOx->FBA98 & 0x0FFF;
        GPIOx->FBA98 = temp + (GPIO_AF << 12);
        break;
    }
    /*FFEDC*/
    case 12:
    {
        temp = GPIOx->FFEDC & 0xFFF0;
        GPIOx->FFEDC = temp + GPIO_AF;
        break;
    }
    case 13:
    {
        temp = GPIOx->FFEDC & 0xFF0F;
        GPIOx->FFEDC = temp + (GPIO_AF << 4);
        break;
    }
    case 14:
    {
        temp = GPIOx->FFEDC & 0xF0FF;
        GPIOx->FFEDC = temp + (GPIO_AF << 8);
        break;
    }
    case 15:
    {
        temp = GPIOx->FFEDC & 0x0FFF;
        GPIOx->FFEDC = temp + (GPIO_AF << 12);
        break;
    }
    default:
        break;
    }
}

 /**
 *@brief @b 函数名称:   void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
 *@brief @b 功能描述:   GPIO外部触发极性选择
 *@see被引用内容：       EXTIMode_TypeDef
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0~GPIO1) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15) \n
                        EXTI_Trigger:指定的触发极性 @see EXTI_Trigger参数来源：EXTIMode_TypeDef
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		EXTI_Trigger_Config(GPIO0,GPIO_PinSource_0,EXTI_Trigger_Negedge);//P0.0信号下降沿触发外部中断事件
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
{
    if(GPIOx == GPIO0)
    {
        switch (GPIO_PinSource)
        {
            case 0:
                EXTI->CR0 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger);
                break;
            case 2:
                EXTI->CR0 = (EXTI->CR0 & 0xfff3) | (EXTI_Trigger << 2);
                break;
            case 4:
                EXTI->CR0 = (EXTI->CR0 & 0xffcf) | (EXTI_Trigger << 4);
                break;
            case 5:
                EXTI->CR0 = (EXTI->CR0 & 0xff3f) | (EXTI_Trigger << 6);
                break;
            case 6:
                EXTI->CR0 = (EXTI->CR0 & 0xfcff) | (EXTI_Trigger << 8);
                break;
            case 7:
                EXTI->CR0 = (EXTI->CR0 & 0xf3ff) | (EXTI_Trigger << 10);
                break;
            case 8:
                EXTI->CR0 = (EXTI->CR0 & 0xcfff) | (EXTI_Trigger << 12);
                break;
            case 9:
                EXTI->CR0 = (EXTI->CR0 & 0x3fff) | (EXTI_Trigger << 14);
                break;
            case 14:
                EXTI->CR1 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger);
                break;
            case 15:
                EXTI->CR1 = (EXTI->CR0 & 0xfff3) | (EXTI_Trigger << 2);
                break;
            default:break;

        }
    }
    if(GPIOx == GPIO1)
    {
        switch (GPIO_PinSource)
        {
            case 4:
                EXTI->CR1 = (EXTI->CR0 & 0xffcf) | (EXTI_Trigger << 4);
                break;
            case 5:
                EXTI->CR1 = (EXTI->CR0 & 0xff3f) | (EXTI_Trigger << 6);
                break;
            case 6:
                EXTI->CR1 = (EXTI->CR0 & 0xfcff) | (EXTI_Trigger << 8);
                break;
            case 7:
                EXTI->CR1 = (EXTI->CR0 & 0xf3ff) | (EXTI_Trigger << 10);
                break;
            case 8:
                EXTI->CR1 = (EXTI->CR0 & 0xcfff) | (EXTI_Trigger << 12);
                break;
            case 9:
                EXTI->CR1 = (EXTI->CR0 & 0x3fff) | (EXTI_Trigger << 14);
                break;
            default:break;
        }
    }
    if(EXTI->CR1 || EXTI->CR0)
    {
        EXTI->IE = 3;
    }
}

 /**
 *@brief @b 函数名称:   u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   读取外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0~GPIO1) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     中断标志，高有效
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
        }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月21日 <td>1.0       <td>YangZJ        <td>创建
 * </table>
 */
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    u16 gpio0_if_def[16] = {BIT0,0,BIT1,0,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7,0,0,0,0,BIT8,BIT9};
    u16 gpio1_if_def[16] = {0,0,0,0,BIT10,BIT11,BIT12,BIT13,BIT14,BIT15,0,0,0,0,0,0};
    if(GPIO_PinSource>=16)
    {
        return 0;
    }
    if(GPIOx == GPIO0)
    {
        if(EXTI_IF & gpio0_if_def[GPIO_PinSource])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if(GPIOx == GPIO1)
    {
        if(EXTI_IF & gpio1_if_def[GPIO_PinSource])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

 /**
 *@brief @b 函数名称:   void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
 *@brief @b 功能描述:   清除外部中断标志位
 *@see被引用内容：       无
 *@param输入参数：       
                        GPIOx:GPIO对象可选(GPIO0~GPIO1) \n
                        GPIO_PadSource:指定的PadSource可选(GPIO_PinSource_0~GPIO_PinSource_15)
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code    
		if(EXTI_GetIRQFlag(GPIO0,GPIO_PinSource_0))//获取P0.0外部中断标志位
        {
            EXTI_ClearIRQFlag(GPIO0,GPIO_PinSource_0);//清除P0.0外部中断标志位
        }
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2022年04月11日 <td>1.0       <td>HuangMG        <td>创建
 * </table>
 */
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource)
{
    u16 gpio0_if_def[16] = {BIT0,0,BIT1,0,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7,0,0,0,0,BIT8,BIT9};
    u16 gpio1_if_def[16] = {0,0,0,0,BIT10,BIT11,BIT12,BIT13,BIT14,BIT15,0,0,0,0,0,0};
    if(GPIOx == GPIO0)
    {
        EXTI_IF = gpio0_if_def[GPIO_PinSource];
    }
    if(GPIOx == GPIO1)
    {
        EXTI_IF = gpio1_if_def[GPIO_PinSource];
    }
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
