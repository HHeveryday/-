#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "tim.h"
#include "led.h"
#include "key.h"
#include "stdbool.h"
#include "fun.h"
#include "usart.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);


int count_cnbr = 2;
int count_vnbr = 4;
int count_idle = 6;
double size1 = 3.50, size2 = 2.00;
bool FlagB1 = true;
bool FlagB4 = true;
bool FlagIDLE = false;
unsigned short Key1delay = 0, Key2delay = 0, Key3delay = 0, Key4delay = 0;
unsigned char Flag5ms = 1;

unsigned char RxBuffer[23] = {'\0'};
unsigned char RxCounter = 0;
unsigned char TxBuffer[30] = {'\0'};
unsigned char TxCounter = 0;
//Main Body

void timecount()
{
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

int main(void)
{
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	Init_Timer();
	Init_LED();
	Init_key();
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	Init_Usart();
	Init_PWM();
	LEDOFF();
//	printf("hello");


	while(1)
	{
			
		if (Flag5ms == 1)
		{
			Flag5ms = 0;
			timecount();
			if (FlagB4 == true)
			{
				TIM_Cmd(TIM3, ENABLE);
			}
			else
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			}
			if (FlagIDLE == true)
			{
				FlagIDLE = false;
				RxCounter = 0;
				LCD_DisplayStringLine(Line9, (unsigned char *)RxBuffer);
				RxBuffer[22] = '\0';
				int flag = Checkstring((char*)RxBuffer);
				if (flag == 0)
				{
					printf("×Ö·û´®´íÎó");
				}
				else
				{
					printf("×Ö·û´®ÕýÈ·");
				}
			}
			if (FlagB1 == true)
			{
				Display_Parkingspace(count_cnbr, count_vnbr, count_idle);
			}
			else
			{
				LCD_ClearLine(Line8);
				Display_Ratesset(size1, size2);
			}	
		}
	}

}
void TIM1_UP_IRQHandler()
{
	if (TIM_GetITStatus(TIM1, TIM_FLAG_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
		Flag5ms = 1;
	}
}

//°´¼üB1
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		if(Key1delay >= 50)
		{
			Key1delay = 0;
			FlagB1 = !FlagB1;
		}
  }
}
//°´¼üB3
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
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
//°´¼üB4
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line2);
		if(Key4delay >= 50)
		{
			Key4delay = 0;
			FlagB4 = !FlagB4;
		}
	}
}
//°´¼üB2
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);
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

void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		if (RxCounter < 23)
		{
			RxBuffer[RxCounter++] = USART_ReceiveData(USART2);
		}
	}	
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
			USART_ClearITPendingBit(USART2, USART_IT_IDLE);
      USART_ReceiveData(USART2);
			FlagIDLE = true;
    }
		
 }


 


 
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

  return ch;
}
