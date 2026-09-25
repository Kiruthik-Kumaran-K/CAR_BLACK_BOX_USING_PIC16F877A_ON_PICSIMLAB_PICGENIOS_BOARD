# 1 "dashboard.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "dashboard.c" 2
# 63 "dashboard.c"
# 1 "./main.h" 1
# 11 "./main.h"
# 1 "./i2c.h" 1





void init_i2c(unsigned long baud);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
unsigned char i2c_read(unsigned char ack);
int i2c_write(unsigned char data);
# 12 "./main.h" 2
# 1 "./ds1307.h" 1
# 12 "./ds1307.h"
void init_ds1307(void);
unsigned char read_ds1307(unsigned char addr);
void write_ds1307(unsigned char addr, unsigned char data);
void read_ds1307_time(unsigned char *clock_reg);
# 13 "./main.h" 2
# 1 "./clcd.h" 1
# 29 "./clcd.h"
void init_clcd(void);
void clcd_putch(const char data, unsigned char addr);
void clcd_print(const char *str, unsigned char addr);
void clcd_clear(void);
# 14 "./main.h" 2
# 1 "./adc.h" 1
# 11 "./adc.h"
void init_adc(void);
unsigned short read_adc(void);
# 15 "./main.h" 2
# 1 "./matrix_keypad.h" 1
# 31 "./matrix_keypad.h"
unsigned char read_matrix_keypad(unsigned char mode);
void init_matrix_keypad(void);
# 16 "./main.h" 2
# 1 "./timer.h" 1
# 11 "./timer.h"
void init_timer0(void);
# 17 "./main.h" 2
# 1 "./menu.h" 1



void menu_page(void);
# 18 "./main.h" 2




void put_data_dashboard(void);
void login_page(void);
# 64 "dashboard.c" 2
# 86 "dashboard.c"
extern unsigned int i;
# 95 "dashboard.c"
extern unsigned char key;
# 135 "dashboard.c"
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
# 184 "dashboard.c"
static void display_time(unsigned char *clock_reg)
{
# 211 "dashboard.c"
    char time[9];
# 259 "dashboard.c"
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
# 283 "dashboard.c"
    time[1] = (clock_reg[0] & 0x0F) + '0';





    time[2] = ':';
# 307 "dashboard.c"
    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
# 321 "dashboard.c"
    time[4] = (clock_reg[1] & 0x0F) + '0';





    time[5] = ':';
# 343 "dashboard.c"
    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
# 355 "dashboard.c"
    time[7] = (clock_reg[2] & 0x0F) + '0';
# 364 "dashboard.c"
    time[8] = '\0';
# 381 "dashboard.c"
    clcd_print(time, (0xC0 + 1));
}
# 400 "dashboard.c"
static void get_time(unsigned char *clock_reg)
{
# 411 "dashboard.c"
    read_ds1307_time(clock_reg);
}
# 433 "dashboard.c"
void put_data_dashboard()
{
# 452 "dashboard.c"
    clcd_print("   Time    E  SP", (0x80 + 0));
# 468 "dashboard.c"
    clcd_print(event[i], (0xC0 + 11));
# 486 "dashboard.c"
    unsigned short adc_reg_val;
# 496 "dashboard.c"
    unsigned char clock_reg[3];
# 505 "dashboard.c"
    unsigned char key;
# 521 "dashboard.c"
    get_time(clock_reg);






    display_time(clock_reg);
# 543 "dashboard.c"
    adc_reg_val = ((unsigned long)read_adc() * 99) / 1023;
# 571 "dashboard.c"
    char speed_1 = (adc_reg_val / 10) + '0';
    char speed_2 = (adc_reg_val % 10) + '0';
# 588 "dashboard.c"
    clcd_putch(speed_1, (0xC0 + 14));
# 604 "dashboard.c"
    clcd_putch(speed_2, (0xC0 + 15));
}
