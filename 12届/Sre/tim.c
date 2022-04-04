#include "tim.h"

void Init_Timer()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 4999;//5ms¶¨Ê±
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	  /* TIM IT enable */
  TIM_ITConfig(TIM1,TIM_FLAG_Update, ENABLE);

  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
//	TIM_PrescalerConfig(TIM2, PrescalerValue, TIM_PSCReloadMode_Immediate);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void Init_PWM()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 9;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 5;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
//	TIM_Cmd(TIM3, ENABLE);
	
	
}

