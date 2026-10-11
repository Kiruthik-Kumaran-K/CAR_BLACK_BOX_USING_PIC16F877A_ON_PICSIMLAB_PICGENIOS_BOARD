#include <xc.h>
#include "main.h"

extern unsigned char log_index;
extern unsigned char log_count;
extern unsigned char oldest_index;

void clear_log(void)
{

    log_index = 0;

    log_count = 0;

    oldest_index = 0;


    eeprom_write(LOG_INDEX_ADDR, log_index);
    eeprom_write(LOG_COUNT_ADDR, log_count);
    eeprom_write(OLDEST_INDEX_ADDR, oldest_index);


    clcd_clear();

    clcd_print("LOG CLEARED", LINE1(2));

    __delay_ms(1000);

    clcd_clear();
    return;
}
