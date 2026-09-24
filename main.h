/* 
 * File:   main.h
 * Author: kirut
 *
 * Created on 19 September, 2026, 10:07 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "i2c.h"
#include"ds1307.h"
#include "clcd.h"
#include "adc.h"
#include "matrix_keypad.h"
#include "timer.h"
#include "external_interrupt.h"


void put_data_dashboard(void);
void login_page(void);

#endif	/* MAIN_H */

