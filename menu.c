#include <xc.h>
#include "main.h"

const char menu_items[5][17] =
{
    "View Log",
    "Clear Log",
    "Download Log",
    "Set Time",
    "Change Password"
};

void menu_page(void)
{
    unsigned char key;
    unsigned char menu_index = 0;
    unsigned char previous_index = 255;

    while (1)
    {
        if (menu_index != previous_index)
        {
            clcd_print("                ", LINE1(0));
            clcd_print("                ", LINE2(0));

            if (menu_index < 4)
            {
                clcd_putch('*', LINE1(0));
                clcd_print(menu_items[menu_index], LINE1(1));

                clcd_putch(' ', LINE2(0));
                clcd_print(menu_items[menu_index + 1], LINE2(1));
            }
            else
            {
                clcd_putch(' ', LINE1(0));
                clcd_print(menu_items[3], LINE1(1));

                clcd_putch('*', LINE2(0));
                clcd_print(menu_items[4], LINE2(1));
            }

            previous_index = menu_index;
        }

        key = read_matrix_keypad(STATE);

        /*
         * SCROLL UP
         */
        if (key == 1)
        {
            if (menu_index > 0)
            {
                menu_index--;
            }
        }

        /*
         * SCROLL DOWN
         */
        else if (key == 2)
        {
            if (menu_index < 4)
            {
                menu_index++;
            }
        }
        
        if(key == 3)
        {
            clcd_clear();
            put_data_dashboard();
            return ;
         }    

        /*
         * SELECT
         */
        else if (key == '#')
        {
            switch (menu_index)
            {
                case 0:
                    /* View Log */
                    break;

                case 1:
                    /* Clear Log */
                    break;

                case 2:
                    /* Download Log */
                    break;

                case 3:
                    /* Set Time */
                    break;

                case 4:
                    /* Change Password */
                    break;
            }
        }
    }
}

