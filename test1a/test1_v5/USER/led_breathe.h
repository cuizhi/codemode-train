
#ifndef _LED_BREATHE_H_
#define _LED_BREATHE_H_



#define LED_PWM_HIGH 0x01   			//----ÁÁ×´Ì¬--
#define LED_PWM_LOW 0x02        //----Ãð×´Ì¬--

#define LED_BREATHE_UP 0x10        //ºôÎü½¥ÁÁ×´Ì¬
#define LED_BREATHE_DOWN 0x20        //ºôÎü½¥Ãð×´Ì¬

void led_task_breathe(void);


#endif
