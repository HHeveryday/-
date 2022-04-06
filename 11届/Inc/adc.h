#ifndef __ADC_H_
#define __ADC_H_


#include "stm32f10x.h"
#define ADC1_DR_Address    ((uint32_t)0x4001244C)


float get_adc(void);
void Adc_Init(void);
#endif
