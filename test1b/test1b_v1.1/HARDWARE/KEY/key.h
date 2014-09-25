
#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define GPIO_PORT_KEY1 GPIOE
#define GPIO_PIN_KEY1 GPIO_Pin_3

#define GPIO_PORT_KEY2 GPIOE 
#define GPIO_PIN_KEY2 GPIO_Pin_2

#define IS_KEY1_DOWN() (!(GPIO_PORT_KEY1->IDR & GPIO_PIN_KEY1))
#define IS_KEY2_DOWN() (!(GPIO_PORT_KEY2->IDR & GPIO_PIN_KEY2))

#define IS_KEY1_UP() (GPIO_PORT_KEY1->IDR & GPIO_PIN_KEY1)
#define IS_KEY2_UP() (GPIO_PORT_KEY2->IDR & GPIO_PIN_KEY2)


void key_init(void);

#endif
