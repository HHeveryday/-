#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"
#include "led.h"
#include "tim.h"
#include "adc.h"
#include "stdio.h"
#include "stdbool.h"

u32 TimingDelay = 0;

float V_data = 0;
float V_Max = 2.4;
float V_Min = 1.2;
uint8_t UpperLED = 1;
uint8_t LowerLED = 2;

uint8_t flag5ms = 0;
bool flagb1 = true;
bool flag200ms = true;
uint8_t count = 0;
uint8_t flagb2 = 1;


uint16_t keyB1 = 0, keyB2 = 0, keyB3 = 0, keyB4 = 0;

char* status[3] = {"Upper","Lower","Normal"};

char* p = "Upper";
void Delay_Ms(u32 nTime);


void Key_clear()//°´¼üÏû¶¶
{
	if (keyB1 < 50)
	{
		keyB1 += 5;
	}
	if (keyB2 < 50)
	{
		keyB2 += 5;
	}
	if (keyB3 < 50)
	{
		keyB3 += 5;
	}
	if (keyB4 < 50)
	{
		keyB4 += 5;
	}
}

void Display1()
{
	LCD_ClearLine(Line4);
	LCD_ClearLine(Line6);
	char temp[20] = {0};
	LCD_DisplayStringLine(Line2 ,(unsigned char *)"        Main        ");
	sprintf(temp,"    %s%.2f%s      ","Volt:", V_Min, "V");
	LCD_DisplayStringLine(Line5 ,(unsigned char *)temp);
	if (V_data < V_Min)
	{
		sprintf(temp,"    %s%%s      ","Status:", p);
	}
	else if (V_data > V_Min && V_data < V_Max)
	{
		sprintf(temp,"    %s%%s      ","Status:", status[3]);
	}
	else
	{
		sprintf(temp,"    %s%%s      ","Status:", status[1]);
	}
		
	
	LCD_DisplayStringLine(Line7 ,(unsigned char *)temp);
}


void Display2()
{
	char temp[20] = {0};
	LCD_DisplayStringLine(Line2 ,(unsigned char *)"      Setting       ");
	sprintf(temp,"    %s%.1f%s     ","Max Volt:", V_Max, "V");
	if (flagb2 == 1)
	{
		LCD_SetBackColor(Green);
	}
	else
	{
		LCD_SetBackColor(Black);
	}
	LCD_DisplayStringLine(Line4 ,(unsigned char *)temp);
  sprintf(temp,"    %s%.1f%s     ","Min Volt:", V_Min, "V");
		if (flagb2 == 2)
	{
		LCD_SetBackColor(Green);
	}
	else
	{
		LCD_SetBackColor(Black);
	}
	LCD_DisplayStringLine(Line5 ,(unsigned char *)temp);
	sprintf(temp,"    %s%d       ","Upper:LD", UpperLED);
	if (flagb2 == 3)
	{
		LCD_SetBackColor(Green);
	}
	else
	{
		LCD_SetBackColor(Black);
	}
	LCD_DisplayStringLine(Line6 ,(unsigned char *)temp);
  sprintf(temp,"    %s%d       ","Lower:LD", LowerLED);
	if (flagb2 == 4)
	{
		LCD_SetBackColor(Green);
	}
	else
	{
		LCD_SetBackColor(Black);
	}
	LCD_DisplayStringLine(Line7 ,(unsigned char *)temp);
}

void PD2_Control()
{
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void LED_Control()
{
	if (V_data > V_Max)
	{
		if (UpperLED == 1)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_8);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_8);
			PD2_Control();
		}
	}
	else if (UpperLED == 2)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_9);
			PD2_Control();
		}
	}
		else if (UpperLED == 3)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			PD2_Control();
		}
	}
		else if (UpperLED == 4)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_11);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_11);
			PD2_Control();
		}
	}
		else if (UpperLED == 5)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_12);
			PD2_Control();
		}
	}
		else if (UpperLED == 6)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			PD2_Control();
		}
	}
		else if (UpperLED == 7)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_14);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_14);
			PD2_Control();
		}
	}
	else
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_15);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_15);
			PD2_Control();
		}
	}
	}
	if (V_data < V_Min)
	{
		if (LowerLED == 1)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_8);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_8);
			PD2_Control();
		}
	}
	else if (LowerLED == 2)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_9);
			PD2_Control();
		}
	}
		else if (LowerLED == 3)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			PD2_Control();
		}
	}
		else if (LowerLED == 4)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_11);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_11);
			PD2_Control();
		}
	}
		else if (LowerLED == 5)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_12);
			PD2_Control();
		}
	}
		else if (LowerLED == 6)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			PD2_Control();
		}
	}
		else if (LowerLED == 7)
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_14);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_14);
			PD2_Control();
		}
	}
	else
	{
		if (flag200ms == false)
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_15);
			PD2_Control();
		}
		else
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_15);
			PD2_Control();
		}
	}
	}
}


int main(void)
{
//	SysTick_Config(SystemCoreClock/1000);

//	Delay_Ms(200);
	
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	Key_Init();
	Led_Init();
	Timer_Init();
	Adc_Init();


  LED_ALLOFF();
	
	while(1)
	{
		V_data = Get_ADC();
		LED_Control();
		if (flag5ms == 1)
		{
			flag5ms = 0;
			if (flagb1  == true)
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
//void Delay_Ms(u32 nTime)
//{
//	TimingDelay = nTime;
//	while(TimingDelay != 0);	
//}

void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		if (keyB1 >= 50)
		{
			keyB1 = 0;
			flagb1 = !flagb1;
		}
  }
}

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);
		if (keyB2 >= 50)
		{
			keyB1 = 0;
			if (++flagb2 == 5)
			{
				flagb2 = 1;
			}
		}
  }
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
		if (keyB3 >= 50)
		{
			keyB3 = 0;
			if (flagb2== 1)
			{
				V_Max += 0.3;
				if (V_Max > 3.3)
				{
					V_Max = 3.3;
				}
			}
			else if (flagb2== 2)
			{
				V_Min += 0.3;
				if (V_Min > 3.3)
				{
					V_Min = 3.3;
				}
			}
			else if (flagb2== 3)
			{
				UpperLED++;
				if (UpperLED == LowerLED)
				{
					UpperLED++;
				}
				if (UpperLED == 9)
				{
					UpperLED = 1;
				}
			}
			else
			{
				LowerLED++;
				if (UpperLED == LowerLED)
				{
					LowerLED++;
				}
				if (LowerLED == 9)
				{
					LowerLED = 1;
				}
			}
		}
  }
}

void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line2);
		if (keyB4 >= 50)
		{
			keyB4 = 0;
			if (flagb2== 1)
			{
				V_Max -= 0.3;
				if (V_Max < 0)
				{
					V_Max = 0;
				}
			}
			else if (flagb2== 2)
			{
				V_Min -= 0.3;
				if (V_Min < 0)
				{
					V_Min = 0;
				}
			}
			else if (flagb2== 3)
			{
				UpperLED--;
				if (UpperLED == LowerLED)
				{
					UpperLED--;
				}
				if (UpperLED == 0)
				{
					UpperLED = 8;
				}
			}
			else
			{
				LowerLED--;
				if (UpperLED == LowerLED)
				{
					LowerLED--;
				}
				if (LowerLED == 0)
				{
					LowerLED = 8;
				}
			}
		}
	}
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
		flag5ms = 1;
		count++;
		if (count == 40)
		{
			count = 0;
			flag200ms = !flag200ms;  
		}
	}
}
