//*********************************************************
//  File Name   : joy_sys.c
//  Created On  : 201501192039
//  Author      : Ming
//  Description : System related sidnfadfahs
//*********************************************************

#include	"joy_sys.h"






//****************************************************************
// External Variable Definitions
//****************************************************************








//**************************************************************//
//********************** BIT SECTION ***************************//
//**************************************************************//
volatile bit data rtc_ud_flag;
volatile bit data rtc_alarm_flag;

volatile bit data k1_val;
volatile bit data k1_bak;
volatile bit data k2_val;
volatile bit data k2_bak;
volatile bit data k3_val;
volatile bit data k3_bak;
volatile bit data k4_val;
volatile bit data k4_bak;
volatile bit data k5_val;
volatile bit data k5_bak;
volatile bit data k1_flag;
volatile bit data k2_flag;
volatile bit data k3_flag;
volatile bit data k4_flag;
volatile bit data k5_flag;
volatile bit data k1_down_flag;
volatile bit data k2_down_flag;
volatile bit data k3_down_flag;
volatile bit data k4_down_flag;
volatile bit data k5_down_flag;
volatile bit data k1_up_flag;
volatile bit data k2_up_flag;
volatile bit data k3_up_flag;
volatile bit data k4_up_flag;
volatile bit data k5_up_flag;
volatile bit data lcd_bkl_time_flag;
volatile bit data lcd_bkl_time_flag_bak;
//**************************************************************//






//**************************************************************//
//********************* DATA SECTION ***************************//
//**************************************************************//
//system tick timer
data volatile unsigned char tick;
// pointers
TIME_STRUCT xdata *pRTC;
//**************************************************************//









//**************************************************************//
//******************** IDATA SECTION ***************************//
//**************************************************************//
idata unsigned char tick_inc; 
idata unsigned char tick_bak1;
idata unsigned char tick_bak2;


//**************************************************************//









//**************************************************************//
//******************** XDATA SECTION ***************************//
//**************************************************************//
// struct
xdata SEN_STRUCT sen;
xdata TIME_STRUCT real_time;

xdata unsigned char chk_read;
xdata unsigned char sensor_state;
xdata unsigned char sensor_error;
xdata unsigned char sensor_rong;


xdata unsigned int sensor_time;
xdata unsigned int sleep_time;
xdata unsigned int sleep_end;
xdata unsigned int bkl_time;
xdata unsigned char set_tmp[8];
//**************************************************************//




//**************************************************************//
//********************* CODE SECTION ***************************//
//**************************************************************//
code const char CONST_CGCODE[]          = {
         0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F, 0x00,    // 日
         0x0F, 0x09, 0x0F, 0x09, 0x0F, 0x09, 0x09, 0x13,    // 月
         //0x02, 0x04, 0x0F, 0x12, 0x0F, 0x0A, 0x1F, 0x02,    // 年
         0x04, 0x0F, 0x12, 0x0F, 0x0A, 0x1F, 0x02, 0x02,    // 年
         0x00, 0x10, 0x1C, 0x1F, 0x1F, 0x1C, 0x10, 0x00,    // STANDBY
         0x00, 0x10, 0x1C, 0x1F, 0x1F, 0x1C, 0x10, 0x00,    // ALARM
         //0x08, 0x1E, 0x00, 0x1C, 0x00, 0x1C, 0x05, 0x07,    // FIRE 
	 0x10, 0x06, 0x09, 0x08, 0x08, 0x09, 0x06, 0x00,    // FIRE 
         //0x04, 0x04, 0x1F, 0x0E, 0x15, 0x04, 0x0C, 0x00,    // WATER 1
         //0x00, 0x08, 0x11, 0x0A, 0x11, 0x0A, 0x01, 0x00,    // WATER 2
         //0x00, 0x00, 0x09, 0x12, 0x09, 0x12, 0x09, 0x00,    // WATER 3
         //0x00, 0x00, 0x09, 0x12, 0x09, 0x12, 0x00, 0x00,    // WATER 4
         0x00, 0x09, 0x09, 0x12, 0x09, 0x12, 0x12, 0x00,    // WATER 5
         0x00, 0x10, 0x1C, 0x1F, 0x1F, 0x1C, 0x10, 0x00,    // INDICTOR
         0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,    //
         0x00, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00, 0x00,    // 二
         0x00, 0x1F, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00,    // 三
         0x00, 0x00, 0x00, 0x0A, 0x15, 0x0A, 0x04, 0x00,    // 心
         0x00, 0x04, 0x15, 0x0E, 0x1F, 0x0E, 0x11, 0x00};   // 坦克


