// Header:
// File Name: usart.c
// Author: pcbddd
// Date: 2014/8/1

#include "usart.h"	  

/*-------------init----------*/
void uart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    USART_InitTypeDef USART_InitStructure;
    		
    /*----PeriphClock------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);   //串口USART2时钟开启
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //串口USART2输入输出端口时钟开启
		
    /*----GPIO_InitStructure----------------------------------*/
    //USART1_TX:PA9
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_USART1TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出TX
    GPIO_Init(GPIO_PORT_USART1TX, &GPIO_InitStructure);
	
    //USART1_RX:PA10
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_USART1RX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //悬浮输入RX
    GPIO_Init(GPIO_PORT_USART1RX, &GPIO_InitStructure); 
	
    /*------USART_InitStructure------------------------------*/
    USART_InitStructure.USART_BaudRate = 9600 ;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b ;
    USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
    USART_Init(USART1, &USART_InitStructure);
	
    USART_Cmd(USART1, ENABLE);
    /*--if use IT?-------*/
	
    /*----other---------*/

}

/*-----------user---------------*/
/*--------非阻塞的串口单字符发送、接收函数---*/
bool serial_out(uint8_t chByte)
{ 
    if(SET != USART_GetFlagStatus(USART1,USART_FLAG_TC)){
        return false;
    }
    USART_SendData(USART1,chByte);
	
    return true;
}

bool serial_in(uint8_t *pchByte)
{
    if(NULL == pchByte){
        return false;  
    }
    if(SET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE)){
        *pchByte = USART_ReceiveData(USART1);
        return true;
    }else{
        return false;
    }
}

