#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "timer.h"
#include "main.h"

unsigned char key;

unsigned char index = 0;

char org_password[5] = "1111";

char usr_password[5];

char display[17] = "                ";

extern volatile unsigned int ms_count;

extern volatile unsigned char cursor_state;

extern volatile unsigned char cursor_update;

extern volatile unsigned char one_second_flag;

unsigned char inactivity_time = 0;

unsigned char attempts = 0;

int my_strcmp(const char *str1, const char *str2)
{
 
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return 1;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2) ? 0 : 1;
}

void login_page(void)
{

    clcd_print("ENTER PASSWORD  ", LINE1(0));

    clcd_print(display, LINE2(0));


    while (1)
    {
        
        key = read_matrix_keypad(STATE);

        if (cursor_update)
        {

            cursor_update = 0;

            if (index < 4)
            {

                if (cursor_state)
                {

                    display[index + 6] = '_';
                }
                else
                {

                    display[index + 6] = ' ';
                }
                clcd_print(display, LINE2(0));
            }
        }

        if (key != ALL_RELEASED)
        {

            inactivity_time = 0;


            if (index < 4)
            {
 
                usr_password[index] = key + '0';

                display[index + 6] = '*';

                clcd_print(display, LINE2(0));

                index++;

                ms_count = 0;

                cursor_state = 0;

                clcd_print(display, LINE2(0));
            }
        }

        if (index == PASSWORD_LENGTH)
        {
            usr_password[index] = '\0';

            attempts++;

            if (my_strcmp(usr_password, org_password) == 0)
            {
                clcd_clear();

                clcd_print("SUCCESSFUL      ", LINE2(4));

                index = 0;

                attempts = 0;

                for (int i = 0; i < PASSWORD_LENGTH; i++)
                {
                    usr_password[i] = '\0';
                }

                for (int i = 0; i < 17; i++)
                {
                    display[i] = ' ';
                }

                display[6] = '_';

                __delay_ms(1000);


                menu_page();


                return;
            }
            else
            {
                if (attempts >= 3)
                {
                    unsigned char lock_time = 60;

                    unsigned char previous_time = 60;

                    clcd_print("BLOCKED          ", LINE1(0));

                    clcd_putch((lock_time / 10) + '0', LINE2(6));
                    clcd_putch((lock_time % 10) + '0', LINE2(7));

                    clcd_print("Wait for ", LINE2(0));

                    clcd_putch('s', LINE2(11));

                    while (lock_time > 0)
                    {
                        if (one_second_flag)
                        {
                            one_second_flag = 0;

                            previous_time = lock_time;

                            lock_time--;

                            if ((lock_time / 10) !=
                                (previous_time / 10))
                            {
                                clcd_putch(
                                    (lock_time / 10) + '0',
                                    LINE2(9)
                                );
                            }

                            if ((lock_time % 10) !=
                                (previous_time % 10))
                            {

                                clcd_putch(
                                    (lock_time % 10) + '0',
                                    LINE2(10)
                                );
                            }
                        }
                    }

                    clcd_clear();

                    index = 0;

                    attempts = 0;

                    for (int i = 0; i < PASSWORD_LENGTH; i++)
                    {
                        usr_password[i] = '\0';
                    }

                    for (int i = 0; i < 17; i++)
                    {
                        display[i] = ' ';
                    }

                    display[6] = '_';

                    put_data_dashboard();

                    return;
                }

                if (attempts == 1)
                {
  
                    clcd_print(
                        "FAILED ATTEMPT  ",
                        LINE1(0)
                    );

                    clcd_print(
                        "2 ATTEMPTS LEFT ",
                        LINE2(0)
                    );
                }


                if (attempts == 2)
                {
                    clcd_print(
                        "FAILED ATTEMPT  ",
                        LINE1(0)
                    );

                    clcd_print(
                        "1 ATTEMPTS LEFT ",
                        LINE2(0)
                    );
                }


                index = 0;

                for (int i = 0; i < PASSWORD_LENGTH; i++)
                {
                    usr_password[i] = '\0';
                    display[i + 6] = ' ';
                }

                __delay_ms(1000);

                clcd_print("ENTER PASSWORD", LINE1(0));
                clcd_print(display, LINE2(0));
            }
        }

        if (one_second_flag)
        {

            one_second_flag = 0;

            if (index < PASSWORD_LENGTH)
            {

                inactivity_time++;

                if (inactivity_time >= 5)
                {

                    inactivity_time = 0;

                    clcd_clear();

                    put_data_dashboard();

                    return;
                }
            }
        }
    }
}