code const char *CONST_CGCODE_DAY       = CONST_CGCODE + 0*8;
code const char *CONST_CGCODE_MONTH     = CONST_CGCODE + 1*8;
code const char *CONST_CGCODE_YEAR      = CONST_CGCODE + 2*8;
code const char *CONST_CGCODE_STANDBY   = CONST_CGCODE + 3*8;
code const char *CONST_CGCODE_ALARM     = CONST_CGCODE + 4*8;
code const char *CONST_CGCODE_FIRE      = CONST_CGCODE + 5*8;
code const char *CONST_CGCODE_WATER     = CONST_CGCODE + 6*8;
code const char *CONST_CGCODE_INDICTOR  = CONST_CGCODE + 7*8;
code const char *CONST_WELCOME          = "Joy System!";
//**************************************************************//

































//**************************************************************//
//******************** Function Definitions ********************//
//**************************************************************//

// system initilizition
void SystemInit (void)
{
    // Device Init
    DeviceInit ();

    // rtc 
    pRTC            = &real_time;

    // LCD CGRAM INIT
    LcdWriteOneCGRAM (LCGR_DAI, CONST_CGCODE_STANDBY);
    LcdWriteOneCGRAM (LCGR_LING, CONST_CGCODE_ALARM);
    LcdWriteOneCGRAM (LCGR_HUO, CONST_CGCODE_FIRE);
    LcdWriteOneCGRAM (LCGR_SHUI, CONST_CGCODE_WATER);
    LcdWriteOneCGRAM (LCGR_ZHI, CONST_CGCODE_INDICTOR);
    LcdWriteOneCGRAM (LCGR_RI, CONST_CGCODE_DAY);
    LcdWriteOneCGRAM (LCGR_YUE, CONST_CGCODE_MONTH);
    LcdWriteOneCGRAM (LCGR_NIAN, CONST_CGCODE_YEAR);

    // Key Init
    k1_val          = 1;
    k2_val          = 1;
    k3_val          = 1;
    k4_val          = 1;
    k5_val          = 1;
    k1_bak          = 1;
    k2_bak          = 1;
    k3_bak          = 1;
    k4_bak          = 1;
    k5_bak          = 1;
    k5_flag         = 0;
    k1_flag         = 0;
    k2_flag         = 0;
    k3_flag         = 0;
    k4_flag         = 0;
    k5_flag         = 0;
    k1_down_flag    = 0;
    k2_down_flag    = 0;
    k3_down_flag    = 0;
    k4_down_flag    = 0;
    k5_down_flag    = 0;
    k1_up_flag      = 0;
    k2_up_flag      = 0;
    k3_up_flag      = 0;
    k4_up_flag      = 0;
    k5_up_flag      = 0;
    bkl_time        = 0;
    lcd_bkl_time_flag = 0;
    lcd_bkl_time_flag_bak = 0;
    
}




// start system
void SystemStart (void)
{
    TR0 = 1;
}





void LcdDrawTime (void)
{
    LcdDispInt (POS_X_CENT, POS_Y_CENT, pRTC->cent, 0x00);
    LcdDispInt (POS_X_YEAR, POS_Y_YEAR, pRTC->year, 0x00);
    LcdDispInt (POS_X_MON, POS_Y_MON, pRTC->mon, 0x10);
    LcdDispInt (POS_X_DAY, POS_Y_DAY, pRTC->day, 0x10);

    LcdDispInt (POS_X_HOU, POS_Y_HOU, pRTC->hour, 0x10);
    LcdDispInt (POS_X_MIN, POS_Y_MIN, pRTC->min, 0x00);
    LcdDispInt (POS_X_SEC, POS_Y_SEC, pRTC->sec, 0x00);
}



void LcdDrawTempHumi (void)
{
    sen.temp_fra = (sen.temp_fra/10)*10;
    sen.humi_fra = (sen.humi_fra/10)*10;
    LcdDispInt (POS_X_TEMP_1, POS_Y_TEMP_1, sen.temp_int, 0x10);
    LcdDispInt (POS_X_TEMP_2, POS_Y_TEMP_2, sen.temp_fra, 0x01);
    LcdDispInt (POS_X_HUMI_1, POS_Y_HUMI_1, sen.humi_int, 0x10);
    LcdDispInt (POS_X_HUMI_2, POS_Y_HUMI_2, sen.humi_fra, 0x01);
	  LcdDispChar (POS_X_HUO, POS_Y_HUO, CHAR_CGRAM_HUO);
    LcdDispChar (POS_X_SHUI, POS_Y_SHUI, '%');
}


