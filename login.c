//#include <xc.h>
//#include "matrix_keypad.h"
//#include "clcd.h"
//#include "timer.h"
//#include "main.h"
//
//
//
//
//unsigned char key;
//unsigned char index = 0;
//    
//char org_password[5]="1111";
//char usr_password[5];
//    
//char display[17]="                ";
//
//extern volatile unsigned int ms_count;
//extern volatile unsigned char cursor_state;
//
//extern volatile unsigned char cursor_update;
//
//extern volatile unsigned char one_second_flag;
//
//unsigned char inactivity_time = 0;
//
//unsigned char attempts = 0;
//
//int my_strcmp(const char *str1, const char *str2)
//{
//    while (*str1 && *str2)
//    {
//        if (*str1 != *str2)
//        {
//            return 1;
//        }
//
//        str1++;
//        str2++;
//    }
//
//    return (*str1 == *str2) ? 0 : 1;
//}
//
//
//void login_page(void) 
//{
//    clcd_print("ENTER PASSWORD  ",LINE1(0));
//    clcd_print(display,LINE2(0));
//    
//    while (1) 
//    {
//        key = read_matrix_keypad(STATE);
//        if(cursor_update)
//        {
//            cursor_update = 0;
//            if(index < 4)
//            {
//                if(cursor_state)
//            {
//                display[index + 6] = '_';
//            }
//            else
//            {
//                display[index + 6] = ' ';
//            }
//                
//            clcd_print(display, LINE2(0));
//            }
//        }
//        if(key != ALL_RELEASED)
//        {
//            inactivity_time = 0;
//            
//            if(index < 4)
//            {
//                
//               
//               usr_password[index] = key + '0';
//               display[index + 6] = '*';
//               clcd_print(display, LINE2(0));
//               index++;
//               
//               
//               ms_count = 0;
//               cursor_state = 0;
//               
//               clcd_print(display, LINE2(0));
//            }  
//        }
//        
//        if(index == PASSWORD_LENGTH)
//        {
//            usr_password[index] = '\0';
//            attempts++;
//            if(my_strcmp(usr_password, org_password) == 0)
//            {
//                clcd_clear();
//                clcd_print("SUCCESSFUL      ",LINE2(4));
//                
//                    index = 0;
//                    attempts = 0;
//                    
//                    for(int i = 0; i < PASSWORD_LENGTH; i++)
//                    {
//                        usr_password[i] = '\0';
//                    }
//                    
//                    for(int i = 0; i< 17; i++)
//                    {
//                       display[i]=' '; 
//                    }
//                    
//                    
//                    display[6] = '_';
//                
//                __delay_ms(1000);
//                
//                menu_page();
//                
//                return;
//            }else
//            {
//
//                
//                if(attempts >= 3)
//                {
//                    unsigned char lock_time = 60;
//                    unsigned char previous_time = 60;
//
//                    clcd_print("BLOCKED          ", LINE1(0));
//
//                    
//                    clcd_putch((lock_time / 10) + '0', LINE2(6));
//                    clcd_putch((lock_time % 10) + '0', LINE2(7));
//                    clcd_print("Wait for ",LINE2(0));
//                    clcd_putch('s', LINE2(11));
//
//                    while (lock_time > 0)
//                    {
//                        if (one_second_flag)
//                        {
//                            one_second_flag = 0;
//
//                            previous_time = lock_time;
//                            lock_time--;
//
//
//                            if ((lock_time / 10) != (previous_time / 10))
//                            {
//                                clcd_putch((lock_time / 10) + '0', LINE2(9));
//                            }
//
//
//                            if ((lock_time % 10) != (previous_time % 10))
//                            {
//                                clcd_putch((lock_time % 10) + '0', LINE2(10));
//                            }
//                        }
//                    }
//                    
//                    clcd_clear();
//                    
//                    index = 0;
//                    attempts = 0;
//                    
//                    for(int i = 0; i < PASSWORD_LENGTH; i++)
//                    {
//                        usr_password[i] = '\0';
//                    }
//                    
//                    for(int i = 0; i< 17; i++)
//                    {
//                       display[i]=' '; 
//                    }
//                    
//                    
//                    display[6] = '_';
//                    
//                    put_data_dashboard();
//                    
//                    return ;
//                            
//       
//                }
//                
//                if(attempts == 1)
//                {
//                    clcd_print("FAILED ATTEMPT  ",LINE1(0));
//                    clcd_print("2 ATTEMPTS LEFT ",LINE2(0));                   
//                }
//                
//                if(attempts == 2)
//                {
//                    clcd_print("FAILED ATTEMPT  ",LINE1(0));
//                    clcd_print("1 ATTEMPTS LEFT ",LINE2(0));                     
//                }
//                
//                index = 0;
//                
//                for(int i = 0; i < PASSWORD_LENGTH; i++)
//                {
//                    usr_password[i]='\0';
//                    display[i + 6] = ' ';
//                }                
//
//                __delay_ms(1000);
//                
//                clcd_print("ENTER PASSWORD",LINE1(0));
//                clcd_print(display,LINE2(0));                
//            }            
//        }
//        
//        if(one_second_flag)
//        {
//            one_second_flag = 0;
//            
//            if(index < PASSWORD_LENGTH)
//            {
//                inactivity_time++;
//                
//                if(inactivity_time >= 5)
//                {
//                    inactivity_time = 0;
//                    clcd_clear();
//                    put_data_dashboard();
//                    return;
//                }
//                
//            }    
//        }
//        
//       
//        
//    }
//}
#include <xc.h>
#include "matrix_keypad.h"
#include "clcd.h"
#include "timer.h"
#include "main.h"


