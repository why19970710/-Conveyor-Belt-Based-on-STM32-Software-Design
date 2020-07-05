#include "motor_steering_change.h"
#include "bsp_exti_key.h"
#include "bsp_motor_control.h"


static uint16_t steering_and_speed_change = 1;//电机转向、转速增/减标识符,初始值为1
static uint16_t speed_change = 1;//电机转速增/减标识符,初始值为1
extern volatile uint16_t time; //计数时间，单位为ms，初始值为0
extern volatile uint16_t Motor_Speed;//PWM波占空比初始值为80%

void motor_steering_change(void)
{
	//TIM_SetCompare1(GENERAL_TIM,0);  // out: pa6
	TIM_SetCompare2(GENERAL_TIM,0);
	TIM_SetCompare3(GENERAL_TIM,0);
	if(time>=1000)//长按，切换blink_time_change_mode值
		{
			TIM_SetCompare1(GENERAL_TIM,Motor_Speed);
			steering_and_speed_change = !(steering_and_speed_change);
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_1;//电机逆时针转动
				Anti_Clockwise_Rotation_2;//电机逆时针转动
			}
			
			else
			{
	      Clockwise_Rotation_1; //电机顺时针转动
				Clockwise_Rotation_2; //电机顺时针转动
			}
		}
		else//短按，改变PWM波占空比
		{
			speed_change = !(speed_change);
			switch(speed_change)//选择电机转速增/减模式
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
	if(time>=1000)//长按，切换blink_time_change_mode值
		{
			TIM_SetCompare2(GENERAL_TIM,Motor_Speed);
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_3;//电机逆时针转动
				Anti_Clockwise_Rotation_4;//电机逆时针转动
			}
			else
			{
	      Clockwise_Rotation_3; //电机顺时针转动
				Clockwise_Rotation_4; //电机顺时针转动
			}
		}
		else//短按，改变PWM波占空比
		{
			speed_change = !(speed_change);
			switch(speed_change)//选择电机转速增/减模式
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
	if(time>=1000)//长按，切换blink_time_change_mode值
		{
			TIM_SetCompare3(GENERAL_TIM,Motor_Speed); 
			steering_and_speed_change = !(steering_and_speed_change);
			
			if(steering_and_speed_change == 0)
			{
	      Anti_Clockwise_Rotation_5;//电机逆时针转动
				Anti_Clockwise_Rotation_6;//电机逆时针转动
			}
			
			else
			{
	      Clockwise_Rotation_5; //电机顺时针转动
				Clockwise_Rotation_6; //电机顺时针转动
			}
		}
		else//短按，改变PWM波占空比
		{
			speed_change = !(speed_change);
			switch(speed_change)//选择电机转速增/减模式
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
