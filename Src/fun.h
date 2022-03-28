#ifndef __FUN_H_
#define __FUN_H_

#include "stm32f10x.h"
#include "lcd.h"
#include "led.h"

void Display_Parkingspace(int count_cnbr, int count_vnbr, int count_idle);
void Display_Ratesset(double s1, double s2);
#endif
