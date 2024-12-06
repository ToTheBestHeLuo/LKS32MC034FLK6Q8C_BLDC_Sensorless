/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-11-23 12:39:01
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-11-28 13:58:56
 * @FilePath: \LKS32MC034FLK6Q8C_BLDC\Kernal_Source\main.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Main.c
 * 文件标识：
 * 内容摘要： 工程主代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： HuangMG 
 * 完成日期： 2022年4月14日
 *
 *
 *******************************************************************************/
#include "lks32mc03x_lib.h"
#include "hardware_init.h"
#include "delay.h"

#include "protocol.h"
/*******************************************************************************
 函数名称：    int main(void)
 功能描述：    主程序入口
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    实验配置MCPWM的CH0,CH1,CH2通道进行手动PWM输出。
							
 
 运行效果：    程序烧录凌鸥LKS32MC033H6P8最小系统板，通过示波器测量MCPWM的CH0都CH2可以
              输出PWM，占空比可变。

修改日期      版本号          修改人            修改内容
-----------------------------------------------------------------------------
 2022/4/14     V1.0          HuangMG             创建
 *******************************************************************************/
int main(void)
{
	Hardware_init(); /* 硬件初始化 */
	
	strPWM_DutyCycleDef  strPWM_DutyCycle;

	strPWM_DutyCycle.th00 = -PWM_PERIOD;
	strPWM_DutyCycle.th01 = -PWM_PERIOD;

	strPWM_DutyCycle.th10 = -PWM_PERIOD;
	strPWM_DutyCycle.th11 = -PWM_PERIOD;

	strPWM_DutyCycle.th20 = -PWM_PERIOD;
	strPWM_DutyCycle.th21 = -PWM_PERIOD;
	

	MCPWM_Update(&strPWM_DutyCycle);
	
//	/*通道3用来触发ADC*/
//	PWMOutputs_CH3(MCPWM0, ENABLE);
	
	/*TIM0使能*/
	TIM_TimerCmd(TIMER0,ENABLE);
	/*TIM1使能*/
	TIM_TimerCmd(TIMER1,ENABLE);
	/*使能三相的PWM输出*/
	PWMOutputs(MCPWM0, ENABLE);
	for (;;)
	{
		protocol_PollingTask();
//		IWDG_Feed();//看门狗喂狗
	}
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
