// Header:
// File Name: key.c
// Author: cz
// Date: 2014/8/1

#include "key.h"

void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*------clock APB2--------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟

    /*-------GPIO:pin/mode/speed--------------*/
    //KEY1:PE3
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIO_PORT_KEY1,&GPIO_InitStructure);

    //KEY2:PE2
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY1;
    GPIO_Init(GPIO_PORT_KEY2,&GPIO_InitStructure);
}
	

