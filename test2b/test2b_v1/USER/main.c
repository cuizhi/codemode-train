#include "sys.h"

typedef struct {
        bool bAutoReset; //事件本身属性-事件自己自动触发bIsSet复位，false:别的事件来触发bIsSet复位 （在这里没体会到用处有多大--|）
        bool bIsSet;  //事件当前状态
    } event_t;

#define PRINT_RESET_FSM()  do{ s_tPrintState = PRINT_START;} while(0);
#define DELAY_RESET_FSM()  do{ s_tDelayState = DELAY_START;} while(0);
#define TASK_PRINT_RESET_FSM()  do{ s_tTaskPrintState = TASK_PRINT_START; } while(0);
#define TASK_DELAY_RESET_FSM()  do{ s_tTaskDelayState = TASK_DELAY_START; } while(0);

#define SET_EVENT(__EVENT)  do{ __EVENT->bIsSet = true; } while(0);
#define WAIT_EVENT(__EVENT)   __EVENT->bIsSet   //此处用于if()中，用于逻辑值判断，不能用return，也不能加分号';'
#define RESET_EVENT(__EVENT)  do{__EVENT->bIsSet = false; }while(0);
#define INIT_EVENT(__EVENT,__INIT_VALUE,__MANUAL)  do{ __EVENT->bIsSet = __INIT_VALUE; __EVENT->bAutoReset = __MANUAL; }while(0);

#define TIME_IDLE        400000  //1s

/*----------breath-led------------*/
#define _BV(bit)     (1 << (bit))
#define ABS(__N)     ((__N) < 0 ? -(__N) : (__N))
#define TOP          (0x01FF)
static void set_led_gradation(uint16_t);
static void breath_led(void);
/*----------------------*/
//! \name finit state machine state
//! @{
typedef enum {
    fsm_rt_err = -1,  //!< fsm error, error code can be get from other interface
    fsm_rt_cpl = 0,    //!< fsm complete
    fsm_rt_on_going = 1,  //!<fsm on-going
} fsm_rt_t;
//! @}



static fsm_rt_t task_print(void);
static fsm_rt_t task_delay(void);
static fsm_rt_t print(void);
static fsm_rt_t delay(void);

static event_t s_tPrintEvent; //本文件可见的全局变量。
static event_t *s_tEvent = &s_tPrintEvent;

/*-main-*/
int main(void)
{
    system_init();
    
    while (1) {
        breath_led();   //!< 呼吸灯任务
        task_print();   //!< 显示任务
        task_delay();   //!< 延时任务
    }
}

static fsm_rt_t task_print(void)
{
    
    static enum{
        TASK_PRINT_START,
        TASK_PRINT_WAIT,
        TASK_PRINT_BUSY
    }s_tTaskPrintState = TASK_PRINT_START;
    
    switch(s_tTaskPrintState){
        case TASK_PRINT_START:
            INIT_EVENT(s_tEvent,false,true);  //对事件进行初始化
            s_tTaskPrintState = TASK_PRINT_WAIT;
        case TASK_PRINT_WAIT:
            if(WAIT_EVENT(s_tEvent)) {  //对事件进行判断，从而决定是否触发打印。
                RESET_EVENT(s_tEvent);
                s_tTaskPrintState = TASK_PRINT_BUSY; 
            }
            break;
        case TASK_PRINT_BUSY:
            if(fsm_rt_cpl == print()){
                TASK_PRINT_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;  
        default:
            break;
    }

    return fsm_rt_on_going;
}

static fsm_rt_t task_delay(void)
{
    static enum{
        TASK_DELAY_START = 0,
        TASK_DELAY_COUNT
    }s_tTaskDelayState = TASK_DELAY_START;
    
    switch(s_tTaskDelayState) {
        case TASK_DELAY_START:
            s_tTaskDelayState = TASK_DELAY_COUNT;
        case TASK_DELAY_COUNT:
            if(fsm_rt_cpl == delay()){
                SET_EVENT(s_tEvent); //事件，这个事件导致了打印的开始
                TASK_DELAY_RESET_FSM();
                return fsm_rt_cpl;
            }
            break;
        default:
            break;
    }
    return fsm_rt_on_going;
}

/*-------------------print()----------------------------*/
static fsm_rt_t print(void)   
{
    static enum {
        PRINT_START = 0,
        PRINT_H ,
        PRINT_O ,
        PRINT_L1 ,
        PRINT_L2 ,
        PRINT_E ,
        PRINT_LR ,
        PRINT_LN 
    } s_tPrintState = PRINT_START;
    
    switch(s_tPrintState){
        case PRINT_START:
            s_tPrintState = PRINT_H;      
        case PRINT_H:
            if(serial_out('h')){
                s_tPrintState = PRINT_E;
            }
            break;  
        case PRINT_E:
            if(serial_out('e')){
                s_tPrintState = PRINT_L1;
            }
            break;
        case PRINT_L1:
            if(serial_out('l')){
                s_tPrintState = PRINT_L2;
            }
            break;
        case PRINT_L2:
            if(serial_out('l')){
                s_tPrintState = PRINT_O;
            }
            break;
        case PRINT_O:
            if(serial_out('o')){
                s_tPrintState = PRINT_LR;
            }
            break; 
        case PRINT_LR:
            if(serial_out('\r')){
                s_tPrintState = PRINT_LN;
            }
            break; 
        case PRINT_LN:
            if(serial_out('\n')){
                PRINT_RESET_FSM();  //自身状态机的复位
                return fsm_rt_cpl;  //返回值---状态完成的消息，“hello”发送完成的消息
            }
            break;                 
        default:
            break;
    }
    return fsm_rt_on_going;
}

/*--------------------delay()-----------*/
static fsm_rt_t delay(void)   
{
    static uint32_t s_wTimeIdle = 0; 
    static enum{
        DELAY_START = 0 ,
        DELAY_WAIT
    }s_tDelayState = DELAY_START ;
    
    switch(s_tDelayState){
        case DELAY_START:
            s_wTimeIdle = 0; 
            s_tDelayState = DELAY_WAIT;
        case DELAY_WAIT:
            s_wTimeIdle++;            //在这里进行一些计数工作。
            if( TIME_IDLE <= s_wTimeIdle) {  
                DELAY_RESET_FSM();   //自身状态的复位。
                return fsm_rt_cpl;   //对上层状态机发送完成的消息，延时完成。
            }
            break;
        default:
            break;
    }
    return fsm_rt_on_going;
}

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
/*-----------------------breath_led()--end----------*/

