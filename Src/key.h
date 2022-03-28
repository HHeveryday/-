#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x_exti.h"
#include "stm32f10x.h"

//Òý½Å¶¨Òå
/*PA0-->B1
PB8-->B2
PB1-->B3
PB2-->B4
*/
#define KEYB1_INT_GPIO_PORT         GPIOA
#define KEYB1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEYB1_INT_GPIO_PIN          GPIO_Pin_0
#define KEYB1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEYB1_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEYB1_INT_EXTI_LINE         EXTI_Line0
#define KEYB1_INT_EXTI_IRQ          EXTI0_IRQn

#define KEYB1_IRQHandler            EXTI0_IRQHandler


#define KEYB2_INT_GPIO_PORT         GPIOA
#define KEYB2_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEYB2_INT_GPIO_PIN          GPIO_Pin_8
#define KEYB2_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEYB2_INT_EXTI_PINSOURCE    GPIO_PinSource8
#define KEYB2_INT_EXTI_LINE         EXTI_Line8
#define KEYB2_INT_EXTI_IRQ          EXTI9_5_IRQn

#define KEYB2_IRQHandler            EXTI9_5_IRQHandler



#define KEYB3_INT_GPIO_PORT         GPIOB
#define KEYB3_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEYB3_INT_GPIO_PIN          GPIO_Pin_1
#define KEYB3_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEYB3_INT_EXTI_PINSOURCE    GPIO_PinSource1
#define KEYB3_INT_EXTI_LINE         EXTI_Line1
#define KEYB3_INT_EXTI_IRQ          EXTI1_IRQn

#define KEYB3_IRQHandler            EXTI1_IRQHandler

#define KEYB4_INT_GPIO_PORT         GPIOB
#define KEYB4_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEYB4_INT_GPIO_PIN          GPIO_Pin_2
#define KEYB4_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEYB4_INT_EXTI_PINSOURCE    GPIO_PinSource2
#define KEYB4_INT_EXTI_LINE         EXTI_Line2
#define KEYB4_INT_EXTI_IRQ          EXTI2_IRQn

#define KEYB4_IRQHandler            EXTI2_IRQHandler
void EXTI_Key_Config(void);

#endif