// check tick time
void TickChk (void)
{
    if (tick_bak1 != tick)
    {
        tick_bak1 = tick;
        if (tick_bak1 > tick_bak2)
            tick_inc = tick_bak1 - tick_bak2;
        else if (tick_bak1 < tick_bak2)     // yichu
            tick_inc = 255 - tick_bak2 + tick_bak1 + 1;
        else
            tick_inc = 0;
        tick_bak2 = tick_bak1;
    }
    else
    {
        tick_inc = 0;
    }
}











void FigureAaaInit (void)
{
    //************************************************************
    // clear screen
    //************************************************************
    LcdClearScreen ();
    RtcLoadTime (pRTC); // read time first
    DelayMs (1);
    //************************************************************




    //************************************************************
    // Redraw Figure
    //************************************************************
    // draw figure: misc
    LcdDispChar (POS_X_HAN_RI, POS_Y_HAN_RI, CHAR_CGRAM_RI);
    LcdDispChar (POS_X_HAN_YUE, POS_Y_HAN_YUE, CHAR_CGRAM_YUE);
    LcdDispChar (POS_X_HAN_NIAN, POS_Y_HAN_NIAN, CHAR_CGRAM_NIAN);
    LcdDispChar (POS_X_HUO, POS_Y_HUO, CHAR_CGRAM_HUO);
    LcdDispChar (POS_X_SHUI, POS_Y_SHUI, '%');
    LcdDispChar (POS_X_COLON_1, POS_Y_COLON_1, ':');
    LcdDispChar (POS_X_COLON_2, POS_Y_COLON_2, ':');
    LcdDispChar (POS_X_DIAN_1, POS_Y_DIAN_1, '.');
    LcdDispChar (POS_X_DIAN_2, POS_Y_DIAN_2, '.');
    // draw figure: time
    LcdDrawTime ();
    // draw figure: temp & humi
    //LcdDrawTempHumi ();
    //************************************************************



    //************************************************************
    // System Init
    //************************************************************
    ShtSoftReset();
    // tick init
    tick            = 0;
    tick_bak1       = 0;
    tick_bak2       = 0;
    tick_inc        = 0;
    // sensor init
    sensor_time     = 0;
    sensor_state    = 0;
    sensor_rong     = 0;
    sensor_error    = 0;
    rtc_ud_flag     = 0;
    //************************************************************
    // clear RTC flag
    RtcRead (RTC_ADDR_C);
    //************************************************************
}




void FigureBbbInit (void)
{
    //************************************************************
    // clear screen
    //************************************************************
    LcdClearScreen ();
    //************************************************************




    //************************************************************
    // Redraw Figure
    //************************************************************
    // draw figure: misc
    //************************************************************



    //************************************************************
    // System Init
    //************************************************************
    // tick init
    tick            = 0;
    tick_bak1       = 0;
    tick_bak2       = 0;
    tick_inc        = 0;
    //************************************************************
}






