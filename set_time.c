#include <xc.h>
#include "main.h"

/*
 * Variables shared with the Timer0 ISR.
 * Define these variables only once in main.c.
 */
extern volatile unsigned int set_time_blink_count;
extern volatile unsigned char set_time_blink_state;
extern volatile unsigned char set_time_blink_update;
extern volatile unsigned char set_time_blink_enable;


/* Convert decimal to BCD for the DS1307 */
static unsigned char decimal_to_bcd(unsigned char value)
{
    return ((value / 10) << 4) | (value % 10);
}


/* Convert BCD from the DS1307 to decimal */
static unsigned char bcd_to_decimal(unsigned char value)
{
    return ((value >> 4) * 10) + (value & 0x0F);
}


/*
 * field:
 * 0 -> Seconds
 * 1 -> Minutes
 * 2 -> Hours
 *
 * blink_on:
 * 1 -> Show selected field
 * 0 -> Blank selected field
 */
static void display_set_time(unsigned char hour,unsigned char minute,unsigned char second,unsigned char field,unsigned char blink_on)
{
    /* Hours: positions 0 and 1 */
    if ((field == 2) && (blink_on == 0))
    {
        clcd_putch(' ', LINE2(4));
        clcd_putch(' ', LINE2(5));
    }
    else
    {
        clcd_putch((hour / 10) + '0', LINE2(4));
        clcd_putch((hour % 10) + '0', LINE2(5));
    }

    clcd_putch(':', LINE2(6));

    /* Minutes: positions 3 and 4 */
    if ((field == 1) && (blink_on == 0))
    {
        clcd_putch(' ', LINE2(7));
        clcd_putch(' ', LINE2(8));
    }
    else
    {
        clcd_putch((minute / 10) + '0', LINE2(7));
        clcd_putch((minute % 10) + '0', LINE2(8));
    }

    clcd_putch(':', LINE2(9));

    /* Seconds: positions 6 and 7 */
    if ((field == 0) && (blink_on == 0))
    {
        clcd_putch(' ', LINE2(10));
        clcd_putch(' ', LINE2(11));
    }
    else
    {
        clcd_putch((second / 10) + '0', LINE2(10));
        clcd_putch((second % 10) + '0', LINE2(11));
    }
}


void set_time(void)
{
    unsigned char clock_reg[3];

    unsigned char hour;
    unsigned char minute;
    unsigned char second;

    unsigned char field = 0;
    unsigned char key;
    unsigned char redraw = 1;

    /*
     * Read the current RTC time.
     * clock_reg[0] = hour
     * clock_reg[1] = minute
     * clock_reg[2] = second
     */
    read_ds1307_time(clock_reg);

    hour   = bcd_to_decimal(clock_reg[0] & 0x3F);
    minute = bcd_to_decimal(clock_reg[1] & 0x7F);
    second = bcd_to_decimal(clock_reg[2] & 0x7F);

    /*
     * Start blinking.
     * Seconds blink first.
     */
    set_time_blink_count = 0;
    set_time_blink_state = 1;
    set_time_blink_update = 0;
    set_time_blink_enable = 1;

    clcd_clear();
    clcd_print("SET TIME", LINE1(4));

    display_set_time(hour, minute, second, field,
set_time_blink_state);

    while (1)
    {
        redraw = 0;

        /* Scan keypad continuously */
        key = read_matrix_keypad(STATE);

        /* Increment selected field */
        if (key == 1)
        {
            if (field == 0)
            {
                second++;

                if (second >= 60)
                    second = 0;
            }
            else if (field == 1)
            {
                minute++;

                if (minute >= 60)
                    minute = 0;
            }
            else
            {
                hour++;

                if (hour >= 24)
                    hour = 0;
            }

            redraw = 1;
        }

        /* Decrement selected field */
        else if (key == 2)
        {
            if (field == 0)
            {
                if (second == 0)
                    second = 59;
                else
                    second--;
            }
            else if (field == 1)
            {
                if (minute == 0)
                    minute = 59;
                else
                    minute--;
            }
            else
            {
                if (hour == 0)
                    hour = 23;
                else
                    hour--;
            }

            redraw = 1;
        }

        /* Change selected field */
        else if (key == 3)
        {
            /*
             * Seconds -> Minutes -> Hours -> Seconds
             */
            field++;

            if (field >= 3)
                field = 0;

            /* Show the newly selected field immediately */
            set_time_blink_state = 1;
            set_time_blink_count = 0;
            set_time_blink_update = 0;

            redraw = 1;
        }

        /* Save the edited time */
        else if (key == 0)
        {
            /*
             * Disable blinking before saving.
             */
            set_time_blink_enable = 0;
            set_time_blink_count = 0;
            set_time_blink_update = 0;

            write_ds1307(HOUR_ADDR, decimal_to_bcd(hour));

            write_ds1307(MIN_ADDR, decimal_to_bcd(minute));

            write_ds1307(SEC_ADDR, decimal_to_bcd(second));

            clcd_clear();
            clcd_print("TIME SAVED", LINE1(3));

            __delay_ms(1000);

            return;
        }

        /*
         * Redraw immediately after a keypad action.
         */
        if (redraw)
        {
            display_set_time(hour, minute, second, field, set_time_blink_state);
        }

        /*
         * Process the blink flag set by Timer0 ISR.
         * LCD operations must remain outside the ISR.
         */
        if (set_time_blink_update)
        {
            set_time_blink_update = 0;

            display_set_time(hour, minute, second, field, set_time_blink_state);
        }
    }
}