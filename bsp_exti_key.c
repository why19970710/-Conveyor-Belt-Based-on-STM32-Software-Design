#include "./key/bsp_exti_key.h"
#include "./basetime/bsp_basetime.h"
#include "./motor_steering_change/bsp_motor_steering_change.h"

static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*第一步：配置中断优先级的分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/*第二步：配置NVIC初始化结构体*/
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	/*第三步：调用NVIC初始化函数把配置好的结构体写到寄存器里*/
	NVIC_Init(&NVIC_InitStruct);
}

void KEY_EXTI_Config(void)
{ 
  /************************************
   第一步：初始化要连接到EXTI的KEY_GPIO
  *************************************/ 	
	GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;	
	
	NVIC_Config();
	
	/*初始化KEY1端口时钟*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_PORT_Clock,ENABLE);
	/*初始化KEY1引脚*/
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*初始化KEY1端口*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	
	/**********************
   第二步：初始化EXTI外设
   **********************/

	/*初始化复用功能的AFIO配置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*将PAO连接到EXTI中*/
	GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PortSource,KEY1_EXTI_GPIO_PinSource);
	
	/*初始化EXTI外设结构体*/
	EXTI_InitStruct.EXTI_Line     = KEY1_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger  = EXTI_Trigger_Rising_Falling;
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	/*调用EXTI初始化函数，将EXTI初始化结构体写入寄存器里*/
	EXTI_Init(&EXTI_InitStruct);
	
}



/*
* 以后中断服务函数最好放到对应的.c文件中，如按键的外部中断就放到按键的配置文件中：
*	bsp_exit_key.c
*/

/*EXTI外部中断服务函数*/
volatile uint16_t time = 0; //计数时间，单位为ms，初始值为0
volatile uint32_t Press_and_release = 1;//按下松开标识符，初始值为1

/*有特殊含义的数字，要使用宏定义*/
#define		KEY_PRESS			1
#define 	KEY_RELEASE		0	

void KEY1_EXTI_IRQHandler(void)
{
	
  if(EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)//按键按下后TIM6开始计数
	{
		switch(Press_and_release)
		{
			case KEY_PRESS:
				time = 0;//time清0
				TIM_Cmd(BASIC_TIM, ENABLE);//启动TIM6
			  Press_and_release = !Press_and_release;//此时Press_and_release的值变为0
			break;
			
			case KEY_RELEASE:
				TIM_Cmd(BASIC_TIM, DISABLE);//关闭TIM6
			  Press_and_release = !Press_and_release;//此时Press_and_release的值变为1
			  motor_steering_change();
			break;
			
			default: break;
		}
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
	}
}
