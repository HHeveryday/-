#ifndef __USART_H_
#define __USART_H_
#include "stm32f10x.h"
#include "stdio.h"


void SendOneByte(u32 Data);
void Usart_SendString( char *str);
void Init_Usart(void);
#endif
