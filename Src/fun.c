#include "fun.h"



void Display_Parkingspace(int c1, int c2, int c3)
{
	char arr1[20] = " ";
	char arr2[20] = " ";
	char arr3[20] = " ";
	sprintf(arr1, "   %s%d          ", "CNBR:", c1);
	sprintf(arr2, "   %s%d          ", "VNBR:", c2);
	sprintf(arr3, "   %s%d          ", "IDLE:", c3);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line4);
	LCD_ClearLine(Line6);

	LCD_DisplayStringLine(Line2, (unsigned char *)"       Data        ");
	LCD_DisplayStringLine(Line4, (unsigned char *)arr1);
	LCD_DisplayStringLine(Line6, (unsigned char *)arr2);
	LCD_DisplayStringLine(Line8, (unsigned char *)arr3);
}


void Display_Ratesset(double s1, double s2)
{
	char arr4[20] = " ";
	char arr5[20] = " ";
  sprintf(arr4,"   %s%.2lf       ","CNBR:",s1);
	sprintf(arr5,"   %s%.2lf       ","VNBR:",s2);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line4);
	LCD_ClearLine(Line6);
	LCD_ClearLine(Line8);
	LCD_DisplayStringLine(Line2, (unsigned char *)"        Para       ");
	LCD_DisplayStringLine(Line4, (unsigned char *)arr4);
	LCD_DisplayStringLine(Line6, (unsigned char *)arr5);
}