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

#define PASSWORD_LENGTH 4
#define LOG_INDEX_ADDR    100
#define LOG_COUNT_ADDR    101
#define OLDEST_INDEX_ADDR 102


void put_data_dashboard(void);
void login_page(void);
void menu_page(void);
void view_log(void);
void clear_log(void);
void set_time(void);

#endif	/* MAIN_H */

