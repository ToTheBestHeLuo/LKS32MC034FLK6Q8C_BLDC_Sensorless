#ifndef _DSHOT_H_
#define _DSHOT_H_

#include <stdint.h>

#define dShot_Logical1_DMA_Value (60u * 4u)
#define dShot_Logical0_DMA_Value (30u * 4u)

extern uint32_t dShot_GetTransmitBufferAddress(void);
extern uint32_t dShot_GetReceiveBufferAddress(void);

extern void dShot_TransmitValueWithDMA(void);
extern uint16_t dShot_ReceiveValueWithDMA(void);
extern void dShot_ValueEncode(uint16_t value,uint8_t checkBit);
extern void dShot_ValueTransmitWithDMA(uint16_t value,uint8_t checkBit);

#endif
