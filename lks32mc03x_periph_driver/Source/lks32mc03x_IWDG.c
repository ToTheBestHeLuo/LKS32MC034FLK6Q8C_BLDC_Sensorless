 /**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc03x_IWDG.c\n
 * 文件标识： 无 \n
 * 内容摘要： IWDG外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */

#include "lks32mc03x_iwdg.h"
#include "basic.h"

/**
 *@brief @b 函数名称:   void IWDG_Init(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
            IWDG_InitTypeDef IWDG_InitStruct;
            IWDG_StrutInit(&IWDG_InitStruct);
            IWDG_InitStruct.WDG_EN  = ENABLE;      //使能看门狗
            IWDG_InitStruct.RTH     = SECOND2IWDGCNT(2.0);//设置看门狗
            IWDG_InitStruct.DWK_EN  = DISABLE;     // 深度休眠定时唤醒关闭   
            IWDG_InitStruct.WTH     = 0;           // 看门狗定时唤醒时间（21位计数器，但低12恒位0）
            IWDG_Init(&IWDG_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月10日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_Init(IWDG_InitTypeDef *this)
{
    this->RTH = (this->RTH > BIT21) ? BIT21 - 1 : this->RTH;
    this->WTH = (this->WTH > BIT21) ? BIT21 - 1 : this->WTH;
    IWDG->CFG = (this->DWK_EN<<4) | (this ->WDG_EN);
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->RTH = this->RTH;
    if(this->RTH > this->WTH)
    {
        IWDG->WTH = this->RTH-this->WTH;
    }
    else
    {
        IWDG->WTH = 0x001000;
    }
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}

/**
 *@brief @b 函数名称:   void IWDG_StrutInit(IWDG_InitTypeDef *this)
 *@brief @b 功能描述:   看门狗配置结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       IWDG_InitTypeDef *this 看门狗配置结构体
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_InitTypeDef IWDG_InitStruct;
                IWDG_StrutInit(&IWDG_InitStruct);    //初始化结构体
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_StrutInit(IWDG_InitTypeDef *this)
{
    this->DWK_EN = DISABLE;             // 深度休眠定时唤醒使能
    this->WDG_EN = DISABLE;             // 独立看门狗使能
    this->WTH = SECOND2IWDGCNT(1);      // 看门狗定时唤醒时间,大于复位时间后无效
    this->RTH = SECOND2IWDGCNT(2);      // 看门狗超时复位时间（21位计数器，但低12恒位0）
                                        // SECOND2IWDGCNT输入参数，秒
}

/**
 *@brief @b 函数名称:   void IWDG_DISABLE(void)
 *@brief @b 功能描述:   关闭看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_DISABLE();    //关闭看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_DISABLE(void)
{
    IWDG->CFG = 0x3c00;
}

/**
 *@brief @b 函数名称:   void IWDG_ENABLE(void)
 *@brief @b 功能描述:   打开看门狗模块
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_ENABLE();    //打开看门狗模块
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_ENABLE(void)
{
    IWDG->CFG = 0x1;
}

/**
 *@brief @b 函数名称:   void IWDG_Feed(void)
 *@brief @b 功能描述:   看门狗喂狗
 *@see被引用内容：       无
 *@param输入参数：       无
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
                IWDG_Feed();    //看门狗喂狗
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2021年11月09日 <td>1.0     <td>YangZJ      <td>创建
 * </table>
 */
void IWDG_Feed(void)
{
    IWDG->PSW = PSW_IWDG_PRE;
    IWDG->CLR = PSW_IWDG_CLR;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
