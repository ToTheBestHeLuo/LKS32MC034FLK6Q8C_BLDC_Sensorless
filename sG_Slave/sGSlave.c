#include "sGSlave.h"

sGHandler sG = {
	.transmitBuffer = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,UINT16_MAX,0},
	.isSendOrReceive = false,
	.isSendOrReceiveFinished = false
};

static uint16_t sG_CalculateWithCRC(uint16_t value,bool isSendOrReceive)
{
		uint16_t pack;
		/*当Slave处于发送状态时，发送的Check位必须为1*/
		if(isSendOrReceive) pack = (value << 1) | (1);
		/*当Slave处于接收状态时，Check位必须为0*/
		else pack = (value << 1);
    uint16_t sum = 0,tmp = pack;
    for(int i = 0;i < 3;i++){
        sum ^= tmp;tmp >>= 4;
    }
    pack = (pack << 4) | (sum & 0xf);
    return pack;
}

void sG_TransmitWithDMA(uint16_t value)
{
    value = (value > 2047) ? 2047 : value;
    value = sG_CalculateWithCRC(value,true);
    for(int i = 0;i < 16;i++){
        sG.transmitBuffer[i] = (value & 0x8000) ? sG_Logical1_DMA_Value : sG_Logical0_DMA_Value;
        value <<= 1;
    }
}

bool sG_ReceiveWithDMA(uint16_t* value)
{
    uint16_t val = 0x0000;
    uint16_t realData = 0x0000;

		for(int i = 0;i < 16;i++){
				realData <<= 1;
				realData |= ((sG.receiveBuffer[i] & sG_ReadPort_Mask) >> sG_ReadPort_Shift);
		}
		
		val = realData >> 5;

		if(sG_CalculateWithCRC(val,false) != realData) return false;
		
		uint8_t checkBit = realData & 0x10;
		
		/*作为Slave接收时，由Master发送的Check必须为0*/
		
		if(checkBit) return false;
		
		*value = val; 
		
    return true;
}




