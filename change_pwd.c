#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"

/* Existing password used by login_page() */
extern char org_password[5];

/* EEPROM addresses reserved for the password.
 * Your log metadata currently uses addresses 100?102.
 */

void change_pwd(void)
{
    unsigned char key;
    unsigned char i;
    unsigned char matched;

    char new_password[5];
    char confirm_password[5];

    /* -------------------------------
     * STEP 1: Enter new password
     * ------------------------------- */
    while (1)
    {
        clcd_clear();
        clcd_print("NEW PASSWORD:", LINE1(0));
        clcd_print("____", LINE2(6));

        i = 0;

        while (i < 4)
        {
            key = read_matrix_keypad(STATE);

            if (key == ALL_RELEASED)
            {
                continue;
            }

            /* SW4: Back to menu */
            if (key == '*')
            {
                clcd_clear();
                return;
            }

            /* Accept only numeric digits */
            if (key <= 9)
            {
                new_password[i] = key + '0';

                clcd_putch('*', LINE2(6 + i));

                i++;
            }
        }

        new_password[4] = '\0';

        /* -------------------------------
         * STEP 2: Confirm new password
         * ------------------------------- */
        clcd_clear();
        clcd_print("CONFIRM PASSWORD", LINE1(0));
        clcd_print("____", LINE2(6));

        i = 0;

        while (i < 4)
        {
            key = read_matrix_keypad(STATE);

            if (key == ALL_RELEASED)
            {
                continue;
            }

            /* SW4: Cancel password change */
            if (key == '*')
            {
                clcd_clear();
                return;
            }

            if (key <= 9)
            {
                confirm_password[i] = key + '0';

                clcd_putch('*', LINE2(6 + i));

                i++;
            }
        }

        confirm_password[4] = '\0';

        /* -------------------------------
         * STEP 3: Compare passwords
         * ------------------------------- */
        matched = 1;

        for (i = 0; i < 4; i++)
        {
            if (new_password[i] != confirm_password[i])
            {
                matched = 0;
                break;
            }
        }

        if (matched)
        {
            /* Update password used by login */
            for (i = 0; i < 4; i++)
            {
                org_password[i] = new_password[i];

                /* Save each digit in EEPROM */
                eeprom_write(
                    PASSWORD_EEPROM_ADDR + i,
                    new_password[i]
                );
            }

            org_password[4] = '\0';

            clcd_clear();
            clcd_print("PASSWORD CHANGED", LINE1(0));
            clcd_print("SUCCESSFULLY", LINE2(2));

            __delay_ms(1000);

            return;
        }
        else
        {
            clcd_clear();
            clcd_print("PASSWORD", LINE1(4));
            clcd_print("MISMATCH!", LINE2(4));

            __delay_ms(1000);

            /* Retry from entering a new password */
        }
    }
}

