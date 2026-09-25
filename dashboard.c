//#include "main.h"
//
//extern unsigned int i;
//
//extern unsigned char key;
//
//char event[9][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5", "_C"};
//
//static void display_time(unsigned char *clock_reg)
//{
//    //BCD Format 
//    //clock_reg[0] = HH
//    //clock_reg[1] = MM
//    //clock_reg[2] = SS
//   
//    /* To store the time in HH:MM:SS format */
//    char time[9];  // "HH:MM:SS"
//    // HH -> 
//    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
//    time[1] = (clock_reg[0] & 0x0F) + '0';
//    
//    time[2] = ':';
//    // MM 
//    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
//    time[4] = (clock_reg[1] & 0x0F) + '0';
//    
//    time[5] = ':';
//    // SS
//    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
//    time[7] = (clock_reg[2] & 0x0F) + '0';
//    time[8] = '\0';
//    
//    clcd_print(time, LINE2(1)); // HH:MM:SS 
//}
//
//static void get_time(unsigned char *clock_reg)
//{
//    read_ds1307_time(clock_reg);
//}
//
//void put_data_dashboard()
//{
//
//    clcd_print("   Time    E  SP", LINE1(0));
//    clcd_print(event[i], LINE2(11));
//
//    unsigned short adc_reg_val;
//    unsigned char clock_reg[3];
//    unsigned char key;
//
//    get_time(clock_reg);
//    display_time(clock_reg);
//
//    adc_reg_val = ((unsigned long)read_adc() * 99) / 1023;
//
//    char speed_1 = (adc_reg_val / 10) + '0';
//    char speed_2 = (adc_reg_val % 10) + '0';
//
//    clcd_putch(speed_1, LINE2(14));
//    clcd_putch(speed_2, LINE2(15));
//}
//
#include "main.h"


/*----------------------------------------------------------
 * EXTERNAL VARIABLES
 *----------------------------------------------------------*/

/*
 * 'i' represents the current event/gear index.
 *
 * It is defined in main.c, but we need to use it here,
 * so we declare it as extern.
 *
 * Example:
 *
 *      i = 0  -> "ON"
 *      i = 1  -> "GN"
 *      i = 2  -> "GR"
 *      i = 3  -> "G1"
 *      ...
 *      i = 7  -> "G5"
 *      i = 8  -> "_C"
 */
extern unsigned int i;


/*
 * 'key' is the keypad value.
 *
 * It is defined elsewhere and declared here because this
 * file may need access to the current keypad value.
 */
extern unsigned char key;


/*----------------------------------------------------------
 * EVENT / GEAR TABLE
 *----------------------------------------------------------*/

/*
 * This is a 2-dimensional character array.
 *
 * There are 9 event/gear strings:
 *
 *      event[0] = "ON"
 *      event[1] = "GN"
 *      event[2] = "GR"
 *      event[3] = "G1"
 *      event[4] = "G2"
 *      event[5] = "G3"
 *      event[6] = "G4"
 *      event[7] = "G5"
 *      event[8] = "_C"
 *
 * Each string contains 2 visible characters + '\0'.
 *
 * Therefore each row needs 3 characters.
 *
 * Example:
 *
 *      event[i]
 *
 * If:
 *
 *      i = 3
 *
 * then:
 *
 *      event[i] = "G1"
 *
 * This value is displayed on the dashboard.
 */
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


/*----------------------------------------------------------
 * DISPLAY TIME FUNCTION
 *----------------------------------------------------------*/

/*
 * Converts the RTC time from BCD format into normal
 * ASCII characters and displays it on the LCD.
 *
 * Input:
 *
 *      clock_reg[0] -> Hours
 *      clock_reg[1] -> Minutes
 *      clock_reg[2] -> Seconds
 *
 * DS1307 stores time in BCD format.
 *
 * Example:
 *
 *      25 seconds is stored as:
 *
 *          0x25
 *
 * Binary:
 *
 *          0010 0101
 *           2    5
 *
 * We need to convert this into the ASCII characters:
 *
 *          '2' and '5'
 *
 * so that the LCD can display:
 *
 *          25
 */
