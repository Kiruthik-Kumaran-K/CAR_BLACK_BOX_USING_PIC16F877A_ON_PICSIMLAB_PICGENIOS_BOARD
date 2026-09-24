#include <xc.h>
#include "i2c.h"
#include "DS1307.h"

void init_ds1307(void)
{
    unsigned char dummy;
   
    dummy = read_ds1307(SEC_ADDR);
    dummy = dummy & 0x7F;
    write_ds1307(SEC_ADDR, dummy);// ch = 0
}

unsigned char read_ds1307(unsigned char addr)
{
    unsigned char data;
    
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(SLAVE_READ);
    data = i2c_read(0);
    i2c_stop();
    
    return data;
}

void write_ds1307(unsigned char addr, unsigned char data) // SEc_ADDR, data
{
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_write(data);
    i2c_stop();
}

void read_ds1307_time(unsigned char *clock_reg)
{
    unsigned char sec;
    unsigned char min;
    unsigned char hour;

    i2c_start();

    i2c_write(SLAVE_WRITE);
    i2c_write(SEC_ADDR);

    i2c_rep_start();

    i2c_write(SLAVE_READ);

    sec = i2c_read(1);
    min = i2c_read(1);
    hour = i2c_read(0);

    i2c_stop();

    clock_reg[0] = hour;
    clock_reg[1] = min;
    clock_reg[2] = sec;
}
