#ifndef __MOTOR_STEERING_CHANGE_H
#define __MOTOR_STEERING_CHANGE_H

#include "stm32f10x.h"

#define speed_increase_mode  0
#define speed_reduce_mode    1

void motor_steering_change(void);
void motor2_steering_change(void);
void motor3_steering_change(void);
#endif /*__BSP_MOTOR_STEERING_CHANGE_H*/

