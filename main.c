#include <xc.h>
#include "main.h"
#include "external_interrupt.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned int crt = 0;

unsigned int i = 0;

extern char event[9][3];

extern volatile unsigned char one_second_flag;

unsigned char key;

static void init_config(void) {
    init_i2c(100000); //100K
    init_ds1307();
    
    init_clcd();
    init_adc();
    init_timer0();
    
    init_matrix_keypad();
    
    GIE = 1;
    PEIE = 1;
    
    clcd_print("Time", LINE1(3));
    clcd_print("E", LINE1(11));
    clcd_print("SP" , LINE1(14));
    clcd_print("ON", LINE2(11));
}

void main(void)
{
    unsigned char clock_reg[3]; // HH MM SS
                                // 0  1  2


    

    init_config();

    while (1)
    {
        
        if(one_second_flag)
        {
            one_second_flag = 0;
            put_data_dashboard();
        }
        
        key = read_matrix_keypad(STATE);

        if(key == 4)
        {
            login_page();
        }
        else if(key == 1)
        {
            i = 8;
            clcd_print(event[i], LINE2(11));
        }
        else if(key == 2)
        {
            if(i < 7)
            {
                i++;
                clcd_print(event[i], LINE2(11));
            }
        }
        else if(key == 3)
        {
            if(i > 1)
            {
                i--;
                clcd_print(event[i], LINE2(11));
            }
        }
        
        
    }

    return;
}


