// Header:
// File Name: led.c
// Author: cz
// Date: 2014/8/1

#include "led.h"

void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    /*----�˿�ʱ�ӳ�ʼ��APB2----*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
    /*----GPIO��LED����ʼ��----*/
    //LED1:PB5
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);
	
    //LED2:PE5
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED2;
    GPIO_Init(GPIO_PORT_LED2, &GPIO_InitStructure);
}


