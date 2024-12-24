#include "..\include\protocol.h"

ProtocolHandler protocolHandler = {
	.status = eProtocol_Sys_Reset
};

/*这是非标准的dShot协议，这里简写为sG协议，11位的油门值[0-2047]中的[0-47]将根据实际情况有不同的功能，第12位为遥测位，最后4位为CRC校验位*/
/*
		
*/

/*******************************************************************************
 函数名称：    static uint16_t sG_CalculateWithCRC(uint16_t value,uint8_t checkBit)
 功能描述：    计算需要发送或者接收到的sG的校验码
 其它说明：    无
 *******************************************************************************/
static uint16_t sG_CalculateWithCRC(uint16_t value,uint8_t checkBit)
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
 函数名称：    static void sG_ValueEncode(uint16_t value,uint8_t checkBit)
 功能描述：    sG专用的编码函数，目前只能发送sG600
 其它说明：    无
 *******************************************************************************/
static void sG_ValueEncode(uint16_t value,uint8_t checkBit)
{
    value = (value > 2047) ? 2047 : value;
    value = sG_CalculateWithCRC(value,checkBit);
    for(int i = 0;i < 16;i++){
        protocolHandler.transmitBuffer[i] = (value & 0x8000) ? sG_Logical1_DMA_Value : sG_Logical0_DMA_Value;
        value <<= 1;
    }
		protocolHandler.transmitBuffer[16] = protocolHandler.transmitBuffer[17] = 0;
}
/*******************************************************************************
 函数名称：    static void sG_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
 功能描述：    sG专用的DMA发送函数
 其它说明：    无
 *******************************************************************************/
static void sG_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
{
    sG_ValueEncode(value,checkBit);
//    void dShot_TransmitValueWithDMA(void){}; /*暂未实现*/
}
/*******************************************************************************
 函数名称：    static uint16_t sG_ReceiveValueWithDMA(void)
 功能描述：    sG专用的DMA接收函数
 其它说明：    使用GPIO口进行sG数据读取，读取位置位于16位信号的每一位的中间点
 *******************************************************************************/
static uint16_t sG_ReceiveValueWithDMA(void)
{
    uint16_t value = 0x0000;
    uint16_t realData = 0x0000;

		for(int i = 0;i < 16;i++){
				realData <<= 1;
				realData |= ((protocolHandler.receiveBuffer[i] & 0x0008) >> 3);
		}

		uint8_t checkBit = realData & 0x10;
		value = realData >> 5;

		if(sG_CalculateWithCRC(value,checkBit) != realData) return 0x0000;
        
    return value;
}
/*******************************************************************************
 函数名称：    static void sG600AnalysisFunction(void)
 功能描述：    sG600的解析函数
 其它说明：    无
 *******************************************************************************/
static void sG600AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}
/*******************************************************************************
 函数名称：    static void sG600AnalysisFunction(void)
 功能描述：    sG300的解析函数
 其它说明：    无
 *******************************************************************************/
static void sG300AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}
/*******************************************************************************
 函数名称：    static void sG600AnalysisFunction(void)
 功能描述：    sG150的解析函数
 其它说明：    无
 *******************************************************************************/
static void sG150AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}

/*不同协议的解析，使用跳转表的形式来实现*/
void (*protocolAnalysisFunc[])(void) = {
		sG600AnalysisFunction,
		sG300AnalysisFunction,
		sG150AnalysisFunction
};

/*******************************************************************************
 函数名称：    void protocol_Reset(void)
 功能描述：    协议的复位函数，主要负责一些变量的初始化
 其它说明：    无
 *******************************************************************************/
void protocol_Reset(void)
{
		protocolHandler.status = eProtocol_Sys_Reset;
		protocolHandler.type = eProtocol_Type_Unkown;
		protocolHandler.signalPulseWidth = 0u;
		protocolHandler.signalFrameCounter = 0u;
		protocolHandler.receiveSamplingPoint = sG600_SamplingPoint;
}
/*******************************************************************************
 函数名称：    void protocol_PollingTask(void)
 功能描述：    负责协议处理的任务
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
					if(protocolHandler.signalPulseWidth > sG600_MinPulseWidth && protocolHandler.signalPulseWidth < sG600_MaxPulseWidth){
						protocolHandler.receiveSamplingPoint = sG600_SamplingPoint;
						protocolHandler.type = eProtocol_Type_sG600;
						protocolHandler.status = eProtocol_Sys_Polling;
					}else if(protocolHandler.signalPulseWidth > sG300_MinPulseWidth && protocolHandler.signalPulseWidth < sG300_MaxPulseWidth){
						protocolHandler.receiveSamplingPoint = sG300_SamplingPoint;
						protocolHandler.type = eProtocol_Type_sG300;
						protocolHandler.status = eProtocol_Sys_Polling;						
					}else if(protocolHandler.signalPulseWidth > sG150_MinPulseWidth && protocolHandler.signalPulseWidth < sG150_MaxPulseWidth){
						protocolHandler.receiveSamplingPoint = sG150_SamplingPoint;
						protocolHandler.type = eProtocol_Type_sG150;
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

