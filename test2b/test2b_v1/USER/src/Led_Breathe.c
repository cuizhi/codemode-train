// Header:
// File Name: usart.c
// Author: pcbddd
// Date: 2014/8/1

#include "sys.h"
#include "led_breathe.h"

void led_task_breathe(void)
{
    static uint8_t s_chLedPwmState = LED_PWM_HIGH; //初始化PWM至高
    static uint8_t s_chLedBreatheState = LED_BREATHE_UP; //初始渐亮
    static uint16_t s_hwLedCnt = 0;  //计数单步
    static uint16_t s_hwLedPwm = 0;  //占空比

    switch (s_chLedPwmState){
    //----亮状态--//亮-计数到ledpwm-跳至灭状态  高：0~ledpwm  低：ledpwm~800
    case LED_PWM_HIGH:
        LED2_ON();
        if(s_hwLedPwm == s_hwLedCnt){
            s_chLedPwmState = LED_PWM_LOW;  //下降沿
        }
        break;
			
    //----灭状态--
    case LED_PWM_LOW:
        LED2_OFF();
        if(800 == s_hwLedCnt){
            s_hwLedCnt = 0; 
            s_chLedPwmState = LED_PWM_HIGH; //上升沿(后一个PWM周期)
				
            /***********************占空比调节**************************************/
            //占空比达到100%---亮度达到峰值 //第一次写的800，最亮状态时，闪烁了一下；改成799就OK了
            if(799 == s_hwLedPwm){
                s_chLedBreatheState = LED_BREATHE_DOWN;
            }
            if(1 == s_hwLedPwm){
                s_chLedBreatheState = LED_BREATHE_UP;
            }
				
            if(LED_BREATHE_UP == s_chLedBreatheState){
                s_hwLedPwm++;      //提高亮的占空比--亮度提升
            }
            else if (LED_BREATHE_DOWN == s_chLedBreatheState){
                s_hwLedPwm--;      //降低亮的占空比--亮度下降
            }
            /**********************************************************************/  
        }
        break;
		
    default:
        break;
    }
    s_hwLedCnt++;	
}