void SensorRefresh (void)
{

    //*******************************************************//
    //******** Sensor Measurment and Display Process ********//
    //*******************************************************//
    sensor_time = sensor_time + tick_inc*SYSTEM_TICK;
    if (sensor_time > TM_SEN_LEN)
        sensor_time = sensor_time - TM_SEN_LEN;
    //*******************************************************//








    //*******************************************************//
    //******** State Machine Process ************************//
    //*******************************************************//
    switch (sensor_state)
    {
        // wait start to read temp
        case (STATE_MEASURE_TEMP): 
        {
            if (sensor_time < 100)
            {
                if (ShtMeasSet (MEA_TEMP))
                {
                    ShtConnectReset ();
                    ShtSoftReset ();
                    sensor_error ++;
                    if (sensor_error > 10)
                    {
                        sensor_rong = 1;
                        sensor_error  = 0;
                        sensor_state = STATE_ERROR;
                    }
                }
                else
                {
                    sensor_rong = 0;
                    sensor_error = 0;
                    sensor_state = STATE_CHECK_TEMP;
                }
            }

            break;
        }
        // wait measurement
        case (STATE_CHECK_TEMP):
        {
            if (ShtMeasChk ())
            {
                ShtMeasRead ((unsigned char *)(&(sen.temp_read)), &chk_read);
                sensor_rong = 0;
                sensor_error = 0;
                sensor_state = STATE_MEASURE_HUMI;
            }
            else
            {
                sensor_error ++;
                if (sensor_error > 500)
                {
                    sensor_rong = 2;
                    sensor_error  = 0;
                    sensor_state = STATE_ERROR;
                }
            }

            break;
        }
        // measure humi
        case (STATE_MEASURE_HUMI): 
        {
            if (ShtMeasSet (MEA_HUMI))
            {
                ShtConnectReset ();
                ShtSoftReset ();
                sensor_error ++;
                if (sensor_error > 10)
                {
                    sensor_rong = 3;
                    sensor_error  = 0;
                    sensor_state = STATE_ERROR;
                }
            }
            else
            {
                sensor_rong = 0;
                sensor_error = 0;
                sensor_state = STATE_CHECK_HUMI;
            }

            break;
        }   
        // wait measurement
        case (STATE_CHECK_HUMI): 
        {
            if (ShtMeasChk ())
            {
                ShtMeasRead ((unsigned char *)(&(sen.humi_read)), &chk_read);
                sensor_rong = 0;
                sensor_error = 0;
                sensor_state = STATE_DISPLAY;
            }
            else
            {
                sensor_error ++;
                if (sensor_error > 500)
                {
                    sensor_rong = 4;
                    sensor_error = 0;
                    sensor_state = STATE_ERROR;
                }
            }

            break;
        }
        // error process
        case (STATE_ERROR): 
        {
            sensor_state = STATE_DISPLAY;

            break;
        }
        // cal and display
        case (STATE_DISPLAY):    
        {
            // error display
            if (sensor_rong)
            {
                LcdDispChar (POS_X_TEMP_1, POS_Y_TEMP_1, 'E');
                LcdDispChar ((POS_X_TEMP_1 + 1), POS_Y_TEMP_1, (sensor_rong + '0'));
                sensor_rong = 0;
            }
            // normal display
            else
            {
                ShtCalHumiTemp2 ((SEN_STRUCT *)(&sen));
                LcdDrawTempHumi ();
            }
            sensor_state = STATE_MEASURE_TEMP;

            break;
        }
    }
}



void Welcome (void)
{
    unsigned char i;



    for (i = 0; i < 12 + 4; i++)
    {
        LcdClearScreen ();
        LcdDispString ((23 - i), 0, CONST_WELCOME);
        DelayMs (300);
    }
    DelayMs (1000);
}



void KeyScan (void)
{
    // k1
    sbit_pin_k1 = 1;
    DelayUs (10);
    k1_val = sbit_pin_k1;
    if ((k1_val == 0) && (k1_bak == 1))     // press down
    {
        k1_flag = 1;
        k1_down_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k1_down_flag = 0;
    }
    if ((k1_val == 1) && (k1_bak == 0))     // press release
    {
        k1_flag = 0;
        k1_up_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k1_up_flag = 0;
    }
    k1_bak = k1_val;

    // k2
    sbit_pin_k2 = 1;
    DelayUs (10);
    k2_val = sbit_pin_k2;
    if ((k2_val == 0) && (k2_bak == 1))     // press down
    {
        k2_flag = 1;
        k2_down_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k2_down_flag = 0;
    }
    if ((k2_val == 1) && (k2_bak == 0))     // press release
    {
        k2_flag = 0;
        k2_up_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k2_up_flag = 0;
    }
    k2_bak = k2_val;

    // k3
    sbit_pin_k3 = 1;
    DelayUs (10);
    k3_val = sbit_pin_k3;
    if ((k3_val == 0) && (k3_bak == 1))     // press down
    {
        k3_flag = 1;
        k3_down_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k3_down_flag = 0;
    }
    if ((k3_val == 1) && (k3_bak == 0))     // press release
    {
        k3_flag = 0;
        k3_up_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k3_up_flag = 0;
    }
    k3_bak = k3_val;

    // k4
    sbit_pin_k4 = 1;
    DelayUs (10);
    k4_val = sbit_pin_k4;
    if ((k4_val == 0) && (k4_bak == 1))     // press down
    {
        k4_flag = 1;
        k4_down_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k4_down_flag = 0;
    }
    if ((k4_val == 1) && (k4_bak == 0))     // press release
    {
        k4_flag = 0;
        k4_up_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k4_up_flag = 0;
    }
    k4_bak = k4_val;

    // k5
    sbit_pin_k5 = 1;
    DelayUs (10);
    k5_val = sbit_pin_k5;
    if ((k5_val == 0) && (k5_bak == 1))     // press down
    {
        k5_flag = 1;
        k5_down_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k5_down_flag = 0;
    }
    if ((k5_val == 1) && (k5_bak == 0))     // press release
    {
        k5_flag = 0;
        k5_up_flag = 1;
        sleep_time = 0;
    }
    else
    {
        k5_up_flag = 0;
    }
    k5_bak = k5_val;
}
