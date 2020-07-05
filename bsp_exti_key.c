#include "./key/bsp_exti_key.h"
#include "./basetime/bsp_basetime.h"
#include "./motor_steering_change/bsp_motor_steering_change.h"

static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*��һ���������ж����ȼ��ķ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/*�ڶ���������NVIC��ʼ���ṹ��*/
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	/*������������NVIC��ʼ�����������úõĽṹ��д���Ĵ�����*/
	NVIC_Init(&NVIC_InitStruct);
}

void KEY_EXTI_Config(void)
{ 
  /************************************
   ��һ������ʼ��Ҫ���ӵ�EXTI��KEY_GPIO
  *************************************/ 	
	GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;	
	
	NVIC_Config();
	
	/*��ʼ��KEY1�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_PORT_Clock,ENABLE);
	/*��ʼ��KEY1����*/
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*��ʼ��KEY1�˿�*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
	/**********************
   �ڶ�������ʼ��EXTI����
   **********************/

	/*��ʼ�����ù��ܵ�AFIO����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*��PAO���ӵ�EXTI��*/
	GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PortSource,KEY1_EXTI_GPIO_PinSource);
	
	/*��ʼ��EXTI����ṹ��*/
	EXTI_InitStruct.EXTI_Line     = KEY1_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger  = EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	/*����EXTI��ʼ����������EXTI��ʼ���ṹ��д��Ĵ�����*/
	EXTI_Init(&EXTI_InitStruct);
	
}



/*
* �Ժ��жϷ�������÷ŵ���Ӧ��.c�ļ��У��簴�����ⲿ�жϾͷŵ������������ļ��У�
*	bsp_exit_key.c
*/

/*EXTI�ⲿ�жϷ�����*/
volatile uint16_t time = 0; //����ʱ�䣬��λΪms����ʼֵΪ0
volatile uint32_t Press_and_release = 1;//�����ɿ���ʶ������ʼֵΪ1

/*�����⺬������֣�Ҫʹ�ú궨��*/
#define		KEY_PRESS			1
#define 	KEY_RELEASE		0	

void KEY1_EXTI_IRQHandler(void)
{
	
  if(EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)//�������º�TIM6��ʼ����
	{
		switch(Press_and_release)
		{
			case KEY_PRESS:
				time = 0;//time��0
				TIM_Cmd(BASIC_TIM, ENABLE);//����TIM6
			  Press_and_release = !Press_and_release;//��ʱPress_and_release��ֵ��Ϊ0
			break;
			
			case KEY_RELEASE:
				TIM_Cmd(BASIC_TIM, DISABLE);//�ر�TIM6
			  Press_and_release = !Press_and_release;//��ʱPress_and_release��ֵ��Ϊ1
			  motor_steering_change();
			break;
			
			default: break;
		}
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}