/*----------------------------------------------------------
 * GLOBAL VARIABLES
 *----------------------------------------------------------*/

/*
 * Stores the key currently read from the matrix keypad.
 *
 * Example:
 *      key = 1  -> key '1' was pressed
 *      key = 4  -> key '4' was pressed
 *      key = 0  -> key '0' was pressed
 *      key = 10 -> depending on keypad driver, this may
 *                  represent '*' or '#'
 */
unsigned char key;


/*
 * 'index' tells us which password position we are currently
 * filling.
 *
 * Password has 4 characters:
 *
 *      index = 0 -> first character
 *      index = 1 -> second character
 *      index = 2 -> third character
 *      index = 3 -> fourth character
 *
 * After entering 4 characters:
 *
 *      index = 4
 *
 * which means password entry is complete.
 */
unsigned char index = 0;


/*
 * Original/correct password stored in the system.
 *
 * Currently the password is:
 *
 *      1 1 1 1
 *
 * '\0' is the string terminating character.
 *
 * Therefore:
 *
 *      org_password[0] = '1'
 *      org_password[1] = '1'
 *      org_password[2] = '1'
 *      org_password[3] = '1'
 *      org_password[4] = '\0'
 */
char org_password[5] = "1111";


/*
 * Stores the password entered by the user.
 *
 * Example:
 *
 * User enters 1234
 *
 * usr_password[] becomes:
 *
 *      ['1']['2']['3']['4']['\0']
 *
 * The array has 5 locations because 4 characters are needed
 * for the password + 1 location for '\0'.
 */
char usr_password[5];


/*
 * This array is used to control what is displayed on
 * the second line of the LCD.
 *
 * It contains 16 visible LCD characters + '\0'.
 *
 * Initially:
 *
 *      "                "
 *       ^--------------^
 *          16 spaces
 *
 * During password entry, characters are replaced.
 *
 * Example:
 *
 *      "      * *       "
 *
 * The '*' characters indicate entered password digits.
 */
char display[17] = "                ";


/*----------------------------------------------------------
 * VARIABLES USED BY TIMER ISR
 *----------------------------------------------------------*/

/*
 * ms_count is maintained by the Timer0 interrupt.
 *
 * It is used for timing operations such as:
 *
 *      - password cursor blinking
 *      - generating the one_second_flag
 *
 * It is declared 'extern' because it is actually defined
 * in another source file, probably isr.c.
 */
extern volatile unsigned int ms_count;


/*
 * cursor_state controls whether the cursor should currently
 * be visible or invisible.
 *
 * Example:
 *
 *      cursor_state = 1 -> show '_'
 *      cursor_state = 0 -> show ' '
 */
extern volatile unsigned char cursor_state;


/*
 * cursor_update is set by the Timer0 ISR whenever it is time
 * to update the blinking cursor.
 *
 * login_page() checks this flag and then updates the LCD.
 */
extern volatile unsigned char cursor_update;


/*
 * one_second_flag is set by the Timer0 ISR approximately
 * once every second.
 *
 * login_page() uses this for:
 *
 *      - 5-second password-entry timeout
 *      - 60-second blocking period
 */
extern volatile unsigned char one_second_flag;


/*----------------------------------------------------------
 * LOGIN-SPECIFIC VARIABLES
 *----------------------------------------------------------*/

/*
 * Counts how many seconds have passed since the user last
 * pressed a key.
 *
 * If it reaches 5 seconds, the login page is exited and
 * the dashboard is displayed again.
 */
unsigned char inactivity_time = 0;


