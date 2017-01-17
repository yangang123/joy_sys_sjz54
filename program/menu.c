#include "menu.h"


#define KEY_MIN_GAP             180
#define SET_DATE_BASE           0
#define SET_DATE_Y              0
#define ABOUT_LINES             30



#define CFG_RTC_ADDR_TMOUT      0x33

//*****************************************************************
// Menu Variables
//*****************************************************************
data unsigned char menu_point;
data unsigned char menu_start;
data unsigned char menu_choose;
data unsigned char menu_max;
data struct MenuItem (*pMenu);
//*****************************************************************











//*****************************************************************
// Menu Constant
//*****************************************************************
code unsigned char const_about[ABOUT_LINES][25] = {
"  Joy System            ",
"     XiDian University  ",
" Hardware Info:         ",
"  Version : 1.0         ",
"  Real Time: DS12C887+  ",
"  Sensor : SHT15        ",
"  CPU : STC15W401AS     ",
"  Memory : 256 Bytes    ",
"  Frequency : 6 MHz     ",
"                        ",
" Software Info:         ",
"  Version : 2.1         ",
"  Author : Zwm          ",
"                        ",
"  This funny idea is    ",
"carried out by LBH, and ",
"ZWM implemented most of ",
"it. Hope you'll like.   ",
"                        ",
"  Bugs can be reported  ",
"with the following      ",
"methods. I wish it is   ",
"useless to you forever. ",
" Email:                 ",
"  weakbrother@163.com   ",
" WeiXin:                ",
"  632599362             ",
"                        ",
"  Finished on 20150405! ",
"                        "
};

//*****************************************************************



//*****************************************************************
// Struct
//*****************************************************************
// Main Menu
code struct MenuItem MainMenu[4] = 
{
    // menu[0]
    {
        4,
        "1. Set Time",
        MenuSetTime,
        0,              // children
        0               // parent
    },
    // menu[1]
    {
        4,
        "2. Set Date",
        MenuSetDate,
        0,
        0
    },
    // menu[2]
    {
        4,
        "3. Set System",
        NullSubs,
        SetSystem,
        0
    },
    // menu[3]
    {
        4,
        "4. About",
        About,
        0,
        0
    }
};
// Secondary Menu 1
code struct MenuItem SetSystem[5] = 
{
    // menu[0]
    {
        5,
        "1. Set Timeout",
        SetTimeout,
        0,
        MainMenu
    },
    // menu[1]
    {
        5,
        "2. Set Backlight",
        NullSubs,
        0,
        MainMenu
    },
    // menu[2]
    {
        5,
        "3. Set Relay",
        NullSubs,
        0,
        MainMenu
    },
    // menu[3]
    {
        5,
        "4. Set Mode",
        NullSubs,
        0,
        MainMenu
    },
    // menu[4]
    {
        5,
        "5. Set ABC",
        NullSubs,
        0,
        MainMenu
    }
};
//*****************************************************************






void MenuInit (void)
{
    pMenu           = &MainMenu[0];
    menu_max        = pMenu->MenuCount;
    menu_point      = 0;
    menu_start      = 0;
    menu_choose     = 0;

    sleep_time      = 0;
    sleep_end       = RtcRead (CFG_RTC_ADDR_TMOUT);
    if (sleep_end < 10)
        sleep_end = 10;
    sleep_end       = sleep_end*1000;
}





void MenuShow (void)
{
    // clear all
    LcdClearScreen ();


    // display menu line 1
    LcdDispString (1, 0, pMenu[menu_start].DisplayString);

    // display menu line 2
    menu_max = pMenu[0].MenuCount;
    if (menu_start < (menu_max - 1))
        LcdDispString (1, 1, pMenu[menu_start + 1].DisplayString);
    else
        LcdDispString (1, 1, pMenu[0].DisplayString);

    // display indicator
    if (menu_choose == menu_start)
        LcdDispChar (0, 0, CHAR_CGRAM_ZHI);
    else
        LcdDispChar (0, 1, CHAR_CGRAM_ZHI);

}
//*****************************************************************








