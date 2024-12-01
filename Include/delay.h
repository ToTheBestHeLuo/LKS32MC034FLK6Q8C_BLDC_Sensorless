#ifndef MYDELAY_H_
#define MYDELAY_H_

#include <basic.h>


void delay_init(u32 SYSCLK);
void delay_ms(u32 nms);
void delay_us(u32 nus);

#endif
