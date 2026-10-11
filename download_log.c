#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "uart.h"

/* Log metadata from main.c */
extern unsigned char log_count;
extern unsigned char oldest_index;

void download_log(void)
{
    unsigned char offset;
    unsigned char slot;
    unsigned char address;
    unsigned char i;
    unsigned char data;

    /* Check whether any logs exist */
    if (log_count == 0)
    {
        clcd_clear();
        clcd_print("NO LOGS FOUND", LINE1(1));
        __delay_ms(1000);
        return;
    }

    clcd_clear();
    clcd_print("DOWNLOADING...", LINE1(1));

    /* Send CSV header to the laptop */
    puts("TIME,EVENT,SPEED\r\n");

    /* Read logs from oldest to newest */
    for (offset = 0; offset < log_count; offset++)
    {
        slot = oldest_index + offset;

        /* Handle circular-buffer wraparound */
        if (slot >= 10)
        {
            slot -= 10;
        }

        address = slot * 10;

        /* Send HH */
        for (i = 0; i < 2; i++)
        {
            data = eeprom_read(address + i);
            putchar(data);
        }

        putchar(':');

        /* Send MM */
        for (i = 2; i < 4; i++)
        {
            data = eeprom_read(address + i);
            putchar(data);
        }

        putchar(':');

        /* Send SS */
        for (i = 4; i < 6; i++)
        {
            data = eeprom_read(address + i);
            putchar(data);
        }

        putchar(',');

        /* Send event code */
        putchar(eeprom_read(address + 6));
        putchar(eeprom_read(address + 7));

        putchar(',');

        /* Send speed */
        putchar(eeprom_read(address + 8));
        putchar(eeprom_read(address + 9));

        /* Move to next line in terminal */
        puts("\r\n");
    }

    clcd_clear();
    clcd_print("LOGS DOWNLOADED", LINE1(0));

    __delay_ms(1000);
}