void MenuRefresh (void)
{

    //*************************************************************
    // Up Response
    //*************************************************************
    if (KEY_UP_up == 1)
    {
        menu_max = pMenu[0].MenuCount;
        // menu start
        if (menu_start == menu_choose)
        {
            if (menu_start == 0)
                menu_start = menu_max - 1;
            else
                menu_start = menu_start - 1;
        }
        else
        {
            if ((menu_start == (menu_max - 1)) && (menu_choose == 0))
                ;
            else if ((menu_start + 1) == menu_choose)
                ;
            else
                ;   // error
        }
        // menu choose
        if (menu_choose == 0)
            menu_choose = menu_max - 1;
        else
            menu_choose = menu_choose - 1;

        MenuShow ();
    }
    //*************************************************************









    //*************************************************************
    // Down Response
    //*************************************************************
    if (KEY_DOWN_up == 1)
    {
        menu_max = pMenu[0].MenuCount;
        // menu start
        if (menu_start == menu_choose)
            ;   // do null
        else if ((menu_start == (menu_max - 1)) && (menu_choose == 0))
            menu_start = 0;
        else if ((menu_start + 1) == menu_choose)
            menu_start = menu_start + 1;
        else
        {
            ; // error
        }
        // menu choose
        if (menu_choose == (menu_max - 1))
            menu_choose = 0;
        else
            menu_choose = menu_choose + 1;

        MenuShow ();
    }
    //*************************************************************










    //*************************************************************
    // Enter Response
    //*************************************************************
    if (KEY_ENTER_up == 1)
    {
        if (pMenu[menu_choose].ChildrenMenu != 0)   // Next Level Menu
        {
            pMenu = pMenu[menu_choose].ChildrenMenu;
            menu_start = 0;
            menu_choose = 0;
        }
        else                                        // Invoke Menu Function
        {
            pMenu[menu_choose].Subs();
        }

        MenuShow ();
    }
    //*************************************************************






    //*************************************************************
    // Right Response
    //*************************************************************
    if (KEY_RIGHT_up == 1)
    {
        if (pMenu[menu_choose].ChildrenMenu != 0)   // Next Level Menu
        {
            pMenu = pMenu[menu_choose].ChildrenMenu;
            menu_start = 0;
            menu_choose = 0;
        }
        else                                        // Invoke Menu Function
        {
            pMenu[menu_choose].Subs();
        }

        MenuShow ();
    }
    //*************************************************************




    //*************************************************************
    // LEFT Response
    //*************************************************************
    if (KEY_LEFT_up == 1)
    {
        if (pMenu[menu_choose].ParentMenu != 0)     // Up Level Menu
        {
            pMenu = pMenu[menu_choose].ParentMenu;
            menu_start = 0;
            menu_choose = 0;
        }
        else
        {
            sleep_time = 0xFFFF;        // quite
        }

        MenuShow ();
    }
    //*************************************************************

}






