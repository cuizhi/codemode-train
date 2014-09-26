// Header:
// File Name: sys.c
// Author: pcbddd
// Date: 2014/8/1

#include "sys.h"

void system_init(void)
{
    uart_init();
    led_init();
    key_init();
}

