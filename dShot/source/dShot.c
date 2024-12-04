/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-09-26 11:21:23
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-09-26 15:03:51
 * @FilePath: \MDK-ARMd:\stm32cube\stm32g431cbu6_dShot_Test\dShot\source\dShot.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "..\include\dShot.h"
#include <stddef.h>
#include <stdbool.h>

uint16_t dmaTransmitBuffer[16 + 2];
uint16_t dmaReceiveBuffer[16 + 2];

uint32_t dShot_GetTransmitBufferAddress(void)
{
    return (uint32_t)&dmaTransmitBuffer[0];
}

uint32_t dShot_GetReceiveBufferAddress(void)
{
    return (uint32_t)&dmaReceiveBuffer[0];
}

uint16_t dShot_CalculateWithCRC(uint16_t value,uint8_t checkBit)
{
    uint16_t pack = (value << 1) | (checkBit ? 1 : 0);
    uint16_t sum = 0,tmp = pack;
    for(int i = 0;i < 3;i++){
        sum ^= tmp;tmp >>= 4;
    }
    pack = (pack << 4) | (sum & 0xf);
    return pack;
}

void dShot_ValueEncode(uint16_t value,uint8_t checkBit)
{
    value = (value > 2047) ? 2047 : value;
    value = dShot_CalculateWithCRC(value,checkBit);
    for(int i = 0;i < 16;i++){
        dmaTransmitBuffer[i] = (value & 0x8000) ? dShot_Logical1_DMA_Value : dShot_Logical0_DMA_Value;
        value <<= 1;
    }
    dmaTransmitBuffer[16] = 0;
    dmaTransmitBuffer[17] = 0;
}

void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit)
{
    dShot_ValueEncode(value,checkBit);
    dShot_TransmitValueWithDMA();
}

void dShot_TransmitValueWithDMA(void)
{
}

uint16_t dShot_ReceiveValueWithDMA(void)
{
    uint16_t value = 0x0000;
    uint16_t realData = 0x0000;

		for(int i = 0;i < 16;i++){
				realData <<= 1;
				realData |= ((dmaReceiveBuffer[i] & 0x0008) >> 3);
		}

		uint8_t checkBit = realData & 0x10;
		value = realData >> 5;

		if(dShot_CalculateWithCRC(value,checkBit) != realData) return 0x0000;
        

    return value;
}





