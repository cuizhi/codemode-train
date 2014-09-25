// Header:
// File Name: usart.c
// Author: pcbddd
// Date: 2014/8/1

#include "sys.h"
#include "led_breathe.h"

void led_task_breathe(void)
{
    static uint8_t s_chLedPwmState = LED_PWM_HIGH; //��ʼ��PWM����
    static uint8_t s_chLedBreatheState = LED_BREATHE_UP; //��ʼ����
    static uint16_t s_hwLedCnt = 0;  //��������
    static uint16_t s_hwLedPwm = 0;  //ռ�ձ�

    switch (s_chLedPwmState){
    //----��״̬--//��-������ledpwm-������״̬  �ߣ�0~ledpwm  �ͣ�ledpwm~800
    case LED_PWM_HIGH:
        LED2_ON();
        if(s_hwLedPwm == s_hwLedCnt){
            s_chLedPwmState = LED_PWM_LOW;  //�½���
        }
        break;
			
    //----��״̬--
    case LED_PWM_LOW:
        LED2_OFF();
        if(800 == s_hwLedCnt){
            s_hwLedCnt = 0; 
            s_chLedPwmState = LED_PWM_HIGH; //������(��һ��PWM����)
				
            /***********************ռ�ձȵ���**************************************/
            //ռ�ձȴﵽ100%---���ȴﵽ��ֵ //��һ��д��800������״̬ʱ����˸��һ�£��ĳ�799��OK��
            if(799 == s_hwLedPwm){
                s_chLedBreatheState = LED_BREATHE_DOWN;
            }
            if(1 == s_hwLedPwm){
                s_chLedBreatheState = LED_BREATHE_UP;
            }
				
            if(LED_BREATHE_UP == s_chLedBreatheState){
                s_hwLedPwm++;      //�������ռ�ձ�--��������
            }
            else if (LED_BREATHE_DOWN == s_chLedBreatheState){
                s_hwLedPwm--;      //��������ռ�ձ�--�����½�
            }
            /**********************************************************************/  
        }
        break;
		
    default:
        break;
    }
    s_hwLedCnt++;	
}

