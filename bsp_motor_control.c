#include "./motor-control/bsp_motor_control.h"

void motor_control_Config(void)
{
	
/*----��ʼ��TB6612����������ϵ�AIN1��AIN2����----*/
	/*��ʼ��AIN�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(AIN_GPIO_PORT_Clock,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	/*��ʼ��AIN1����*/
	GPIO_InitStruct.GPIO_Pin = AIN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*��ʼ��AIN1�˿�*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);
	
		/*��ʼ��AIN2����*/
	GPIO_InitStruct.GPIO_Pin = AIN2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*��ʼ��AIN2�˿�*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);



/************ͨ�ö�ʱ��TIM3��������************/
  GPIO_InitTypeDef GPIO_InitStructure;

// ����Ƚ�ͨ��1 GPIO ��ʼ�� [��ֲʱ���Ը���ʵ�������GPIO����]
  /*��ʼ��ͨ��1�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE); 
	/*��ʼ��ͨ��1����*/
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	/*��ʼ��ͨ��1�˿�*/
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	
//��ʼ��TIM3
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	//TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
	extern volatile uint16_t CCR1_Val; //PWM��ռ�ձȳ�ʼֵΪ80%
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
	//ʹ��TIM3�Զ���װ��
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM, ENABLE);
	
	//���˳ʱ��ת��
	AIN1_ON;
	AIN2_OFF;

}
