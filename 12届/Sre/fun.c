#include "fun.h"

typedef struct Car
{
	char type[4];
	char ID[4];
	int year;
	int month;
	int day;
	int hour;
	int min;
	
}Car;

/*
计算相同车辆的停车时间，入：200202120000
												出：200202213205
                       费用=（2002-2002）*365*24+（02-02）*
*/


extern unsigned char RxBuffer[23];
extern unsigned char RxCounter;
extern unsigned char TxBuffer[30];
extern unsigned char TxCounter;
void Display_Parkingspace(int c1, int c2, int c3)
{
	char arr1[20] = " ";
	char arr2[20] = " ";
	char arr3[20] = " ";
	sprintf(arr1, "   %s%d          ", "CNBR:", c1);
	sprintf(arr2, "   %s%d          ", "VNBR:", c2);
	sprintf(arr3, "   %s%d          ", "IDLE:", c3);
//	LCD_ClearLine(Line2);
//	LCD_ClearLine(Line4);
//	LCD_ClearLine(Line6);

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
//	LCD_ClearLine(Line2);
//	LCD_ClearLine(Line4);
//	LCD_ClearLine(Line6);
//	LCD_ClearLine(Line8);
	LCD_DisplayStringLine(Line2, (unsigned char *)"        Para       ");
	LCD_DisplayStringLine(Line4, (unsigned char *)arr4);
	LCD_DisplayStringLine(Line6, (unsigned char *)arr5);
}

int Checkstring(const char* p)
{
	 if (*p != 'V' && *p != 'C')
    {
        return 0;
    }
    p++;
    if (*p != 'N')
    {
        return 0;
    }
    p++;
    if (*p != 'B')
    {
        return 0;
    }
    p++;
    if (*p != 'R')
    {
        return 0;
    }
    p++;
    if (*p != ':')
    {
        return 0;
    }
    p++;
    for (int i = 0; i < 4; i++)
    {
        if ('0' <= (*p) <= '9' || 'A' <= (*p) <= 'd')
        {
            p++;
        }
        else
        {
            return 0;
        }
    }
    if (*p != ':')
    {
        return 0;
    }
    p++;
    for (int i = 0; i < 12; i++)
    {
        if ('0' <= (*p) <= '9')
        {
            p++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

