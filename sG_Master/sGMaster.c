#include "sGMaster.h"

void DMA_IRQHandler(void)
{
		TIMER1->CFG &= ~(BIT31);
		/*清中断标志*/
		TIMER1->IF = 0x7;DMA_IF = 0xf;
		GPIO_SetBits(GPIO1,GPIO_Pin_3);
		if(sG.isSendOrReceive){
			/*调整IO为输入模式*/
			sG.isSendOrReceive = false;
			/*调整DMA配置*/
			sG_DMA_Switch2Receive();
			/*调整计数门限*/
			TIMER1->TH = UINT32_MAX;
			/*调整帧间隔时间*/
			TIMER1->CMPT0 = 160 - 1;
			TIMER1->CNT = 1;
			/*开比较中断*/
			TIMER1->IE = (BIT0);
		}else{
			GPIO_ResetBits(GPIO1,GPIO_Pin_3);
			sG_ProtocolProcess(&sG.transmitData);
			sG_TransmitWithDMA(sG.transmitData);
			sG.isSendOrReceive = true;
			/*调整为发送状态*/
			sG_DMA_Switch2Transmit();
			/*调整计数门限*/
			TIMER1->TH = UINT32_MAX;
			TIMER1->CMPT0 = 160 * 4 - 1;
			TIMER1->CNT = 1;
			/*调整为比较输出模式*/
			TIMER1->CFG &= ~(BIT10);
			/*打开比较中断*/
			TIMER1->IE = BIT0;
		}
		GPIO_SetBits(GPIO1,GPIO_Pin_3);
		sG.isSendOrReceiveFinished = true;
		TIMER1->CFG |= (BIT31);
}

void TIMER1_IRQHandler(void)
{
		TIMER1->CFG &= (~BIT31);
		/*清中断标志*/
		TIMER1->IF = 0x7;
		if(sG.isSendOrReceive){
			/*进入发送状态*/
			/*调整计数门限*/
			TIMER1->TH = 160 - 1;
			TIMER1->CMPT1 = 0;
			TIMER1->CNT = 1;
			TIMER1->IE = BIT10;
			/*调整IO为输出模式*/
			GPIO1->PIE &= ~(BIT5);
			GPIO1->POE |= (BIT5);
			/*DMA传输：发送模式*/
			DMA_CH0->DMA_CTMS = 18;
			DMA_CH0->DMA_CCR |= BIT0;
		}else{
			/*进入接收状态*/
			/*调整计数门限*/
			TIMER1->TH = 160 * 16;
			TIMER1->CNT = 81;
			TIMER1->CMPT0 = 80;
			/*调整为捕获输入模式*/
			GPIO1->POE &= ~(BIT5);
			GPIO1->PIE |= (BIT5);
			TIMER1->CFG |= (BIT10);
			/*使能比较信号触发DMA*/
			TIMER1->IE = (BIT8);
			/*DMA传输：接收模式*/
			DMA_CH0->DMA_CTMS = 16;    /*配置DMA搬运轮数或次数*/
			DMA_CH0->DMA_CCR |= BIT0;/*使能DMA搬运*/
		}
		TIMER1->CFG |= (BIT31);
}

sGHandler sG = {
	.transmitBuffer = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,UINT16_MAX,0},
	.isSendOrReceive = true,
	.isSendOrReceiveFinished = false,
	.isReceiveTimeOut = false
};

static uint16_t sG_CalculateWithCRC(uint16_t value,bool isSendOrReceive)
{
		uint16_t pack;
		/*当Master处于发送状态时，发送的Check位必须为0*/
		if(isSendOrReceive) pack = (value << 1);
		/*当Master处于接收状态时，Check位必须为1*/
		else pack = (value << 1) | (1);
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
		
		/*作为Master接收时，由Slave发送的Check必须为1*/
		
		if(!checkBit) return false;
		
		*value = val; 
		
    return true;
}




