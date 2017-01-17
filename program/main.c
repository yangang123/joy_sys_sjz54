//*****************************************************************
// Author       : MING
// Time         : 20150327
// Description  : Just for fun.
//*****************************************************************
#include "main.h"






void main (void)
{

    // system init
    DelayMs (100);
    SystemInit ();
    SystemStart ();



    // Welcome
    //Welcome (); 
    LCD_BKL = 1;

    // Main
    while (1)
    {


        //*********************************************************
        //*********** Loop1: main display menu process **********//
        //*********************************************************
        // Figure AAA Redraw
        FigureAaaInit ();
        // Figure AAA Refresh
        while (1)
        {
            // tick check
            TickChk ();


            // tick process
            if (tick_inc)
            {
                // 1. temp & humi refresh
                SensorRefresh ();

                // 2. time refresh
                if (rtc_ud_flag != 0)
                {
                    RtcLoadTime (pRTC);
                    LcdDrawTime ();
                                        rtc_ud_flag = 0;
                }

                // 3. check key
                KeyScan ();
                if (KEY_ENTER_up == 1)
                {
                    break;
                }
                
                // backlight
                if ((pRTC->hour >= 19) && (pRTC->hour <= 23))//OPEN TIME
                    lcd_bkl_time_flag = 1;
                else
                    lcd_bkl_time_flag = 0;
                
                
                
                // time change
                if ((lcd_bkl_time_flag_bak==0) && (lcd_bkl_time_flag==1))
                {
                    LCD_BKL = 0;
                }
                else if ((lcd_bkl_time_flag_bak==1) && (lcd_bkl_time_flag==0))
                {
                    LCD_BKL = 1;
                }
                else
                {
                    if (KEY_UP_up == 1)
                        LCD_BKL = 0;
                    if (KEY_DOWN_up == 1)
                        LCD_BKL = 1;
                    if (lcd_bkl_time_flag == 0)
                    {
                        if (LCD_BKL == 0)
                        {
                            bkl_time = bkl_time + tick_inc*SYSTEM_TICK;
                            if (bkl_time > 10000)
                            {
                                LCD_BKL = 1;
                                bkl_time = 0;
                            }
                        }
                        else
                        {
                            bkl_time = 0;
                        }
                    }
                }
                lcd_bkl_time_flag_bak = lcd_bkl_time_flag;
            }
        }
        //*********************************************************












        //*********************************************************
        //********* Loop2: key response and menu process ********//
        //*********************************************************
        // Figure BBB Redraw
        FigureBbbInit ();
        MenuInit ();
        MenuShow ();
        // Figure BBB Process
        while (1)
        {
            // tick check
            TickChk ();



            // tick process
            if (tick_inc)
            {
                // Sleep Time
                sleep_time = sleep_time + tick_inc*SYSTEM_TICK;
                if (sleep_time > sleep_end)
                {
                    sleep_time = 0;
                    break;
                }


                // check key
                KeyScan ();


                // Menu Refresh
                MenuRefresh ();
                if (sleep_time > sleep_end)
                {
                    sleep_time = 0;
                    break;
                }
            }
        }
        //*********************************************************
    }
}

