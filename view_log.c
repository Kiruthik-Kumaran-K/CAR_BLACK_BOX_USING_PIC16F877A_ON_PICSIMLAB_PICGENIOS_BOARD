#include "main.h"
#include <xc.h>

extern unsigned char log_count;
extern unsigned char oldest_index;

void view_log(void)
{
    unsigned char view_index = 0;
    unsigned char slot1;
    unsigned char slot2;
    unsigned char address;
    unsigned char j;
    unsigned char key;

    char record1[11];
    char record2[11];

    if (log_count == 0)
    {
        clcd_clear();
        clcd_print("NO LOGS", LINE1(0));

        __delay_ms(1000);
        return;
    }

    while (1)
    {
        key = read_matrix_keypad(STATE);
        
        slot1 = oldest_index + view_index;

        if (slot1 >= 10)
        {
            slot1 = slot1 - 10;
        }
        address = slot1 * 10;

        for (j = 0; j < 10; j++)
        {
            record1[j] = eeprom_read(address + j);
        }

        record1[10] = '\0';

        clcd_putch(record1[0], LINE1(0));
        clcd_putch(record1[1], LINE1(1));
        clcd_putch(':',       LINE1(2));
        clcd_putch(record1[2], LINE1(3));
        clcd_putch(record1[3], LINE1(4));
        clcd_putch(':',       LINE1(5));
        clcd_putch(record1[4], LINE1(6));
        clcd_putch(record1[5], LINE1(7));

        clcd_putch(' ',       LINE1(8));

        clcd_putch(record1[6], LINE1(9));
        clcd_putch(record1[7], LINE1(10));

        clcd_putch(' ',       LINE1(11));

        clcd_putch(record1[8], LINE1(12));
        clcd_putch(record1[9], LINE1(13));

        if ((view_index + 1) < log_count)
        {
            slot2 = oldest_index + view_index + 1;

            if (slot2 >= 10)
            {
                slot2 = slot2 - 10;
            }

            address = slot2 * 10;

            for (j = 0; j < 10; j++)
            {
                record2[j] = eeprom_read(address + j);
            }

            record2[10] = '\0';

            clcd_putch(record2[0], LINE2(0));
            clcd_putch(record2[1], LINE2(1));
            clcd_putch(':',       LINE2(2));
            clcd_putch(record2[2], LINE2(3));
            clcd_putch(record2[3], LINE2(4));
            clcd_putch(':',       LINE2(5));
            clcd_putch(record2[4], LINE2(6));
            clcd_putch(record2[5], LINE2(7));

            clcd_putch(' ',       LINE2(8));

            clcd_putch(record2[6], LINE2(9));
            clcd_putch(record2[7], LINE2(10));

            clcd_putch(' ',       LINE2(11));

            clcd_putch(record2[8], LINE2(12));
            clcd_putch(record2[9], LINE2(13));
        }
        else
        {

            clcd_print("              ", LINE2(0));
        }

        if (key == 2)
        {
            if ((view_index + 2) < log_count)
            {
                view_index++;
            }
        }

        else if (key == 1)
        {
            if (view_index > 0)
            {
                view_index--;
            }
        }

        if(key == 3)
        {
            clcd_clear();
            return;
        }
    }
}

