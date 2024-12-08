/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-12-05 16:48:35
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-12-06 16:28:04
 * @FilePath: \undefinedd:\LKS\LKS32MC034FLK6Q8C_BLDC\protocol\source\protocol.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "..\include\protocol.h"

ProtocolHandler protocolHandler = {
	.status = eProtocol_Sys_Reset
};

/*******************************************************************************
 函数名称：    static uint16_t dShot_CalculateWithCRC(uint16_t value,uint8_t checkBit)
 功能描述：    计算需要发送或者接收到的dShot的校验码
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static uint16_t dShot_CalculateWithCRC(uint16_t value,uint8_t checkBit)
{
    uint16_t pack = (value << 1) | (checkBit ? 1 : 0);
    uint16_t sum = 0,tmp = pack;
    for(int i = 0;i < 3;i++){
        sum ^= tmp;tmp >>= 4;
    }
    pack = (pack << 4) | (sum & 0xf);
    return pack;
}
/*******************************************************************************
 函数名称：    static void dShot_ValueEncode(uint16_t value,uint8_t checkBit)
 功能描述：    dShot专用的编码函数，目前只能发送dShot600
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void dShot_ValueEncode(uint16_t value,uint8_t checkBit)
{
    value = (value > 2047) ? 2047 : value;
    value = dShot_CalculateWithCRC(value,checkBit);
    for(int i = 0;i < 16;i++){
        protocolHandler.dShotTransmitBuffer[i] = (value & 0x8000) ? dShot_Logical1_DMA_Value : dShot_Logical0_DMA_Value;
        value <<= 1;
    }
		protocolHandler.dShotTransmitBuffer[16] = protocolHandler.dShotTransmitBuffer[17] = 0;
}
/*******************************************************************************
 函数名称：    static void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
 功能描述：    dShot专用的DMA发送函数
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
{
    dShot_ValueEncode(value,checkBit);
//    void dShot_TransmitValueWithDMA(void){}; /*暂未实现*/
}
/*******************************************************************************
 函数名称：    static uint16_t dShot_ReceiveValueWithDMA(void)
 功能描述：    dShot专用的DMA接收函数
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    使用GPIO口进行dShot数据读取，读取位置位于16位信号的每一位的中间点
 *******************************************************************************/
static uint16_t dShot_ReceiveValueWithDMA(void)
{
    uint16_t value = 0x0000;
    uint16_t realData = 0x0000;

		for(int i = 0;i < 16;i++){
				realData <<= 1;
				realData |= ((protocolHandler.dShotReceiveBuffer[i] & 0x0008) >> 3);
		}

		uint8_t checkBit = realData & 0x10;
		value = realData >> 5;

		if(dShot_CalculateWithCRC(value,checkBit) != realData) return 0x0000;
        
    return value;
}
/*******************************************************************************
 函数名称：    static void dShot600AnalysisFunction(void)
 功能描述：    dShot600的解析函数
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void dShot600AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}
/*******************************************************************************
 函数名称：    static void dShot600AnalysisFunction(void)
 功能描述：    dShot300的解析函数
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void dShot300AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}
/*******************************************************************************
 函数名称：    static void dShot600AnalysisFunction(void)
 功能描述：    dShot150的解析函数
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
static void dShot150AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}

/*不同协议的解析，使用跳转表的形式来实现*/
void (*protocolAnalysisFunc[])(void) = {
		dShot600AnalysisFunction,
		dShot300AnalysisFunction,
		dShot150AnalysisFunction
};

/*******************************************************************************
 函数名称：    void protocol_Reset(void)
 功能描述：    协议的复位函数，主要负责一些变量的初始化
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 *******************************************************************************/
void protocol_Reset(void)
{
		protocolHandler.status = eProtocol_Sys_Reset;
		protocolHandler.type = eProtocol_Type_Unkown;
		protocolHandler.signalPulseWidth = 0u;
		protocolHandler.signalFrameCounter = 0u;
		protocolHandler.dShotReceiveSamplingPoint = dShot600_SamplingPoint;
}
/*******************************************************************************
 函数名称：    void protocol_PollingTask(void)
 功能描述：    负责协议处理的任务
 输入参数：    无         
 输出参数：    无
 返 回 值：    无
 其它说明：    这个函数应由main函数的死循环进行调用
 *******************************************************************************/
void protocol_PollingTask(void)
{
		ProtocolStatus status = protocolHandler.status;
		switch(status){
			case eProtocol_Sys_Reset:
				protocol_Reset();
				protocolHandler.status = eProtocol_Sys_TypeCheck;
				break;
			case eProtocol_Sys_TypeCheck:
				if(protocolHandler.signalFrameCounter == 2){
					if(protocolHandler.signalPulseWidth > dShot600_MinPulseWidth && protocolHandler.signalPulseWidth < dShot600_MaxPulseWidth){
						protocolHandler.dShotReceiveSamplingPoint = dShot600_SamplingPoint;
						protocolHandler.type = eProtocol_Type_dShot600;
						protocolHandler.status = eProtocol_Sys_Polling;
					}else if(protocolHandler.signalPulseWidth > dShot300_MinPulseWidth && protocolHandler.signalPulseWidth < dShot300_MaxPulseWidth){
						protocolHandler.dShotReceiveSamplingPoint = dShot300_SamplingPoint;
						protocolHandler.type = eProtocol_Type_dShot300;
						protocolHandler.status = eProtocol_Sys_Polling;						
					}else if(protocolHandler.signalPulseWidth > dShot150_MinPulseWidth && protocolHandler.signalPulseWidth < dShot150_MaxPulseWidth){
						protocolHandler.dShotReceiveSamplingPoint = dShot150_SamplingPoint;
						protocolHandler.type = eProtocol_Type_dShot150;
						protocolHandler.status = eProtocol_Sys_Polling;						
					}else{
						protocolHandler.status = eProtocol_Sys_Reset;
					}
				}
				break;
			case eProtocol_Sys_Polling:
				break;
			default:
				while(1);
		}
}

