
#include "sys.h"

/*--------test1a（）宏定义----------------------*/
#define TIME_IDLE        400000  //1s

#define START      0x00    //发送准备
#define SEND_H     0x01    //'h'
#define SEND_O     0x02    //'o'
#define SEND_L1    0x03    //'l'
#define SEND_L2    0x04    //'l'
#define SEND_E     0x05    //'e'
#define SEND_LR    0x06    //'\r'
#define SEND_LN    0x07    //'\n'
#define SEND_WAIT  0x08    //发送等待

#define SEND_RESET_FSM()  do{ s_chSendState = START;}while(0); //状态复位

/*---------------------------------*/
#define _BV(bit)     (1 << (bit))
#define ABS(__N)     ((__N) < 0 ? -(__N) : (__N))

#define TOP          (0x01FF)



/*! \brief set the 16-level led gradation
 *! \param hwLevel gradation
 *! \return none
 */
static void set_led_gradation(uint16_t hwLevel)
{
    static uint16_t s_hwCounter = 0;
    
    if (hwLevel >= s_hwCounter) {
        LED1_ON();
    } else {
        LED1_OFF();
    }
    
    s_hwCounter++;
    s_hwCounter &= TOP;
}

static void breath_led(void)
{
    static uint16_t s_hwCounter = 0;
    static int16_t s_nGray = (TOP >> 1);
                    
    s_hwCounter++;
    if (!(s_hwCounter & (_BV(10)-1))) {
        s_nGray++; 
        if (s_nGray == TOP) {
            s_nGray = 0;
        }
    }
    
    set_led_gradation(ABS(s_nGray - (TOP >> 1)));
}
/*-------------------test1a----------------------------*/
static void test1(void)
{
    static uint32_t s_wTimeIdle = 0;
    static uint8_t s_chSendState = START;         
    

    switch(s_chSendState){
        //----------Start
        case START:
            s_wTimeIdle = 0;   //这个状态机中，计数等待部分的计数值初始化
            s_chSendState = SEND_H;
        //----------h
        case SEND_H:
            if(serial_out('h')){
                s_chSendState = SEND_E;
            }
            break;
        //----------e
        case SEND_E:
            if(serial_out('e')){
                s_chSendState = SEND_L1;
            }
            break;
        //----------l
        case SEND_L1:
            if(serial_out('l')){
                s_chSendState = SEND_L2;
            }
            break;
        //----------l
        case SEND_L2:
            if(serial_out('l')){
                s_chSendState = SEND_O;
            }
            break;
        //---------o
        case SEND_O:
            if(serial_out('o')){
                s_chSendState = SEND_LR;
            }
            break; 
        //---------/r
        case SEND_LR:
            if(serial_out('\r')){
                s_chSendState = SEND_LN;
            }
            break; 
        //---------/n
        case SEND_LN:
            if(serial_out('\n')){
                s_chSendState = SEND_WAIT;  //进入发送等待
            }
            break;                 
        case SEND_WAIT:
            s_wTimeIdle++;
            if( TIME_IDLE <= s_wTimeIdle) {               
                SEND_RESET_FSM();//状态复位
            }
            break;
        default:
            break;
    }
}

int main(void)
{
    system_init();
    
    while (1) {
        breath_led(); 
        test1();  
    }
}

