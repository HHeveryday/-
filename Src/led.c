#include "led.h"
void LED_GPIO_Config(void)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启LED相关的GPIO外设时钟*/
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    /*设置引脚速率为50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /*调用库函数，初始化GPIO*/
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	
	    /*开启控制LED相关的GPIO外设时钟*/
    RCC_APB2PeriphClockCmd(LED_CONTROL_GPIO_CLK, ENABLE);
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = LED_CONTROL_GPIO_PIN;
	
    /*调用库函数，初始化GPIO*/
    GPIO_Init(LED_CONTROL_GPIO_PORT, &GPIO_InitStructure);
    /* 关闭所有led灯	*/
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		//给数据锁存器一个下降沿
    GPIO_SetBits(LED_CONTROL_GPIO_PORT, LED_CONTROL_GPIO_PIN);
		GPIO_ResetBits(LED_CONTROL_GPIO_PORT, LED_CONTROL_GPIO_PIN);
		
}