/*
 * Counts the number of incorrect password attempts.
 *
 *      attempts = 0 -> no wrong attempts
 *      attempts = 1 -> one wrong attempt
 *      attempts = 2 -> two wrong attempts
 *      attempts = 3 -> three wrong attempts
 *
 * After 3 wrong attempts, the system is blocked for 60 seconds.
 */
unsigned char attempts = 0;


/*----------------------------------------------------------
 * STRING COMPARISON FUNCTION
 *----------------------------------------------------------*/

/*
 * Compares two strings.
 *
 * str1 -> first string
 * str2 -> second string
 *
 * Return value:
 *
 *      0 -> strings are equal
 *      1 -> strings are different
 *
 * Example:
 *
 *      my_strcmp("1111", "1111") -> 0
 *      my_strcmp("1234", "1111") -> 1
 */
int my_strcmp(const char *str1, const char *str2)
{
    /*
     * Continue comparing until either string reaches
     * the null character '\0'.
     */
    while (*str1 && *str2)
    {
        /*
         * Compare the current characters.
         *
         * Example:
         *
         * str1 -> "1234"
         * str2 -> "1111"
         *
         * First comparison:
         *      '1' == '1'
         *
         * Second comparison:
         *      '2' != '1'
         *
         * Therefore strings are different.
         */
        if (*str1 != *str2)
        {
            return 1;
        }

        /*
         * Move both pointers to the next character.
         */
        str1++;
        str2++;
    }


    /*
     * At this point one or both strings reached '\0'.
     *
     * If both reached '\0' at the same time,
     * the strings are equal.
     *
     * If only one reached '\0', their lengths are different.
     */
    return (*str1 == *str2) ? 0 : 1;
}


/*----------------------------------------------------------
 * LOGIN PAGE
 *----------------------------------------------------------*/