static void display_time(unsigned char *clock_reg)
{
    /*
     * DS1307 stores the time in BCD format.
     *
     * clock_reg[0] = HH
     * clock_reg[1] = MM
     * clock_reg[2] = SS
     */


    /*
     * Create a character array to store the time
     * in the format:
     *
     *      HH:MM:SS
     *
     * 8 visible characters:
     *
     *      H H : M M : S S
     *
     * plus one '\0' character.
     *
     * Therefore:
     *
     *      char time[9];
     */
    char time[9];


    /*------------------------------------------------------
     * HOURS
     *------------------------------------------------------*/

    /*
     * clock_reg[0] contains hours in BCD.
     *
     * Example:
     *
     *      0x23
     *
     * Binary:
     *
     *      0010 0011
     *
     * Upper nibble = 2
     * Lower nibble = 3
     */


    /*
     * Extract the upper nibble.
     *
     *      clock_reg[0] >> 4
     *
     * moves the upper 4 bits to the lower 4 bits.
     *
     * Example:
     *
     *      0010 0011
     *          >>
     *      0000 0010
     *
     * & 0x03 keeps only the required hour bits.
     *
     * Finally:
     *
     *      + '0'
     *
     * converts the numerical digit into its ASCII character.
     *
     * Example:
     *
     *      2 + '0' = '2'
     */
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';


    /*
     * Extract the lower nibble of the hour.
     *
     *      clock_reg[0] & 0x0F
     *
     * keeps only the lower 4 bits.
     *
     * Example:
     *
     *      0x23
     *
     *      0010 0011
     *          &
     *      0000 1111
     *      ----------
     *      0000 0011
     *
     * Result = 3
     *
     * + '0' converts 3 into ASCII '3'.
     */
    time[1] = (clock_reg[0] & 0x0F) + '0';


    /*
     * Position 2 is the ':' between hours and minutes.
     */
    time[2] = ':';


    /*------------------------------------------------------
     * MINUTES
     *------------------------------------------------------*/

    /*
     * Extract the upper nibble of minutes.
     *
     * Example:
     *
     *      0x45
     *
     * represents 45 minutes in BCD.
     *
     * Upper nibble = 4.
     */
    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';


    /*
     * Extract the lower nibble of minutes.
     *
     * Example:
     *
     *      0x45
     *
     * lower nibble = 5.
     *
     * + '0' converts it to ASCII '5'.
     */
    time[4] = (clock_reg[1] & 0x0F) + '0';


    /*
     * Position 5 is the ':' between minutes and seconds.
     */
    time[5] = ':';


    /*------------------------------------------------------
     * SECONDS
     *------------------------------------------------------*/

    /*
     * Extract the upper nibble of seconds.
     *
     * Example:
     *
     *      0x37
     *
     * upper nibble = 3.
     */
    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';


    /*
     * Extract the lower nibble of seconds.
     *
     * Example:
     *
     *      0x37
     *
     * lower nibble = 7.
     */
    time[7] = (clock_reg[2] & 0x0F) + '0';


    /*
     * C strings must end with '\0'.
     *
     * Without this, clcd_print() would not know where
     * the string ends.
     */
    time[8] = '\0';


    /*
     * Display the complete time on LCD line 2,
     * starting at position 1.
     *
     * So:
     *
     *      LINE2(1)
     *
     * gives:
     *
     *      _HH:MM:SS
     *
     * where the first LCD position is left empty.
     */
    clcd_print(time, LINE2(1));
}


/*----------------------------------------------------------
 * GET TIME FUNCTION
 *----------------------------------------------------------*/

/*
 * Reads the current time from the DS1307 RTC.
 *
 * The actual I2C communication is handled by:
 *
 *      read_ds1307_time()
 *
 * This function is kept separate so that the dashboard
 * code does not need to know the details of the I2C
 * communication.
 */
