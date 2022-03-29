#include "key.h"


void Init_Exti(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/*      B1 B2     */
  // 时钟使能-GPIOA和AFIO（引脚复用功能）
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE); 
  // 将GPIOA0配置为上拉输入模式
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE); 
  // 将GPIOB1  B2配置为上拉输入模式
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
  // 将EXTI_Line0配置为下降沿触发中断模式
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  // 将EXTI_Line0与GPIOA0绑定
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  
	
	
		// 将EXTI_Line8配置为下降沿触发中断模式
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	  // 将EXTI_Line0与GPIOA8绑定
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8); 
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	  // 将EXTI_Line1与GPIOB1绑定
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); 
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	  // 将EXTI_Line2与GPIOB2绑定
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); 
	
	
  // 设置中断优先级并使能中断
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_Init(&NVIC_InitStructure);
	
	
}





















//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* 配置NVIC为优先级组1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  
//  /* 配置中断源：按键B1 */
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB1_INT_EXTI_IRQ;
//  /* 配置抢占优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 配置子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断通道 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//  
//  /* 配置中断源：按键B2，其他使用上面相关配置 */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB2_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//	
//	  /* 配置中断源：按键B3，其他使用上面相关配置 */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB3_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//	  /* 配置中断源：按键B4，其他使用上面相关配置 */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB4_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//}

// /**
//  * @brief  配置 IO为EXTI中断口，并设置中断优先级
//  * @param  无
//  * @retval 无
//  */
//void EXTI_Key_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure; 
//	EXTI_InitTypeDef EXTI_InitStructure;

//	/*开启按键GPIO口的时钟*/
//	RCC_APB2PeriphClockCmd(KEYB1_INT_GPIO_CLK,ENABLE);
//												
//	/* 配置 NVIC 中断*/
//	NVIC_Configuration();
//	
///*--------------------------KEY1配置-----------------------------*/
//	/* 选择按键用到的GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB1_INT_GPIO_PIN;
//  /* 配置为浮空输入 */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB1_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* 选择EXTI的信号源 */
//  GPIO_EXTILineConfig(KEYB1_INT_EXTI_PORTSOURCE, KEYB1_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB1_INT_EXTI_LINE;
//	
//	/* EXTI为中断模式 */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 上升沿中断 */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  /* 使能中断 */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	
//  /*--------------------------KEY2配置-----------------------------*/
//	/* 选择按键用到的GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB2_INT_GPIO_PIN;
//  /* 配置为浮空输入 */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB2_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* 选择EXTI的信号源 */
//  GPIO_EXTILineConfig(KEYB2_INT_EXTI_PORTSOURCE, KEYB2_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB2_INT_EXTI_LINE;
//	
//	/* EXTI为中断模式 */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 下降沿中断 */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* 使能中断 */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	  /*--------------------------KEY3配置-----------------------------*/
//			/*开启按键GPIO口的时钟*/
//	RCC_APB2PeriphClockCmd(KEYB3_INT_GPIO_CLK,ENABLE);
//	/* 选择按键用到的GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB2_INT_GPIO_PIN;
//  /* 配置为浮空输入 */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB3_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* 选择EXTI的信号源 */
//  GPIO_EXTILineConfig(KEYB3_INT_EXTI_PORTSOURCE, KEYB3_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB3_INT_EXTI_LINE;
//	
//	/* EXTI为中断模式 */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 下降沿中断 */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* 使能中断 */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	  /*--------------------------KEY4配置-----------------------------*/
//	/* 选择按键用到的GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB4_INT_GPIO_PIN;
//  /* 配置为浮空输入 */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB4_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* 选择EXTI的信号源 */
//  GPIO_EXTILineConfig(KEYB4_INT_EXTI_PORTSOURCE, KEYB4_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB4_INT_EXTI_LINE;
//	
//	/* EXTI为中断模式 */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* 下降沿中断 */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* 使能中断 */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//}
