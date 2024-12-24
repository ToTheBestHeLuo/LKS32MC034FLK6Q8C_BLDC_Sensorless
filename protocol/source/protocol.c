#include "..\include\protocol.h"

ProtocolHandler protocolHandler = {
	.status = eProtocol_Sys_Reset
};

/*���ǷǱ�׼��dShotЭ�飬�����дΪsGЭ�飬11λ������ֵ[0-2047]�е�[0-47]������ʵ������в�ͬ�Ĺ��ܣ���12λΪң��λ�����4λΪCRCУ��λ*/
/*
		
*/

/*******************************************************************************
 �������ƣ�    static uint16_t sG_CalculateWithCRC(uint16_t value,uint8_t checkBit)
 ����������    ������Ҫ���ͻ��߽��յ���sG��У����
 ����˵����    ��
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
 �������ƣ�    static void sG_ValueEncode(uint16_t value,uint8_t checkBit)
 ����������    sGר�õı��뺯����Ŀǰֻ�ܷ���sG600
 ����˵����    ��
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
 �������ƣ�    static void sG_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
 ����������    sGר�õ�DMA���ͺ���
 ����˵����    ��
 *******************************************************************************/
static void sG_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
{
    sG_ValueEncode(value,checkBit);
//    void dShot_TransmitValueWithDMA(void){}; /*��δʵ��*/
}
/*******************************************************************************
 �������ƣ�    static uint16_t sG_ReceiveValueWithDMA(void)
 ����������    sGר�õ�DMA���պ���
 ����˵����    ʹ��GPIO�ڽ���sG���ݶ�ȡ����ȡλ��λ��16λ�źŵ�ÿһλ���м��
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
 �������ƣ�    static void sG600AnalysisFunction(void)
 ����������    sG600�Ľ�������
 ����˵����    ��
 *******************************************************************************/
static void sG600AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}
/*******************************************************************************
 �������ƣ�    static void sG600AnalysisFunction(void)
 ����������    sG300�Ľ�������
 ����˵����    ��
 *******************************************************************************/
static void sG300AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}
/*******************************************************************************
 �������ƣ�    static void sG600AnalysisFunction(void)
 ����������    sG150�Ľ�������
 ����˵����    ��
 *******************************************************************************/
static void sG150AnalysisFunction(void)
{
		protocolHandler.testData = sG_ReceiveValueWithDMA();
}

/*��ͬЭ��Ľ�����ʹ����ת�����ʽ��ʵ��*/
void (*protocolAnalysisFunc[])(void) = {
		sG600AnalysisFunction,
		sG300AnalysisFunction,
		sG150AnalysisFunction
};

/*******************************************************************************
 �������ƣ�    void protocol_Reset(void)
 ����������    Э��ĸ�λ��������Ҫ����һЩ�����ĳ�ʼ��
 ����˵����    ��
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
 �������ƣ�    void protocol_PollingTask(void)
 ����������    ����Э�鴦�������
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

