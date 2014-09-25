// Header:
// File Name: main.c
// Author: pcbddd
// Date: 2014/8/1

#include "sys.h"
#include "led_breathe.h"

int main(void)
{
    system_init();
  
    //! write your name here  
    while(!serial_out('p')); 
    while(!serial_out('c'));
    while(!serial_out('b'));
    while(!serial_out('d'));
    while(!serial_out('d'));
    while(!serial_out('d'));

    while(!serial_out('\r'));
    while(!serial_out('\n'));	//OK
    
    while (1){
        uint8_t chByte;
        if (IS_KEY1_DOWN()){
            LED1_ON();
        }else{
            LED1_OFF();
        }		
        if (serial_in(&chByte)){
            serial_out(chByte);
        }
        /*--------∫ÙŒ¸µ∆£¨≤‚ ‘OK------*/
        led_task_breathe();
    }
}

