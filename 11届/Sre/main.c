#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "led.h"
#include "key.h"
#include "tim.h"
#include "adc.h"
#include "stdbool.h"


float ADCConvertedValue;
bool Flagdisplay1 = true;//切换数据和参数界面
bool Flagdisplay2 = true;//切换模式
uint16_t Flag5ms = 0;
uint16_t Flag1_500us = 0;
uint16_t Flag2_500us = 0;
uint16_t Flag1_50us;
uint16_t Flag2_50us;

float V_data = 0;
uint8_t keyb1 = 0, keyb2 = 0, keyb3 = 0, keyb4 = 0;
uint8_t PA6_Data = 1;
uint8_t PA7_Data = 1;
int pwm_auto = 0;
u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

bool t = true;


void keyclear()
{
	if (keyb1 < 50)
	{
		keyb1 += 5;
	}
		if (keyb2 < 50)
	{
		keyb2 += 5;
	}
		if (keyb3 < 50)
	{
		keyb3 += 5;
	}
	
		if (keyb4 < 50)
	{
		keyb4 += 5;
	}
}

void Display1()
{
	V_data =(float) ADCConvertedValue/4096*3.3; // 读取转换的AD值
	LCD_DisplayStringLine(Line1, (unsigned char *)"      Data           ");
	if (Flagdisplay2 == true)
	{
		char temp[20] = {0};
		sprintf(temp,"    %s%.2f%s         ","V:",V_data,"V");
	  LCD_DisplayStringLine(Line3, (unsigned char *)temp);
		LCD_DisplayStringLine(Line5, (unsigned char *)"    Mode:AUTO        ");
	}
	else
	{
		char temp[20] = {0};
		sprintf(temp,"    %s%.2f%s         ","V:",V_data,"V");
		LCD_DisplayStringLine(Line3, (unsigned char *)temp);
		LCD_DisplayStringLine(Line5, (unsigned char *)"    Mode:MANU        ");
	}

}

void Display2()
{
	char temp[20] = {0};
	uint8_t temp1 = PA6_Data*10;
	uint8_t temp2 = PA7_Data*10;
	LCD_DisplayStringLine(Line1, (unsigned char *)"      Para           ");
	sprintf(temp,"    %s%d%s          ","PA6:",temp1,"%");
	LCD_DisplayStringLine(Line3, (unsigned char *)temp);
	sprintf(temp,"    %s%d%s          ","PA7:",temp2,"%");
	LCD_DisplayStringLine(Line5, (unsigned char *)temp);
}

void LED_Control()
{
	if (Flagdisplay2 == true)
	{
				GPIO_ResetBits(GPIOC,GPIO_Pin_8);
				GPIO_SetBits(GPIOC,GPIO_Pin_9);
	      GPIO_SetBits(GPIOD,GPIO_Pin_2);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			}
			else
			{
				GPIO_ResetBits(GPIOC,GPIO_Pin_9);
				GPIO_SetBits(GPIOC,GPIO_Pin_8);
	      GPIO_SetBits(GPIOD,GPIO_Pin_2);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			}
}

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);


	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	Key_Init();
	LED_Init();
	Timer_Init();
	PWM_Init();
	Adc_Init();
	LED_OFF();

		
	while (1)
	{
		if (t == false)
		{
		  	GPIO_ResetBits(GPIOC,GPIO_Pin_12);
	      GPIO_SetBits(GPIOD,GPIO_Pin_2);
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		}
		ADCConvertedValue = get_adc();
		pwm_auto = ADCConvertedValue/3.3*100;
		if (Flag5ms == 1)
		{
			LED_Control();
			Flag5ms = 0;
			keyclear();
			if (Flagdisplay1 == true)
			{
				Display1();
			}
			else
			{
				Display2();
			}			
		}		
	}
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}


void EXTI0_IRQHandler()
{
	 if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		if (keyb1 >= 50)
		{
			keyb1 = 0;
			Flagdisplay1 = !Flagdisplay1;
		}
  }
}
void EXTI9_5_IRQHandler()
{
	 if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);
		if (keyb2 >= 50)
		{
			keyb2 = 0;
			if (Flagdisplay1 == false)
			{
				if (PA6_Data == 9)
				{
					PA6_Data = 1;
				}
				else
				{
					PA6_Data++;
				}
			}
		}
  }
}
void EXTI1_IRQHandler()
{
	 if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
		if (keyb3 >= 50)
		{
			keyb3 = 0;
			if (Flagdisplay1 == false)
			{
				if (PA7_Data == 9)
				{
					PA7_Data = 1;
				}
				else
				{
					PA7_Data++;
				}
			}
		}
  }
}

void EXTI2_IRQHandler()
{
	 if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line2);
		if (keyb4 >= 50)
		{
			keyb4 = 0;
			Flagdisplay2 = !Flagdisplay2;
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


void TIM2_IRQHandler()
{
	 if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
		if (Flagdisplay2 == false)
		{
			Flag1_500us++;
			Flag2_500us++;
		if (Flag1_500us == 10)
		{
			Flag1_500us = 0;
		}
		if (Flag2_500us == 20)
		{
			Flag2_500us = 0;
		}
		
		
		if (Flag1_500us < PA6_Data)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		}

		
		if (Flag2_500us < PA7_Data*2)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
		}
		else
		{
			
		}
	}
}

void TIM3_IRQHandler()
{
	 if (TIM_GetITStatus(TIM3, TIM_FLAG_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
		t = false;
		if (Flagdisplay2 == true)
		{
			Flag1_50us++;
			Flag2_50us++;

		if (Flag1_50us == 100)
		{
			Flag1_50us = 0;
		}
		if (Flag2_50us == 200)
		{
			Flag2_50us = 0;
		}
		
		
		if (Flag1_50us < pwm_auto)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		}

		
		if (Flag2_50us < pwm_auto*2)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_7);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		}
		}
	}
}
