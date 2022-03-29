#include "uart.h"

//void Init_UART(void)
//{
//  USART_InitTypeDef	USART_InitStructure;
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  NVIC_InitTypeDef  NVIC_InitStructure;
//  //ʹ��GPIOAʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3; //RXD ���Ŷ˿�PA3����
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		    
//  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;  //TXD ���Ŷ˿�PA2����
//  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);	
//  //ʹ��USART1ʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
//  USART_DeInit(USART1);  //���ڸ�λ
//  USART_InitStructure.USART_BaudRate  = 9600;
//  USART_InitStructure.USART_WordLength= USART_WordLength_8b;//8������λ
//  USART_InitStructure.USART_StopBits  = USART_StopBits_1;   //1��ֹͣλ
//  USART_InitStructure.USART_Parity    = USART_Parity_No ;   //�޼�żУ��
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
//  USART_InitStructure.USART_Mode      = USART_Mode_Rx|USART_Mode_Tx;   
//  USART_Init(USART1, &USART_InitStructure);     //���ڳ�ʼ��
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܴ��ڽ����ж�
//  USART_Cmd(USART1, ENABLE);             //ʹ�ܴ���
//  USART_ClearFlag(USART1,USART_FLAG_TXE);//������ͱ�־
//  // �ж����ȼ�����
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
//  NVIC_Init(&NVIC_InitStructure);
//}

//void SendOneByte(unsigned char dat)
//{
//  USART_SendData(USART2,dat);
//  while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
//  USART_ClearFlag(USART2,USART_FLAG_TXE);
//}


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);		

  // ���������ɱ�־
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}

/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}