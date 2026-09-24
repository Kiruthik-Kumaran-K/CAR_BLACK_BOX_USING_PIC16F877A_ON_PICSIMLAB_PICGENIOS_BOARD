#include <xc.h>
#include "timer.h"
#include "main.h"


#define ONE_SECOND_CYCLE 1000

volatile unsigned int ms_count = 0;
volatile unsigned char cursor_state = 1;

volatile unsigned char cursor_update = 0;

volatile unsigned char one_second_flag = 0;

extern unsigned int crt = 0;

extern char display[17];
extern unsigned char index;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    


    if (TMR0IF == 1)
    {
        TMR0 = TMR0 + 100 + 2;

        TMR0IF = 0;
        
        
        
        ms_count++;
        if(ms_count >= ONE_SECOND_CYCLE)
        {
            ms_count = 0;
            one_second_flag = 1;
            if(index < 4)
            {
                cursor_state = !cursor_state;
                cursor_update = 1;
            }
        }   
    }
}



