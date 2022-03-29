#include "key.h"


void Init_Exti(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/*      B1 B2     */
  // ʱ��ʹ��-GPIOA��AFIO�����Ÿ��ù��ܣ�
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE); 
  // ��GPIOA0����Ϊ��������ģʽ
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE); 
  // ��GPIOB1  B2����Ϊ��������ģʽ
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
  // ��EXTI_Line0����Ϊ�½��ش����ж�ģʽ
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  // ��EXTI_Line0��GPIOA0��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  
	
	
		// ��EXTI_Line8����Ϊ�½��ش����ж�ģʽ
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);
	  // ��EXTI_Line0��GPIOA8��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8); 
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	  // ��EXTI_Line1��GPIOB1��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); 
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	  // ��EXTI_Line2��GPIOB2��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); 
	
	
  // �����ж����ȼ���ʹ���ж�
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
//  /* ����NVICΪ���ȼ���1 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  
//  /* �����ж�Դ������B1 */
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB1_INT_EXTI_IRQ;
//  /* ������ռ���ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* ���������ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж�ͨ�� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//  
//  /* �����ж�Դ������B2������ʹ������������� */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB2_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//	
//	  /* �����ж�Դ������B3������ʹ������������� */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB3_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//	  /* �����ж�Դ������B4������ʹ������������� */  
//  NVIC_InitStructure.NVIC_IRQChannel = KEYB4_INT_EXTI_IRQ;
//  NVIC_Init(&NVIC_InitStructure);
//}

// /**
//  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
//  * @param  ��
//  * @retval ��
//  */
//void EXTI_Key_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure; 
//	EXTI_InitTypeDef EXTI_InitStructure;

//	/*��������GPIO�ڵ�ʱ��*/
//	RCC_APB2PeriphClockCmd(KEYB1_INT_GPIO_CLK,ENABLE);
//												
//	/* ���� NVIC �ж�*/
//	NVIC_Configuration();
//	
///*--------------------------KEY1����-----------------------------*/
//	/* ѡ�񰴼��õ���GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB1_INT_GPIO_PIN;
//  /* ����Ϊ�������� */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB1_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* ѡ��EXTI���ź�Դ */
//  GPIO_EXTILineConfig(KEYB1_INT_EXTI_PORTSOURCE, KEYB1_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB1_INT_EXTI_LINE;
//	
//	/* EXTIΪ�ж�ģʽ */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* �������ж� */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  /* ʹ���ж� */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	
//  /*--------------------------KEY2����-----------------------------*/
//	/* ѡ�񰴼��õ���GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB2_INT_GPIO_PIN;
//  /* ����Ϊ�������� */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB2_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* ѡ��EXTI���ź�Դ */
//  GPIO_EXTILineConfig(KEYB2_INT_EXTI_PORTSOURCE, KEYB2_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB2_INT_EXTI_LINE;
//	
//	/* EXTIΪ�ж�ģʽ */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* �½����ж� */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* ʹ���ж� */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	  /*--------------------------KEY3����-----------------------------*/
//			/*��������GPIO�ڵ�ʱ��*/
//	RCC_APB2PeriphClockCmd(KEYB3_INT_GPIO_CLK,ENABLE);
//	/* ѡ�񰴼��õ���GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB2_INT_GPIO_PIN;
//  /* ����Ϊ�������� */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB3_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* ѡ��EXTI���ź�Դ */
//  GPIO_EXTILineConfig(KEYB3_INT_EXTI_PORTSOURCE, KEYB3_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB3_INT_EXTI_LINE;
//	
//	/* EXTIΪ�ж�ģʽ */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* �½����ж� */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* ʹ���ж� */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	  /*--------------------------KEY4����-----------------------------*/
//	/* ѡ�񰴼��õ���GPIO */	
//  GPIO_InitStructure.GPIO_Pin = KEYB4_INT_GPIO_PIN;
//  /* ����Ϊ�������� */	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(KEYB4_INT_GPIO_PORT, &GPIO_InitStructure);

//	/* ѡ��EXTI���ź�Դ */
//  GPIO_EXTILineConfig(KEYB4_INT_EXTI_PORTSOURCE, KEYB4_INT_EXTI_PINSOURCE); 
//  EXTI_InitStructure.EXTI_Line = KEYB4_INT_EXTI_LINE;
//	
//	/* EXTIΪ�ж�ģʽ */
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	/* �½����ж� */
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  /* ʹ���ж� */	
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//}
