#include "motor_steering_change.h"
#include "bsp_exti_key.h"
#include "bsp_motor_control.h"


static uint16_t steering_and_speed_change = 1;//���ת��ת����/����ʶ��,��ʼֵΪ1
static uint16_t speed_change = 1;//���ת����/����ʶ��,��ʼֵΪ1
extern volatile uint16_t time; //����ʱ�䣬��λΪms����ʼֵΪ0
extern volatile uint16_t Motor_Speed;//PWM��ռ�ձȳ�ʼֵΪ80%

void motor_steering_change(void)
{
	//TIM_SetCompare1(GENERAL_TIM,0);  // out: pa6
	TIM_SetCompare2(GENERAL_TIM,0);
	TIM_SetCompare3(GENERAL_TIM,0);
	if(time>=1000)//�������л�blink_time_change_modeֵ
		{
			TIM_SetCompare1(GENERAL_TIM,Motor_Speed);
			steering_and_speed_change = !(steering_and_speed_change);
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_1;//�����ʱ��ת��
				Anti_Clockwise_Rotation_2;//�����ʱ��ת��
			}
			
			else
			{
	      Clockwise_Rotation_1; //���˳ʱ��ת��
				Clockwise_Rotation_2; //���˳ʱ��ת��
			}
		}
		else//�̰����ı�PWM��ռ�ձ�
		{
			speed_change = !(speed_change);
			switch(speed_change)//ѡ����ת����/��ģʽ
			{
				case speed_increase_mode:
					Motor_Speed = 9;
					TIM_SetCompare1(GENERAL_TIM,Motor_Speed);  // out: pa6 
					break;				
				case speed_reduce_mode:
					Motor_Speed = 5;
					TIM_SetCompare1(GENERAL_TIM,Motor_Speed);  // out: pa6 
					break;		
				default:  break;
			}	
		}
		time = 0;
}


void motor2_steering_change(void)
{
	TIM_SetCompare1(GENERAL_TIM,0);  
	//TIM_SetCompare2(GENERAL_TIM,0);
	TIM_SetCompare3(GENERAL_TIM,0);
	if(time>=1000)//�������л�blink_time_change_modeֵ
		{
			TIM_SetCompare2(GENERAL_TIM,Motor_Speed);
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_3;//�����ʱ��ת��
				Anti_Clockwise_Rotation_4;//�����ʱ��ת��
			}
			else
			{
	      Clockwise_Rotation_3; //���˳ʱ��ת��
				Clockwise_Rotation_4; //���˳ʱ��ת��
			}
		}
		else//�̰����ı�PWM��ռ�ձ�
		{
			speed_change = !(speed_change);
			switch(speed_change)//ѡ����ת����/��ģʽ
			{
				case speed_increase_mode:
					Motor_Speed = 9;
					TIM_SetCompare2(GENERAL_TIM,Motor_Speed);  // out: pa7 
					break;
				
				case speed_reduce_mode:
					Motor_Speed = 5;
					TIM_SetCompare2(GENERAL_TIM,Motor_Speed);  // out: pa7 
					break;
				default:  break;
			}	
		}

		time = 0;
}

void motor3_steering_change(void)
{
	TIM_SetCompare1(GENERAL_TIM,0);  
	TIM_SetCompare2(GENERAL_TIM,0);
	//TIM_SetCompare3(GENERAL_TIM,0);
	if(time>=1000)//�������л�blink_time_change_modeֵ
		{
			TIM_SetCompare3(GENERAL_TIM,Motor_Speed); 
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_5;//�����ʱ��ת��
				Anti_Clockwise_Rotation_6;//�����ʱ��ת��
			}
			
			else
			{
	      Clockwise_Rotation_5; //���˳ʱ��ת��
				Clockwise_Rotation_6; //���˳ʱ��ת��
			}
		}
		else//�̰����ı�PWM��ռ�ձ�
		{
			speed_change = !(speed_change);
			switch(speed_change)//ѡ����ת����/��ģʽ
			{
				case speed_increase_mode:
					Motor_Speed = 9;
					TIM_SetCompare3(GENERAL_TIM,Motor_Speed);  // out: pb0
					break;			
				case speed_reduce_mode:
					Motor_Speed = 5;
					TIM_SetCompare3(GENERAL_TIM,Motor_Speed);  // out: pb0 
					break;
				default:  break;
			}	
		}
		time = 0;
}
