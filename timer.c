#include <xc.h>
#include "timer.h"

void init_timer0(void)
{
    /* Setting the internal clock source */
    T0CS = 0;
    
    /* Assinging the prescaler to  Timer */
    PSA = 0;
    
    PS2 = 1;
    
    PS1 = 0;
    
    PS0 = 0;
            
    TMR0 = 100;
    
    /* The timer interrupt is enabled */
    TMR0IE = 1;
}


