#include "main.h"

extern unsigned int i;

extern unsigned char key;

char event[9][3] =
{
    "ON",
    "GN",
    "GR",
    "G1",
    "G2",
    "G3",
    "G4",
    "G5",
    "_C"
};

static void display_time(unsigned char *clock_reg)
{
    char time[9];

    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';

    time[1] = (clock_reg[0] & 0x0F) + '0';

    time[2] = ':';

    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';

    time[4] = (clock_reg[1] & 0x0F) + '0';

    time[5] = ':';

    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';

    time[7] = (clock_reg[2] & 0x0F) + '0';

    time[8] = '\0';

    clcd_print(time, LINE2(1));
}

static void get_time(unsigned char *clock_reg)
{
    read_ds1307_time(clock_reg);
}

void put_data_dashboard()
{
    clcd_print("   Time    E  SP", LINE1(0));

    clcd_print(event[i], LINE2(11));

    unsigned short adc_reg_val;

    unsigned char clock_reg[3];

    unsigned char key;

    get_time(clock_reg);

    display_time(clock_reg);

    adc_reg_val = ((unsigned long)read_adc() * 99) / 1023;


    char speed_1 = (adc_reg_val / 10) + '0';
    char speed_2 = (adc_reg_val % 10) + '0';


    clcd_putch(speed_1, LINE2(14));

    clcd_putch(speed_2, LINE2(15));
}