#include <xc.h>
#include "timer.h"
#include "main.h"


#define ONE_SECOND_CYCLE 1000

volatile unsigned int set_time_blink_count = 0;
volatile unsigned char set_time_blink_state = 1;
volatile unsigned char set_time_blink_update = 0;
volatile unsigned char set_time_blink_enable = 0;

volatile unsigned int ms_count = 0;
volatile unsigned int ms_count_cursor = 0;
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
        ms_count_cursor++;
        if(ms_count_cursor >= ONE_SECOND_CYCLE/2)
        {
            ms_count_cursor = 0;
            if(index < 4)
            {
                cursor_state = !cursor_state;
                cursor_update = 1;
            }            
        }
        if(ms_count >= ONE_SECOND_CYCLE)
        {
            ms_count = 0;
            one_second_flag = 1;

        } 
        
        if (set_time_blink_enable)
        {
            set_time_blink_count++;

            if (set_time_blink_count >= 500)
            {
                set_time_blink_count = 0;

                set_time_blink_state = !set_time_blink_state;
                set_time_blink_update = 1;
            }
        }
        else
        {
            set_time_blink_count = 0;
        }
    }
}



