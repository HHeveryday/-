
#include "fun.h"

#include "led.h"
#include "key.h"
#include "timi.h"
#include "stdbool.h"
#include "uart.h"

unsigned char Flag5ms = 0;
unsigned short Key1delay = 0, Key2delay = 0, Key3delay = 0, Key4delay = 0;

bool FlagB1 = true;
bool FlagB4 = true;

int count_cnbr = 2;
int count_vnbr = 4;
int count_idle = 6;
double size1 = 3.50, size2 = 2.00;
u32 TimingDelay = 0;
void Delay_Ms(u32 nTime);

int main(void)
{
	Init_Timer();
	LED_GPIO_Config();
	STM3210B_LCD_Init();
	Init_Exti();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	Init_Timer_PWM();
//	Init_UART();
//	SendOneByte('A');
//	USART_Config();
//	printf("欢迎\n\n\n\n");
	while (1)
	{
		if(Flag5ms == 1)
		{
			Flag5ms = 0;
			if (FlagB1 == true)
			{
				Display_Parkingspace(count_cnbr, count_vnbr, count_idle);
			}
			else
			{
				LCD_ClearLine(Line8);
				Display_Ratesset(size1, size2);
			}
			
			if (FlagB4 == true)
			{
				TIM_Cmd(TIM3, ENABLE);
			}
			else
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			}
			
			
			if (Key1delay < 50)
			{
				Key1delay += 5;
			}
			if (Key2delay < 50)
			{
				Key2delay += 5;
			}
			if (Key3delay < 50)
			{
				Key3delay += 5;
			}
			if (Key4delay < 50)
			{
				Key4delay += 5;
			}
		}
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}

void KEYB1_IRQHandler()
{
	if(EXTI_GetITStatus(KEYB1_INT_EXTI_LINE) != RESET) 
	{
    //清除中断标志位
		EXTI_ClearITPendingBit(KEYB1_INT_EXTI_LINE);
    if(Key1delay >= 50)
		{
			Key1delay = 0;
			FlagB1 = !FlagB1;
		}
	}  
}
// 定时器1中断
void TIM1_UP_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //更新中断产生
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除中断标志
    Flag5ms = 1;
  }
}

void KEYB2_IRQHandler()
{
	if(EXTI_GetITStatus(KEYB2_INT_EXTI_LINE) != RESET) 
	{
    //清除中断标志位
		EXTI_ClearITPendingBit(KEYB2_INT_EXTI_LINE);
    if(Key2delay >= 50)
		{
			Key2delay = 0;
			if (FlagB1 == false)
			{
				size1 += 0.5;
				size2 += 0.5;
			}

		}
	}
}


void KEYB3_IRQHandler()
{
	if(EXTI_GetITStatus(KEYB3_INT_EXTI_LINE) != RESET) 
	{
    //清除中断标志位
		EXTI_ClearITPendingBit(KEYB3_INT_EXTI_LINE);
    if(Key3delay >= 50)
		{
			Key3delay = 0;
			if (FlagB1 == false)
			{
				size1 -= 0.5;
				size2 -= 0.5;
			}
		}
}
}
void KEYB4_IRQHandler()
{
	if(EXTI_GetITStatus(KEYB4_INT_EXTI_LINE) != RESET) 
	{
    //清除中断标志位
		EXTI_ClearITPendingBit(KEYB4_INT_EXTI_LINE);
    if(Key4delay >= 50)
		{
			Key4delay = 0;
			FlagB4 = !FlagB4;
		}
	}
}

void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
    USART_SendData(DEBUG_USARTx,ucTemp);
	}	 
}

//void USART2_IRQHandler(void)
//{
//	unsigned char  dat;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{
//		USART_ClearFlag(USART2, USART_IT_RXNE);
//		dat = USART_ReceiveData(USART2);
//		count_cnbr = dat;
//		SendOneByte(dat);

//	} 										 
//}