void login_page(void)
{
    /*
     * Display the login heading on LCD line 1.
     */
    clcd_print("ENTER PASSWORD  ", LINE1(0));


    /*
     * Initially display the password entry area.
     *
     * 'display' contains 16 spaces, so the second line
     * initially appears blank.
     */
    clcd_print(display, LINE2(0));


    /*------------------------------------------------------
     * LOGIN LOOP
     *
     * This loop continues until:
     *
     * 1. Correct password is entered
     * 2. User is blocked for 60 seconds
     * 3. User remains inactive for 5 seconds
     *------------------------------------------------------*/
    while (1)
    {
        /*
         * Read the matrix keypad.
         *
         * STATE mode means a key is returned only once
         * when it is pressed.
         */
        key = read_matrix_keypad(STATE);


        /*--------------------------------------------------
         * CURSOR BLINKING
         *--------------------------------------------------*/

        /*
         * The Timer0 ISR sets cursor_update when the cursor
         * needs to change its state.
         *
         * Instead of continuously refreshing the LCD,
         * we update it only when necessary.
         */
        if (cursor_update)
        {
            /*
             * Clear the flag immediately because we are now
             * processing the requested cursor update.
             */
            cursor_update = 0;


            /*
             * Cursor should only be displayed while we are
             * still entering the 4-digit password.
             */
            if (index < 4)
            {
                /*
                 * cursor_state decides whether '_' or ' '
                 * should be displayed.
                 */
                if (cursor_state)
                {
                    /*
                     * Show cursor.
                     *
                     * index + 6 gives the LCD position where
                     * the password characters are displayed.
                     */
                    display[index + 6] = '_';
                }
                else
                {
                    /*
                     * Hide cursor by replacing it with a space.
                     */
                    display[index + 6] = ' ';
                }


                /*
                 * Update the second LCD line with the new
                 * cursor state.
                 */
                clcd_print(display, LINE2(0));
            }
        }


        /*--------------------------------------------------
         * CHECK WHETHER A KEY WAS PRESSED
         *--------------------------------------------------*/

        if (key != ALL_RELEASED)
        {
            /*
             * A key was pressed.
             *
             * Therefore reset the inactivity timer.
             *
             * This means the 5-second timeout starts again
             * from zero whenever the user presses a key.
             */
            inactivity_time = 0;


            /*
             * Only accept password characters while fewer
             * than 4 characters have been entered.
             */
            if (index < 4)
            {
                /*
                 * Convert the keypad number into its ASCII
                 * equivalent.
                 *
                 * Example:
                 *
                 *      key = 1
                 *
                 *      key + '0'
                 *
                 *      1 + ASCII('0')
                 *
                 *      = ASCII('1')
                 *
                 * So usr_password[index] stores a character,
                 * not the integer value.
                 */
                usr_password[index] = key + '0';


                /*
                 * Display '*' instead of the actual password
                 * digit for security.
                 *
                 * Example:
                 *
                 *      User enters 1
                 *
                 * LCD:
                 *
                 *      ______*________
                 */
                display[index + 6] = '*';


                /*
                 * Update LCD immediately so the entered
                 * character appears on screen.
                 */
                clcd_print(display, LINE2(0));


                /*
                 * Move to the next password position.
                 */
                index++;


                /*
                 * Reset the millisecond counter.
                 *
                 * This helps restart the cursor blinking
                 * timing after a key is pressed.
                 */
                ms_count = 0;


                /*
                 * Hide the cursor immediately after entering
                 * a password character.
                 */
                cursor_state = 0;


                /*
                 * Update the LCD again after changing the
                 * cursor state.
                 */
                clcd_print(display, LINE2(0));
            }
        }


        /*--------------------------------------------------
         * CHECK WHETHER 4 PASSWORD CHARACTERS ARE ENTERED
         *--------------------------------------------------*/

        if (index == PASSWORD_LENGTH)
        {
            /*
             * Add the null character at the end.
             *
             * This converts usr_password into a proper C
             * string.
             *
             * Example:
             *
             *      1 1 1 1
             *
             * becomes:
             *
             *      "1111\0"
             */
            usr_password[index] = '\0';


            /*
             * One complete password attempt has now been
             * made.
             *
             * Increase the attempt counter.
             */
            attempts++;


            /*------------------------------------------------
             * CHECK WHETHER PASSWORD IS CORRECT
             *------------------------------------------------*/

            if (my_strcmp(usr_password, org_password) == 0)
            {
                /*
                 * Passwords match.
                 *
                 * Therefore login is successful.
                 */

                /*
                 * Clear the LCD.
                 */
                clcd_clear();


                /*
                 * Display successful message.
                 */
                clcd_print("SUCCESSFUL      ", LINE2(4));


                /*
                 * Reset password index so that the next
                 * login starts from the beginning.
                 */
                index = 0;


                /*
                 * Reset wrong-attempt counter.
                 *
                 * This is important because a successful login
                 * should start a fresh set of 3 attempts later.
                 */
                attempts = 0;


                /*
                 * Clear the entered password array.
                 */
                for (int i = 0; i < PASSWORD_LENGTH; i++)
                {
                    usr_password[i] = '\0';
                }


                /*
                 * Clear the display array.
                 */
                for (int i = 0; i < 17; i++)
                {
                    display[i] = ' ';
                }


                /*
                 * Put the cursor back at the first password
                 * position for the next login.
                 */
                display[6] = '_';


                /*
                 * Keep the successful message on screen for
                 * approximately one second.
                 */
                __delay_ms(1000);


                /*
                 * Password is correct.
                 *
                 * Go to the menu page.
                 */
                menu_page();


                /*
                 * When menu_page() eventually returns,
                 * return from login_page().
                 */
                return;
            }


            /*------------------------------------------------
             * PASSWORD IS WRONG
             *------------------------------------------------*/

            else
            {
                /*
                 * Password did not match.
                 *
                 * First check whether this was the third
                 * incorrect attempt.
                 */
                if (attempts >= 3)
                {
                    /*
                     * User has entered the wrong password
                     * three times.
                     *
                     * Lock the system for 60 seconds.
                     */
                    unsigned char lock_time = 60;


                    /*
                     * Stores the previous value of lock_time.
                     *
                     * We use this to determine which digit
                     * actually changed before updating LCD.
                     */
                    unsigned char previous_time = 60;


                    /*
                     * Display the blocked message.
                     */
                    clcd_print("BLOCKED          ", LINE1(0));


                    /*
                     * Display the initial 60-second value.
                     */
                    clcd_putch((lock_time / 10) + '0', LINE2(6));
                    clcd_putch((lock_time % 10) + '0', LINE2(7));


                    /*
                     * Display "Wait for " on the second line.
                     */
                    clcd_print("Wait for ", LINE2(0));


                    /*
                     * Display the seconds unit.
                     */
                    clcd_putch('s', LINE2(11));


                    /*----------------------------------------
                     * 60-SECOND BLOCKING LOOP
                     *----------------------------------------*/

                    while (lock_time > 0)
                    {
                        /*
                         * Wait until Timer0 generates the
                         * one-second flag.
                         */
                        if (one_second_flag)
                        {
                            /*
                             * Consume the flag.
                             */
                            one_second_flag = 0;


                            /*
                             * Save the old value before
                             * decreasing it.
                             */
                            previous_time = lock_time;


                            /*
                             * Decrease remaining lock time
                             * by one second.
                             */
                            lock_time--;


                            /*
                             * Check whether the tens digit
                             * changed.
                             *
                             * Example:
                             *
                             * 50 -> 49
                             *
                             * tens digit changed:
                             *
                             * 5 -> 4
                             */
                            if ((lock_time / 10) !=
                                (previous_time / 10))
                            {
                                /*
                                 * Update only the tens digit
                                 * on the LCD.
                                 */
                                clcd_putch(
                                    (lock_time / 10) + '0',
                                    LINE2(9)
                                );
                            }


                            /*
                             * Check whether the units digit
                             * changed.
                             *
                             * Example:
                             *
                             * 50 -> 49
                             *
                             * units digit changed:
                             *
                             * 0 -> 9
                             */
                            if ((lock_time % 10) !=
                                (previous_time % 10))
                            {
                                /*
                                 * Update only the units digit.
                                 */
                                clcd_putch(
                                    (lock_time % 10) + '0',
                                    LINE2(10)
                                );
                            }
                        }
                    }


                    /*----------------------------------------
                     * BLOCK PERIOD FINISHED
                     *----------------------------------------*/

                    /*
                     * Clear the LCD.
                     */
                    clcd_clear();


                    /*
                     * Reset password entry position.
                     */
                    index = 0;


                    /*
                     * Reset number of failed attempts.
                     *
                     * User gets 3 fresh attempts after
                     * the 60-second block.
                     */
                    attempts = 0;


                    /*
                     * Clear the stored password.
                     */
                    for (int i = 0; i < PASSWORD_LENGTH; i++)
                    {
                        usr_password[i] = '\0';
                    }


                    /*
                     * Clear the password display.
                     */
                    for (int i = 0; i < 17; i++)
                    {
                        display[i] = ' ';
                    }


                    /*
                     * Put the cursor at the first password
                     * position.
                     */
                    display[6] = '_';


                    /*
                     * Return to the dashboard.
                     */
                    put_data_dashboard();


                    /*
                     * Exit login_page().
                     */
                    return;
                }


                /*--------------------------------------------
                 * FIRST WRONG ATTEMPT
                 *--------------------------------------------*/

                if (attempts == 1)
                {
                    /*
                     * Tell the user that the password failed
                     * and that two attempts remain.
                     */
                    clcd_print(
                        "FAILED ATTEMPT  ",
                        LINE1(0)
                    );

                    clcd_print(
                        "2 ATTEMPTS LEFT ",
                        LINE2(0)
                    );
                }


                /*--------------------------------------------
                 * SECOND WRONG ATTEMPT
                 *--------------------------------------------*/

                if (attempts == 2)
                {
                    /*
                     * Tell the user that only one attempt
                     * remains.
                     */
                    clcd_print(
                        "FAILED ATTEMPT  ",
                        LINE1(0)
                    );

                    clcd_print(
                        "1 ATTEMPTS LEFT ",
                        LINE2(0)
                    );
                }


                /*
                 * Reset password position so the user can
                 * enter another password from the beginning.
                 */
                index = 0;


                /*
                 * Clear the previously entered password and
                 * remove the '*' characters from the LCD
                 * display array.
                 */
                for (int i = 0; i < PASSWORD_LENGTH; i++)
                {
                    usr_password[i] = '\0';
                    display[i + 6] = ' ';
                }


                /*
                 * Keep the failed-attempt message visible
                 * for approximately one second.
                 */
                __delay_ms(1000);


                /*
                 * Return to the password-entry screen.
                 */
                clcd_print("ENTER PASSWORD", LINE1(0));
                clcd_print(display, LINE2(0));
            }
        }


        /*--------------------------------------------------
         * 5-SECOND INACTIVITY TIMEOUT
         *--------------------------------------------------*/

        /*
         * Check whether one second has passed.
         *
         * This flag is generated by the Timer0 ISR.
         */
        if (one_second_flag)
        {
            /*
             * Consume the flag.
             */
            one_second_flag = 0;


            /*
             * Only count inactivity while the user has not
             * completed the password.
             */
            if (index < PASSWORD_LENGTH)
            {
                /*
                 * One more second of inactivity has passed.
                 */
                inactivity_time++;


                /*
                 * If the user has not pressed anything for
                 * 5 seconds, leave the login page.
                 */
                if (inactivity_time >= 5)
                {
                    /*
                     * Reset inactivity timer for the next
                     * login attempt.
                     */
                    inactivity_time = 0;


                    /*
                     * Clear login screen.
                     */
                    clcd_clear();


                    /*
                     * Return to dashboard.
                     */
                    put_data_dashboard();


                    /*
                     * Exit login_page().
                     */
                    return;
                }
            }
        }
    }
}
