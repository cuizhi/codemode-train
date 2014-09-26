#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define NULL (void*)0

#define GPIO_PORT_USART1TX GPIOA
#define GPIO_PIN_USART1TX GPIO_Pin_9

#define GPIO_PORT_USART1RX GPIOA
#define GPIO_PIN_USART1RX GPIO_Pin_10

typedef enum {
    false = 0,
    true = !false
} bool;


bool serial_out(uint8_t chByte);
bool serial_in(uint8_t *pchByte);

void uart_init(void);

#endif


