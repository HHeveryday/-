#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"

#define LED_GPIO_PORT   			 	GPIOC			              /* 控制LED的GPIO端口D和LED的GPIO端口C */
#define LED_GPIO_CLK 				    RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define LED_GPIO_PIN						GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15 /* 连接到SCL时钟线的GPIO */

#define LED_CONTROL_GPIO_PORT   GPIOD
#define LED_CONTROL_GPIO_CLK    RCC_APB2Periph_GPIOD
#define LED_CONTROL_GPIO_PIN    GPIO_Pin_2


void LED_GPIO_Config(void);
#endif