static void get_time(unsigned char *clock_reg)
{
    /*
     * Read:
     *
     *      seconds
     *      minutes
     *      hours
     *
     * from DS1307 and store them in clock_reg.
     */
    read_ds1307_time(clock_reg);
}


/*----------------------------------------------------------
 * DASHBOARD DISPLAY FUNCTION
 *----------------------------------------------------------*/

/*
 * This function updates the car black box dashboard.
 *
 * The dashboard contains:
 *
 *      Time
 *      Event / Gear
 *      Speed
 *
 * Example display:
 *
 *      Time      E  SP
 *      12:35:27  G3 65
 */
void put_data_dashboard()
{
    /*------------------------------------------------------
     * DASHBOARD HEADING
     *------------------------------------------------------*/

    /*
     * Display the labels on the first LCD line.
     *
     * LCD line 1:
     *
     *      "   Time    E  SP"
     *
     * Meaning:
     *
     *      Time -> current RTC time
     *      E    -> event/gear
     *      SP   -> speed
     */
    clcd_print("   Time    E  SP", LINE1(0));


    /*
     * Display the current event/gear.
     *
     * 'i' determines which event is selected.
     *
     * Example:
     *
     *      i = 3
     *
     *      event[3] = "G1"
     *
     * Therefore "G1" is displayed at LCD position 11.
     */
    clcd_print(event[i], LINE2(11));


    /*------------------------------------------------------
     * LOCAL VARIABLES
     *------------------------------------------------------*/

    /*
     * ADC result.
     *
     * PIC16F877A ADC is 10-bit.
     *
     * Therefore the ADC result ranges from:
     *
     *      0 to 1023
     *
     * unsigned short is sufficient to hold this value.
     */
    unsigned short adc_reg_val;


    /*
     * Array to store:
     *
     *      clock_reg[0] -> hours
     *      clock_reg[1] -> minutes
     *      clock_reg[2] -> seconds
     */
    unsigned char clock_reg[3];


    /*
     * Local keypad variable.
     *
     * Note: this variable is declared here but is not used
     * anywhere in this function.
     */
    unsigned char key;


    /*------------------------------------------------------
     * READ AND DISPLAY RTC TIME
     *------------------------------------------------------*/

    /*
     * Read the current time from DS1307.
     *
     * After this function:
     *
     *      clock_reg[0] = hours
     *      clock_reg[1] = minutes
     *      clock_reg[2] = seconds
     */
    get_time(clock_reg);


    /*
     * Convert the BCD values into ASCII characters
     * and display HH:MM:SS on the LCD.
     */
    display_time(clock_reg);


    /*------------------------------------------------------
     * READ ADC AND CONVERT TO SPEED
     *------------------------------------------------------*/

    /*
     * Read the 10-bit ADC value from the potentiometer.
     *
     * ADC result:
     *
     *      0       -> minimum potentiometer position
     *      1023    -> maximum potentiometer position
     */
    adc_reg_val = ((unsigned long)read_adc() * 99) / 1023;


    /*
     * Convert the speed value into two individual
     * ASCII characters.
     *
     * The speed range is:
     *
     *      0 to 99
     *
     * Example:
     *
     *      adc_reg_val = 65
     *
     *      65 / 10 = 6
     *
     *      65 % 10 = 5
     *
     * Therefore:
     *
     *      speed_1 = '6'
     *      speed_2 = '5'
     *
     * and the LCD displays:
     *
     *      65
     */
    char speed_1 = (adc_reg_val / 10) + '0';
    char speed_2 = (adc_reg_val % 10) + '0';


    /*
     * Display the tens digit of speed.
     *
     * LINE2(14) means LCD line 2, position 14.
     *
     * Example:
     *
     *      speed = 65
     *
     *      speed_1 = '6'
     *
     * so '6' is displayed here.
     */
    clcd_putch(speed_1, LINE2(14));


    /*
     * Display the units digit of speed.
     *
     * LINE2(15) is the next LCD position.
     *
     * Example:
     *
     *      speed = 65
     *
     *      speed_2 = '5'
     *
     * so '5' is displayed here.
     */
    clcd_putch(speed_2, LINE2(15));
}