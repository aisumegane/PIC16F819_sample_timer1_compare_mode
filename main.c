/*
 * File:   interrupt.c
 * Author: �XMEGANE
 * Mid-Range 8-bit MCUs PIC16F819
 * Created on 2024/03/27, 23:38
 */

#include "config_bits.h"
#include <xc.h>
#include "grobal_macro.h"
#include "grobal_function.h"
#include "register_setup.h"
#include "interrupt.h"


void init(void);

void main(void) {
    init();
    gf_enable_interrupt();
    gf_timer1_start();
    
    while(1)
    {
        
    }   
}

void init(void)
{
    pic819_register_setup();
}