//*****************************************************************
// Menu Process Function
//*****************************************************************
void MenuSetTime (void)
{
    // clear all
    LcdClearScreen ();

    // load time
    //set_tmp[0]      = (((pRTC->hour)&0xF0)*10) + ((pRTC->hour)&0x0F);
    //set_tmp[1]      = (((pRTC->min)&0xF0)*10) + ((pRTC->min)&0x0F);
    set_tmp[0]      = pRTC->hour;
    set_tmp[1]      = pRTC->min;
    set_tmp[2]      = 0;
    set_tmp[3]      = 1;    // position: 1: hour; 4: min; 7: sec; 10: Y; 13: N;
    set_tmp[4]      = 0;    // key hold timer
    set_tmp[5]      = 0;    // break flag
    sleep_time      = 0;    // keep in menu time


    // figrue redraw
    // Set Mode: open cursor, close splash
    LcdWriteCmd (LCD1602_CMD_DM_0E);
    // Draw Figure   xx:xx:xx   Y   N
    LcdDispInt (0, 0, set_tmp[0], 0x10);    // hour
    LcdDispChar (2, 0, ':');
    LcdDispInt (3, 0, set_tmp[1], 0x00);    // min
    LcdDispChar (5, 0, ':');
    LcdDispInt (6, 0, set_tmp[2], 0x00);    // sec
    LcdDispChar (10, 0, 'N');
    LcdDispChar (13, 0, 'Y');
    // set cursor
    LcdSetPos (1, 0);



    // key process
    while (1)
    {
        // tick check
        TickChk ();
        if (tick_inc)
        {
            // sleep time
            sleep_time = sleep_time + tick_inc*SYSTEM_TICK;
            //set_tmp[4] = set_tmp[4] + tick_inc*SYSTEM_TICK;
            if (sleep_time > sleep_end)
            {
                // Set Mode: close cursor, close splash
                LcdWriteCmd (LCD1602_CMD_DM_0C);
                set_tmp[5] = 1;    // time out break
                break;
            }


            // key scan
            KeyScan ();



            //*************************************************************
            // Up Response
            //*************************************************************
            if (KEY_UP_ok == 1)
            {
//                if ((KEY_UP_down==1) || ((set_tmp[7]==0) && (set_tmp[4]>KEY_MIN_GAP_FIRST)) || ((set_tmp[7]==1) && (set_tmp[4]>KEY_MIN_GAP)))
//                {
//                    if ((set_tmp[7] == 0) && (set_tmp[4] > KEY_MIN_GAP_FIRST))
//                    {
//                        set_tmp[4] = 0;
//                        set_tmp[7] = 1;
//                    }
//                    else if ((set_tmp[7] == 1) && (set_tmp[4] > KEY_MIN_GAP))
//                    {
//                        set_tmp[4] = 0;
//                    }
                if ((KEY_UP_down==1) || (set_tmp[4]>KEY_MIN_GAP))
                {
                    if (set_tmp[4] > KEY_MIN_GAP)
                        set_tmp[4] = 0;

                    // up process
                    switch (set_tmp[3])
                    {
                        // hour
                        case 1:
                            {
                                if (set_tmp[0] > 22)
                                    set_tmp[0] = 0;
                                else
                                    set_tmp[0] = set_tmp[0] + 1;
                                LcdDispInt (0, 0, set_tmp[0], 0x10);    // hour
                                LcdSetPos (1, 0);
                                break;
                            }
                        // min
                        case 4:
                            {
                                if (set_tmp[1] > 58)
                                    set_tmp[1] = 0;
                                else
                                    set_tmp[1] = set_tmp[1] + 1;
                                LcdDispInt (3, 0, set_tmp[1], 0x00);    // min
                                LcdSetPos (4, 0);
                                break;
                            }
                        // sec
                        case 7:
                            {
                                if (set_tmp[2] > 58)
                                    set_tmp[2] = 0;
                                else
                                    set_tmp[2] = set_tmp[2] + 1;
                                LcdDispInt (6, 0, set_tmp[2], 0x00);    // sec
                                LcdSetPos (7, 0);
                                break;
                            }
                        // others
                        default:
                            {
                                break;
                            }
                    }
                }
            }
            // key press timer
            if ((KEY_UP_down == 1) || (KEY_UP_up == 1))
            {
                set_tmp[4] = 0;
                set_tmp[7] = 0;
            }
            else if (KEY_UP_ok == 1)
            {
                set_tmp[4] = set_tmp[4] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************






            //*************************************************************
            // DOWN Response
            //*************************************************************
            if (KEY_DOWN_ok == 1)
            {
                if ((KEY_DOWN_down == 1) || (set_tmp[4] > KEY_MIN_GAP))
                {
                    if (set_tmp[4] > KEY_MIN_GAP)
                        set_tmp[4] = 0;

                    // down process
                    switch (set_tmp[3])
                    {
                        // hour
                        case 1:
                            {
                                if (set_tmp[0] < 1)
                                    set_tmp[0] = 23;
                                else
                                    set_tmp[0] = set_tmp[0] - 1;
                                LcdDispInt (0, 0, set_tmp[0], 0x10);    // hour
                                LcdSetPos (1, 0);
                                break;
                            }
                        // min
                        case 4:
                            {
                                if (set_tmp[1] < 1)
                                    set_tmp[1] = 59;
                                else
                                    set_tmp[1] = set_tmp[1] - 1;
                                LcdDispInt (3, 0, set_tmp[1], 0x00);    // min
                                LcdSetPos (4, 0);
                                break;
                            }
                        // sec
                        case 7:
                            {
                                if (set_tmp[2] < 1)
                                    set_tmp[2] = 59;
                                else
                                    set_tmp[2] = set_tmp[2] - 1;
                                LcdDispInt (6, 0, set_tmp[2], 0x00);    // sec
                                LcdSetPos (7, 0);
                                break;
                            }
                        // others
                        default:
                            {
                                break;
                            }
                    }
                }
            }
            // key press timer
            if ((KEY_DOWN_down == 1) || (KEY_DOWN_up == 1))
            {
                set_tmp[4] = 0;
            }
            else if (KEY_DOWN_ok == 1)
            {
                set_tmp[4] = set_tmp[4] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************








            //*************************************************************
            // RIGHT Response
            //*************************************************************
            if (KEY_RIGHT_up == 1)
            {
                // right process
                switch (set_tmp[3])
                {
                    // hour
                    case 1:
                        {
                            set_tmp[3] = 4;
                            LcdSetPos (4, 0);
                            break;
                        }
                    // min
                    case 4:
                        {
                            set_tmp[3] = 7;
                            LcdSetPos (7, 0);
                            break;
                        }
                    // sec
                    case 7:
                        {
                            set_tmp[3] = 10;
                            LcdSetPos (10, 0);
                            break;
                        }
                    // Y
                    case 10:
                        {
                            set_tmp[3] = 13;
                            LcdSetPos (13, 0);
                            break;
                        }
                    // N
                    case 13:
                        {
                            set_tmp[3] = 1;
                            LcdSetPos (1, 0);
                            break;
                        }
                    // others
                    default:
                        {
                            set_tmp[3] = 1;
                            LcdSetPos (1, 0);
                            break;
                        }
                }
            }
            //*************************************************************







            //*************************************************************
            // LEFT Response
            //*************************************************************
            if (KEY_LEFT_up == 1)
            {
                // left process
                switch (set_tmp[3])
                {
                    // hour
                    case 1:
                        {
                            set_tmp[3] = 13;
                            LcdSetPos (13, 0);
                            break;
                        }
                    // min
                    case 4:
                        {
                            set_tmp[3] = 1;
                            LcdSetPos (1, 0);
                            break;
                        }
                    // sec
                    case 7:
                        {
                            set_tmp[3] = 4;
                            LcdSetPos (4, 0);
                            break;
                        }
                    // Y
                    case 10:
                        {
                            set_tmp[3] = 7;
                            LcdSetPos (7, 0);
                            break;
                        }
                    // N
                    case 13:
                        {
                            set_tmp[3] = 10;
                            LcdSetPos (10, 0);
                            break;
                        }
                    // others
                    default:
                        {
                            set_tmp[3] = 1;
                            LcdSetPos (1, 0);
                            break;
                        }
                }
            }
            //*************************************************************









            //*************************************************************
            // ENTER Response
            //*************************************************************
            if (KEY_ENTER_up == 1)
            {
                // left process
                switch (set_tmp[3])
                {
                    // hour
                    case 1:
                        {
                            set_tmp[3] = 4;
                            LcdSetPos (4, 0);
                            break;
                        }
                    // min
                    case 4:
                        {
                            set_tmp[3] = 7;
                            LcdSetPos (7, 0);
                            break;
                        }
                    // sec
                    case 7:
                        {
                            set_tmp[3] = 10;
                            LcdSetPos (10, 0);
                            break;
                        }
                    // N
                    case 10:
                        {
                            set_tmp[5] = 3;
                            break;
                        }
                    // Y
                    case 13:
                        {
                            set_tmp[5] = 2;
                            break;
                        }
                    // others
                    default:
                        {
                            break;
                        }
                }
            }
            //*************************************************************
        }




        // quit judge
        if (set_tmp[5] != 0)
        {
            // Set Mode: close cursor, close splash
            LcdWriteCmd (LCD1602_CMD_DM_0C);

            if (set_tmp[5] == 1)
            {
                break;
            }
            else if (set_tmp[5] == 2)   // setup time
            {
                // SET
                RtcWrite (RTC_ADDR_B, 0x80);
                // set up time
                RtcWrite (RTC_ADDR_HOUR,    set_tmp[0]);    // hour
                RtcWrite (RTC_ADDR_MIN,     set_tmp[1]);    // min
                RtcWrite (RTC_ADDR_SEC,     set_tmp[2]);    // sec 
                // NO SET
                //RtcWrite (RTC_ADDR_B, (RtcRead(RTC_ADDR_B)&0x7F));
                RtcWrite (RTC_ADDR_B, 0x16);
                // direct return to FigureAAA
                sleep_time = 0xFFFF;
                break;
            }
            else if (set_tmp[5] == 3)
            {
                sleep_time = 0xFFFF;
                break;
            }
        }
    }
}















void MenuSetDate (void)
{
    // clear all
    LcdClearScreen ();

    // load time
    //set_tmp[0]      = (((pRTC->hour)&0xF0)*10) + ((pRTC->hour)&0x0F);
    //set_tmp[1]      = (((pRTC->min)&0xF0)*10) + ((pRTC->min)&0x0F);
    set_tmp[0]      = pRTC->cent;
    set_tmp[1]      = pRTC->year;
    set_tmp[2]      = pRTC->mon;
    set_tmp[3]      = pRTC->day;
    set_tmp[4]      = 1;    // position: 1: century; 3: year; 6: mon; 9: day; 13: N; 16: Y;
    set_tmp[5]      = 0;    // key hold time
    set_tmp[6]      = 0;    // break flag
    sleep_time      = 0;    // keep in menu time


    // figrue redraw
    // Set Mode: open cursor, close splash
    LcdWriteCmd (LCD1602_CMD_DM_0E);
    // Draw Figure   xx:xx:xx   Y   N
    LcdDispInt (SET_DATE_BASE, SET_DATE_Y, set_tmp[0], 0x10);       // cent
    LcdDispInt (SET_DATE_BASE+2, SET_DATE_Y, set_tmp[1], 0x00);     // year
    LcdDispChar (SET_DATE_BASE+4, SET_DATE_Y, CHAR_CGRAM_NIAN);     // NIAN
    LcdDispInt (SET_DATE_BASE+5, SET_DATE_Y, set_tmp[2], 0x10);     // mon
    LcdDispChar (SET_DATE_BASE+7, SET_DATE_Y, CHAR_CGRAM_YUE);      // YUE
    LcdDispInt (SET_DATE_BASE+8, SET_DATE_Y, set_tmp[3], 0x10);     // day
    LcdDispChar (SET_DATE_BASE+10, SET_DATE_Y, CHAR_CGRAM_RI);      // RI
    LcdDispChar (SET_DATE_BASE+13, SET_DATE_Y, 'N');                // N
    LcdDispChar (SET_DATE_BASE+16, SET_DATE_Y, 'Y');                // Y
    // set cursor
    LcdSetPos (1, 0);



    // key process
    while (1)
    {
        // tick check
        TickChk ();
        if (tick_inc)
        {
            // sleep time
            sleep_time = sleep_time + tick_inc*SYSTEM_TICK;
            if (sleep_time > sleep_end)
            {
                // Set Mode: close cursor, close splash
                LcdWriteCmd (LCD1602_CMD_DM_0C);
                set_tmp[6] = 1;    // time out break
                break;
            }


            // key scan
            KeyScan ();



            //*************************************************************
            // Up Response
            //*************************************************************
            if (KEY_UP_ok == 1)
            {
                if ((KEY_UP_down == 1) || (set_tmp[5] > KEY_MIN_GAP))
                {
                    if (set_tmp[5] > KEY_MIN_GAP)
                        set_tmp[5] = 0;

                    // up process
                    switch (set_tmp[4])
                    {
                        // cent
                        case 1:
                            {
                                if (set_tmp[0] > 99)
                                    set_tmp[0] = 1;
                                else
                                    set_tmp[0] = set_tmp[0] + 1;
                                LcdDispInt (SET_DATE_BASE+0, SET_DATE_Y, set_tmp[0], 0x10);
                                LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                                break;
                            }
                        // year
                        case 3:
                            {
                                if (set_tmp[1] > 99)
                                    set_tmp[1] = 0;
                                else
                                    set_tmp[1] = set_tmp[1] + 1;
                                LcdDispInt (SET_DATE_BASE+2, SET_DATE_Y, set_tmp[1], 0x00);
                                LcdSetPos (SET_DATE_BASE+3, SET_DATE_Y);
                                break;
                            }
                        // mon
                        case 6:
                            {
                                if (set_tmp[2] > 11)
                                    set_tmp[2] = 1;
                                else
                                    set_tmp[2] = set_tmp[2] + 1;
                                LcdDispInt (SET_DATE_BASE+5, SET_DATE_Y, set_tmp[2], 0x10);
                                LcdSetPos (SET_DATE_BASE+6, SET_DATE_Y);
                                break;
                            }
                        // day
                        case 9:
                            {
                                if (set_tmp[3] > 30)
                                    set_tmp[3] = 1;
                                else
                                    set_tmp[3] = set_tmp[3] + 1;
                                LcdDispInt (SET_DATE_BASE+8, SET_DATE_Y, set_tmp[3], 0x10);
                                LcdSetPos (SET_DATE_BASE+9, SET_DATE_Y);
                                break;
                            }
                        // others
                        default:
                            {
                                set_tmp[4] = 1;
                                LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                                break;
                            }
                    }
                }
            }
            // key press timer
            if ((KEY_UP_down == 1) || (KEY_UP_up == 1))
            {
                set_tmp[5] = 0;
            }
            else if (KEY_UP_ok == 1)
            {
                set_tmp[5] = set_tmp[5] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************






            //*************************************************************
            // DOWN Response
            //*************************************************************
            if (KEY_DOWN_ok == 1)
            {
                if ((KEY_DOWN_down == 1) || (set_tmp[5] > KEY_MIN_GAP))
                {
                    if (set_tmp[5] > KEY_MIN_GAP)
                        set_tmp[5] = 0;

                    // up process
                    switch (set_tmp[4])
                    {
                        // cent
                        case 1:
                            {
                                if (set_tmp[0] < 2)
                                    set_tmp[0] = 99;
                                else
                                    set_tmp[0] = set_tmp[0] - 1;
                                LcdDispInt (SET_DATE_BASE+0, SET_DATE_Y, set_tmp[0], 0x10);
                                LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                                break;
                            }
                        // year
                        case 3:
                            {
                                if (set_tmp[1] < 1)
                                    set_tmp[1] = 99;
                                else
                                    set_tmp[1] = set_tmp[1] - 1;
                                LcdDispInt (SET_DATE_BASE+2, SET_DATE_Y, set_tmp[1], 0x00);
                                LcdSetPos (SET_DATE_BASE+3, SET_DATE_Y);
                                break;
                            }
                        // mon
                        case 6:
                            {
                                if (set_tmp[2] < 2)
                                    set_tmp[2] = 12;
                                else
                                    set_tmp[2] = set_tmp[2] - 1;
                                LcdDispInt (SET_DATE_BASE+5, SET_DATE_Y, set_tmp[2], 0x10);
                                LcdSetPos (SET_DATE_BASE+6, SET_DATE_Y);
                                break;
                            }
                        // day
                        case 9:
                            {
                                if (set_tmp[3] < 2)
                                    set_tmp[3] = 31;
                                else
                                    set_tmp[3] = set_tmp[3] - 1;
                                LcdDispInt (SET_DATE_BASE+8, SET_DATE_Y, set_tmp[3], 0x10);
                                LcdSetPos (SET_DATE_BASE+9, SET_DATE_Y);
                                break;
                            }
                        // others
                        default:
                            {
                                set_tmp[4] = 1;
                                LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                                break;
                            }
                    }
                }
            }
            // key press timer
            if ((KEY_DOWN_down == 1) || (KEY_DOWN_up == 1))
            {
                set_tmp[5] = 0;
            }
            else if (KEY_DOWN_ok == 1)
            {
                set_tmp[5] = set_tmp[5] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************








            //*************************************************************
            // RIGHT Response
            //*************************************************************
            if (KEY_RIGHT_up == 1)
            {
                // right process
                switch (set_tmp[4])
                {
                    // cent
                    case 1:
                        {
                            set_tmp[4] = 3;
                            LcdSetPos (SET_DATE_BASE+3, SET_DATE_Y);
                            break;
                        }
                    // year
                    case 3:
                        {
                            set_tmp[4] = 6;
                            LcdSetPos (SET_DATE_BASE+6, SET_DATE_Y);
                            break;
                        }
                    // mon
                    case 6:
                        {
                            set_tmp[4] = 9;
                            LcdSetPos (SET_DATE_BASE+9, SET_DATE_Y);
                            break;
                        }
                    // day
                    case 9:
                        {
                            set_tmp[4] = 13;
                            LcdSetPos (SET_DATE_BASE+13, SET_DATE_Y);
                            break;
                        }
                    // N
                    case 13:
                        {
                            set_tmp[4] = 16;
                            LcdSetPos (SET_DATE_BASE+16, SET_DATE_Y);
                            break;
                        }
                    // N
                    case 16:
                        {
                            set_tmp[4] = 1;
                            LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                            break;
                        }
                    // others
                    default:
                        {
                            set_tmp[4] = 1;
                            LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                            break;
                        }
                }
            }
            //*************************************************************







            //*************************************************************
            // LEFT Response
            //*************************************************************
            if (KEY_LEFT_up == 1)
            {
                // left process
                switch (set_tmp[4])
                {
                    // cent
                    case 1:
                        {
                            set_tmp[4] = 16;
                            LcdSetPos (SET_DATE_BASE+16, SET_DATE_Y);
                            break;
                        }
                    // year
                    case 3:
                        {
                            set_tmp[4] = 1;
                            LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                            break;
                        }
                    // mon
                    case 6:
                        {
                            set_tmp[4] = 3;
                            LcdSetPos (SET_DATE_BASE+3, SET_DATE_Y);
                            break;
                        }
                    // day
                    case 9:
                        {
                            set_tmp[4] = 6;
                            LcdSetPos (SET_DATE_BASE+6, SET_DATE_Y);
                            break;
                        }
                    // N
                    case 13:
                        {
                            set_tmp[4] = 9;
                            LcdSetPos (SET_DATE_BASE+9, SET_DATE_Y);
                            break;
                        }
                    // N
                    case 16:
                        {
                            set_tmp[4] = 13;
                            LcdSetPos (SET_DATE_BASE+13, SET_DATE_Y);
                            break;
                        }
                    // others
                    default:
                        {
                            set_tmp[4] = 1;
                            LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                            break;
                        }
                }
            }
            //*************************************************************









            //*************************************************************
            // ENTER Response
            //*************************************************************
            if (KEY_ENTER_up == 1)
            {
                // enter process
                switch (set_tmp[4])
                {
                    // cent
                    case 1:
                        {
                            set_tmp[4] = 3;
                            LcdSetPos (SET_DATE_BASE+3, SET_DATE_Y);
                            break;
                        }
                    // year
                    case 3:
                        {
                            set_tmp[4] = 6;
                            LcdSetPos (SET_DATE_BASE+6, SET_DATE_Y);
                            break;
                        }
                    // mon
                    case 6:
                        {
                            set_tmp[4] = 9;
                            LcdSetPos (SET_DATE_BASE+9, SET_DATE_Y);
                            break;
                        }
                    // day
                    case 9:
                        {
                            set_tmp[4] = 13;
                            LcdSetPos (SET_DATE_BASE+13, SET_DATE_Y);
                            break;
                        }
                    // N
                    case 13:
                        {
                            set_tmp[6] = 3;
                            break;
                        }
                    // Y
                    case 16:
                        {
                            set_tmp[6] = 2;
                            break;
                        }
                    // others
                    default:
                        {
                            set_tmp[4] = 1;
                            LcdSetPos (SET_DATE_BASE+1, SET_DATE_Y);
                            break;
                        }
                }
            }
            //*************************************************************
        }




        // quit judge
        if (set_tmp[6] != 0)
        {
            // Set Mode: close cursor, close splash
            LcdWriteCmd (LCD1602_CMD_DM_0C);

            if (set_tmp[6] == 1)
            {
                set_tmp[6] = 0;
                break;
            }
            else if (set_tmp[6] == 2)   // setup time
            {
                set_tmp[6] = 0;
                // SET
                RtcWrite (RTC_ADDR_B, 0x80);
                // set up time
                RtcWrite (RTC_ADDR_CENT,    set_tmp[0]);    // cent
                RtcWrite (RTC_ADDR_YEAR,    set_tmp[1]);    // year
                RtcWrite (RTC_ADDR_MON,     set_tmp[2]);    // mon
                RtcWrite (RTC_ADDR_DAY,     set_tmp[3]);    // day 
                // NO SET
                //RtcWrite (RTC_ADDR_B, (RtcRead(RTC_ADDR_B)&0x7F));
                RtcWrite (RTC_ADDR_B, 0x16);
                // direct return to FigureAAA
                sleep_time = 0xFFFF;
                break;
            }
            else if (set_tmp[6] == 3)
            {
                set_tmp[6] = 0;
                sleep_time = 0xFFFF;
                break;
            }
        }
    }
}








//*****************************************************************
// About Function
//*****************************************************************
void About (void)
{
    // clear all
    LcdClearScreen ();

    // display
    LcdDispString (0, 0, const_about[0]);
    LcdDispString (0, 1, const_about[1]);

    // Init
    set_tmp[0] = 0;     // display start
    set_tmp[1] = 0;     // time out flag
    sleep_time = 0;

    // key process
    while (1)
    {
        // tick check
        TickChk ();
        if (tick_inc)
        {
            // sleep time
            sleep_time = sleep_time + tick_inc*SYSTEM_TICK;
            if (sleep_time > sleep_end)
            {
                set_tmp[1] = 1;    // time out break
                break;
            }


            // key scan
            KeyScan ();



            //*************************************************************
            // Up Response
            //*************************************************************
            if (KEY_UP_up == 1)
            {
                if (set_tmp[0] > 0)
                {
                    set_tmp[0] = set_tmp[0] - 1;
                    LcdClearScreen ();
                    LcdDispString (0, 0, const_about[set_tmp[0]]);
                    LcdDispString (0, 1, const_about[(set_tmp[0] + 1)]);
                }
            }
            //*************************************************************




            //*************************************************************
            // DOWN Response
            //*************************************************************
            if (KEY_DOWN_up == 1)
            {
                if (set_tmp[0] < (ABOUT_LINES - 2))
                {
                    set_tmp[0] = set_tmp[0] + 1;
                    LcdClearScreen ();
                    LcdDispString (0, 0, const_about[set_tmp[0]]);
                    LcdDispString (0, 1, const_about[(set_tmp[0] + 1)]);
                }
            }
            //*************************************************************








            //*************************************************************
            // RIGHT Response
            //*************************************************************
            if (KEY_RIGHT_up == 1)
            {
                KEY_RIGHT_up = 0;
                set_tmp[1] = 3;    // return to main
            }
            //*************************************************************







            //*************************************************************
            // LEFT Response
            //*************************************************************
            if (KEY_LEFT_up == 1)
            {
                KEY_LEFT_up = 0;
                set_tmp[1] = 2;    // genral break
            }
            //*************************************************************









            //*************************************************************
            // ENTER Response
            //*************************************************************
            if (KEY_ENTER_up == 1)
            {
                if (set_tmp[0] < (ABOUT_LINES - 2))
                {
                    set_tmp[0] = set_tmp[0] + 1;
                    LcdClearScreen ();
                    LcdDispString (0, 0, const_about[set_tmp[0]]);
                    LcdDispString (0, 1, const_about[(set_tmp[0] + 1)]);
                }
            }
            //*************************************************************
        }




        // over?
        if (set_tmp[1] != 0)
        {
            if (set_tmp[1] == 1)    // time out
            {
                set_tmp[1] = 0;
                break;
            }
            else if (set_tmp[1] == 2) // return 
            {
                set_tmp[1] = 0;
                break;
            }
            else if (set_tmp[1] == 3) // exit
            {
                set_tmp[1] = 0;
                sleep_time = 0xFFFF;
                break;
            }
        }
    }
}
//*****************************************************************








//*****************************************************************
// Set Timeout Function
//*****************************************************************
void SetTimeout (void)
{
    // clear all
    LcdClearScreen ();


    // load time
    set_tmp[0]      = RtcRead (CFG_RTC_ADDR_TMOUT);
    set_tmp[1]      = 0;    // quit flag
    set_tmp[2]      = 0;
    set_tmp[3]      = 0;
    set_tmp[5]      = 0;    // key stay timer
    sleep_time      = 0;    // keep in menu time


    // figrue redraw
    // Set Mode: open cursor, close splash
    LcdWriteCmd (LCD1602_CMD_DM_0E);
    // Draw Figure   xx:xx:xx   Y   N
    LcdDispChar (0, 0, 'T');
    LcdDispChar (1, 0, 'i');
    LcdDispChar (2, 0, 'm');
    LcdDispChar (3, 0, 'e');
    LcdDispChar (4, 0, 'o');
    LcdDispChar (5, 0, 'u');
    LcdDispChar (6, 0, 't');
    LcdDispChar (7, 0, ':');
    LcdDispChar (8, 0, ' ');
    LcdDispChar (12, 0, 's');
    set_tmp[2] = set_tmp[0]/100;
    set_tmp[3] = set_tmp[0] - set_tmp[2]*100;
    LcdDispInt (8, 0, set_tmp[2], 0x11);
    if (set_tmp[0] > 99)
        LcdDispInt (10, 0, set_tmp[3], 0x00);
    else
        LcdDispInt (10, 0, set_tmp[3], 0x10);
    // set cursor
    LcdSetPos (11, 0);



    // key process
    while (1)
    {
        // tick check
        TickChk ();
        if (tick_inc)
        {
            // sleep time
            sleep_time = sleep_time + tick_inc*SYSTEM_TICK;
            if (sleep_time > sleep_end)
            {
                // Set Mode: close cursor, close splash
                LcdWriteCmd (LCD1602_CMD_DM_0C);
                set_tmp[1] = 1;    // time out break
                break;
            }


            // key scan
            KeyScan ();



            //*************************************************************
            // Up Response
            //*************************************************************
            if (KEY_UP_ok == 1)
            {
                if ((KEY_UP_down == 1) || (set_tmp[5] > KEY_MIN_GAP))
                {
                    if (set_tmp[5] > KEY_MIN_GAP)
                        set_tmp[5] = 0;
                    // value change
                    if (set_tmp[0] > 254)
                        set_tmp[0] = 10;
                    else
                        set_tmp[0] = set_tmp[0] + 1;
                    // display
                    set_tmp[2] = set_tmp[0]/100;
                    set_tmp[3] = set_tmp[0] - set_tmp[2]*100;
                    LcdDispInt (8, 0, set_tmp[2], 0x11);
                    if (set_tmp[0] > 99)
                        LcdDispInt (10, 0, set_tmp[3], 0x00);
                    else
                        LcdDispInt (10, 0, set_tmp[3], 0x10);
                    // set cursor
                    LcdSetPos (11, 0);
                }
            }
            // key press timer
            if ((KEY_UP_down == 1) || (KEY_UP_up == 1))
            {
                set_tmp[5] = 0;
            }
            else if (KEY_UP_ok == 1)
            {
                set_tmp[5] = set_tmp[5] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************







            //*************************************************************
            // Down Response
            //*************************************************************
            if (KEY_DOWN_ok == 1)
            {
                if ((KEY_DOWN_down == 1) || (set_tmp[5] > KEY_MIN_GAP))
                {
                    if (set_tmp[5] > KEY_MIN_GAP)
                        set_tmp[5] = 0;
                    // value change
                    if (set_tmp[0] < 11)
                        set_tmp[0] = 255;
                    else
                        set_tmp[0] = set_tmp[0] - 1;
                    // display
                    set_tmp[2] = set_tmp[0]/100;
                    set_tmp[3] = set_tmp[0] - set_tmp[2]*100;
                    LcdDispInt (8, 0, set_tmp[2], 0x11);
                    if (set_tmp[0] > 99)
                        LcdDispInt (10, 0, set_tmp[3], 0x00);
                    else
                        LcdDispInt (10, 0, set_tmp[3], 0x10);
                    // set cursor
                    LcdSetPos (11, 0);
                }
            }
            // key press timer
            if ((KEY_DOWN_down == 1) || (KEY_DOWN_up == 1))
            {
                set_tmp[5] = 0;
            }
            else if (KEY_DOWN_ok == 1)
            {
                set_tmp[5] = set_tmp[5] + tick_inc*SYSTEM_TICK;
            }
            //*************************************************************










            //*************************************************************
            // RIGHT Response
            //*************************************************************
            if (KEY_RIGHT_up == 1)
            {
                KEY_RIGHT_up = 0;
                set_tmp[1] = 2;    // return to main
            }
            //*************************************************************







            //*************************************************************
            // LEFT Response
            //*************************************************************
            if (KEY_LEFT_up == 1)
            {
                KEY_LEFT_up = 0;
                set_tmp[1] = 3;    // genral break
            }
            //*************************************************************









            //*************************************************************
            // ENTER Response
            //*************************************************************
            if (KEY_ENTER_up == 1)
            {
                // write value
                RtcWrite (CFG_RTC_ADDR_TMOUT, set_tmp[0]);
                // clear
                LcdClearScreen ();
                // Set Mode: close cursor, close splash
                LcdWriteCmd (LCD1602_CMD_DM_0C);
                // display
                LcdDispString (0, 1, "Timeout      s    ok!");

                set_tmp[2] = set_tmp[0]/100;
                set_tmp[3] = set_tmp[0] - set_tmp[2]*100;
                LcdDispInt (9, 1, set_tmp[2], 0x11);
                if (set_tmp[0] > 99)
                    LcdDispInt (11, 1, set_tmp[3], 0x00);
                else
                    LcdDispInt (11, 1, set_tmp[3], 0x10);
                DelayMs (2200);
                set_tmp[1] = 2;    // genral break
            }
            //*************************************************************
        }




        // over?
        if (set_tmp[1] != 0)
        {
            // Set Mode: close cursor, close splash
            LcdWriteCmd (LCD1602_CMD_DM_0C);

            if (set_tmp[1] == 1)    // time out
            {
                set_tmp[1] = 0;
                break;
            }
            else if (set_tmp[1] == 2) // exit
            {
                set_tmp[1] = 0;
                sleep_time = 0xFFFF;
                break;
            }
            else if (set_tmp[1] == 3) // return
            {
                set_tmp[1] = 0;
                break;
            }
        }
    }
}
//*****************************************************************



//*****************************************************************
// Null Function
//*****************************************************************
void NullSubs (void)
{
}
//*****************************************************************
