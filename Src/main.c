
#include "fun.h"

u32 TimingDelay = 0;

void Delay_Ms(u32 nTime);

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);

	//	Delay_Ms(200);
	LED_GPIO_Config();
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);

	int count_cnbr = 2;
	int count_vnbr = 4;
	int count_idle = 6;
	double size1 = 3.50, size2 = 2.00;
	Display_Parkingspace(count_cnbr, count_vnbr, count_idle);
	Delay_Ms(6000);
	Display_Ratesset(size1, size2);

	while (1)
		;
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}
