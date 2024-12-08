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
 �������ƣ�    static uint16_t dShot_CalculateWithCRC(uint16_t value,uint8_t checkBit)
 ����������    ������Ҫ���ͻ��߽��յ���dShot��У����
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
 �������ƣ�    static void dShot_ValueEncode(uint16_t value,uint8_t checkBit)
 ����������    dShotר�õı��뺯����Ŀǰֻ�ܷ���dShot600
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
 �������ƣ�    static void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
 ����������    dShotר�õ�DMA���ͺ���
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 *******************************************************************************/
static void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
{
    dShot_ValueEncode(value,checkBit);
//    void dShot_TransmitValueWithDMA(void){}; /*��δʵ��*/
}
/*******************************************************************************
 �������ƣ�    static uint16_t dShot_ReceiveValueWithDMA(void)
 ����������    dShotר�õ�DMA���պ���
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ʹ��GPIO�ڽ���dShot���ݶ�ȡ����ȡλ��λ��16λ�źŵ�ÿһλ���м��
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
 �������ƣ�    static void dShot600AnalysisFunction(void)
 ����������    dShot600�Ľ�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 *******************************************************************************/
static void dShot600AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}
/*******************************************************************************
 �������ƣ�    static void dShot600AnalysisFunction(void)
 ����������    dShot300�Ľ�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 *******************************************************************************/
static void dShot300AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}
/*******************************************************************************
 �������ƣ�    static void dShot600AnalysisFunction(void)
 ����������    dShot150�Ľ�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
 *******************************************************************************/
static void dShot150AnalysisFunction(void)
{
		protocolHandler.testData = dShot_ReceiveValueWithDMA();
}

/*��ͬЭ��Ľ�����ʹ����ת�����ʽ��ʵ��*/
void (*protocolAnalysisFunc[])(void) = {
		dShot600AnalysisFunction,
		dShot300AnalysisFunction,
		dShot150AnalysisFunction
};

/*******************************************************************************
 �������ƣ�    void protocol_Reset(void)
 ����������    Э��ĸ�λ��������Ҫ����һЩ�����ĳ�ʼ��
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��
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
 �������ƣ�    void protocol_PollingTask(void)
 ����������    ����Э�鴦�������
 ���������    ��         
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    �������Ӧ��main��������ѭ�����е���
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

