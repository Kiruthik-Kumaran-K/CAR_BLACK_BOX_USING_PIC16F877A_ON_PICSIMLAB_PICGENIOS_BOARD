#include <xc.h>
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned int crt = 0;

unsigned int i = 0;

extern char event[9][3];

extern volatile unsigned char one_second_flag;

unsigned char log_index = 0;
unsigned char log_count = 0;

unsigned char oldest_index = 0;

unsigned char key;

void init_log(void)
{
    log_index = eeprom_read(LOG_INDEX_ADDR);
    log_count = eeprom_read(LOG_COUNT_ADDR);
    oldest_index = eeprom_read(OLDEST_INDEX_ADDR);

    if (log_index >= 10)
    {
        log_index = 0;
    }

    if (log_count > 10)
    {
        log_count = 0;
    }

    if (oldest_index >= 10)
    {
        oldest_index = 0;
    }
}

void save_event(void)
{
        unsigned char clock_reg[3];
        unsigned short adc_value;
        unsigned char speed;
        unsigned char address;

   
        address = log_index * 10;

        read_ds1307_time(clock_reg);

        adc_value = read_adc();

        speed = ((unsigned long)adc_value * 99) / 1023;

        eeprom_write(address + 0,((clock_reg[0] >> 4) & 0x03) + '0');


        /* Hour units */
        eeprom_write(address + 1,(clock_reg[0] & 0x0F) + '0');

        /* Minute tens */
        eeprom_write(address + 2,((clock_reg[1] >> 4) & 0x07) + '0');


        /* Minute units */
        eeprom_write(address + 3, (clock_reg[1] & 0x0F) + '0');

        /* Second tens */
        eeprom_write(address + 4,((clock_reg[2] >> 4) & 0x07) + '0');

        /* Second units */
        eeprom_write(address + 5,(clock_reg[2] & 0x0F) + '0');

        
        eeprom_write(address + 6, event[i][0]);
        eeprom_write(address + 7, event[i][1]);


        eeprom_write(address + 8, (speed / 10) + '0');

        eeprom_write(address + 9, (speed % 10) + '0');


       if (log_count < 10)
       {
           log_count++;
       }
       else
       {
           oldest_index++;

           if (oldest_index >= 10)
           {
               oldest_index = 0;
           }
       }

       log_index++;

       if (log_index >= 10)
       {
           log_index = 0;
       }

       /* Save circular-buffer state permanently */
       eeprom_write(LOG_INDEX_ADDR, log_index);
       eeprom_write(LOG_COUNT_ADDR, log_count);
       eeprom_write(OLDEST_INDEX_ADDR, oldest_index);
}

static void init_config(void) {
    init_i2c(100000); //100K
    init_ds1307();
    
    init_clcd();
    init_adc();
    init_timer0();
    
    init_matrix_keypad();
    init_log();
    init_uart(9600);
    
    GIE = 1;
    PEIE = 1;
    
    clcd_print("Time", LINE1(3));
    clcd_print("E", LINE1(11));
    clcd_print("SP" , LINE1(14));
    load_password();
    put_data_dashboard();
}

void main(void)
{
 
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
            if(i != 8)
            {
                i = 8;
                clcd_print(event[i], LINE2(11));
                save_event();                
            }

        }
        else if(key == 2)
        {
            if(i < 7)
            {
                i++;
                clcd_print(event[i], LINE2(11));
                save_event();
            }
        }
        else if(key == 3)
        {
            if(i > 1)
            {
                i--;
                clcd_print(event[i], LINE2(11));
                save_event();
            }
        }
        
        
    }

    return;
}


