
#ifndef _LED_
#define _LED_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define GPIO_PORT_LED1 GPIOB   
#define GPIO_PIN_LED1 GPIO_Pin_5

#define GPIO_PORT_LED2 GPIOE 
#define GPIO_PIN_LED2 GPIO_Pin_5 

#define LED1_ON() do { GPIO_PORT_LED1->BRR = GPIO_PIN_LED1;} while(0);
#define LED1_OFF() do {GPIO_PORT_LED1->BSRR = GPIO_PIN_LED1;} while(0); 
#define LED2_ON() do {GPIO_PORT_LED2->BRR = GPIO_PIN_LED2;} while(0); 
#define LED2_OFF() do {GPIO_PORT_LED2->BSRR = GPIO_PIN_LED2;} while(0); 

void led_init(void);

#endif 


