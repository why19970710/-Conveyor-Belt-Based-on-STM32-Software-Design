#ifndef __BSP_EXTI_KEY_H
#define __BSP_EXTI_KEY_H
#include "stm32f10x.h"

#define KEY1_GPIO_PORT_Clock        RCC_APB2Periph_GPIOA
#define KEY1_GPIO_PORT              GPIOA
#define KEY1_PIN                    GPIO_Pin_0
#define KEY1_EXTI_GPIO_PortSource   GPIO_PortSourceGPIOA
#define KEY1_EXTI_GPIO_PinSource    GPIO_PinSource0
#define KEY1_EXTI_LINE              EXTI_Line0
#define KEY1_EXTI_IRQn              EXTI0_IRQn
#define KEY1_EXTI_IRQHandler        EXTI0_IRQHandler

void KEY_EXTI_Config(void);

#endif /*__BSP_EXTI_KEY_H*/
