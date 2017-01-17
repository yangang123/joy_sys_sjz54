
#ifndef	__JOY_SYS_H__
#define	__JOY_SYS_H__


#include "ds12c887.h"
#include "init.h"








//**************************************************************//
//**************************************************************//
//**************************************************************//
//******************** Constant Definitions ********************//
//**************************************************************//
//**************************************************************//
//**************************************************************//
// system 
#define TM_SEN_LEN          1500        // ms
//#define TM_MOV_LEN          50          // ms
#define SYSTEM_TICK         2           // ms
#define SYSTEM_CLK          6           // MHz
//#define TICK_TMR_LOW        ((65535 - (SYSTEM_TICK*1000)/(12/SYSTEM_CLK)) & 0xFF)
//#define TICK_TMR_HIGH       ((((unsigned int)65535 - (SYSTEM_TICK*1000)/(12/SYSTEM_CLK)) >> 16) & 0xFF)
#define TICK_TMR_LOW        0x17
#define TICK_TMR_HIGH       0xFC
#define MEA_TEMP            0x00
#define MEA_HUMI            0x01

// LCD CGRAM
#define LCGR_DAI            0x00        // 待机
#define LCGR_LING           0x01        // 闹钟
#define LCGR_HUO            0x02        // 火
#define LCGR_SHUI           0x03        // 水
#define LCGR_ZHI            0x04        //  >
#define LCGR_RI             0x05        // 日
#define LCGR_YUE            0x06        // 月
#define LCGR_NIAN           0x07        // 年
// LCD CGRAM
#define CHAR_CGRAM_DAI      0x00        // 待机
#define CHAR_CGRAM_LING     0x01        // 闹钟
#define CHAR_CGRAM_HUO      0x02        // 火
#define CHAR_CGRAM_SHUI     0x03        // 水
#define CHAR_CGRAM_ZHI      0x04        //  >
#define CHAR_CGRAM_RI       0x05        // 日
#define CHAR_CGRAM_YUE      0x06        // 月
#define CHAR_CGRAM_NIAN     0x07        // 年
//**************************************************************//
// Time Position
#define POS_X_CENT          0
#define POS_X_YEAR          2
#define POS_X_MON           5
#define POS_X_DAY           8
#define POS_X_HOU           2
#define POS_X_MIN           5
#define POS_X_SEC           8
#define POS_Y_CENT          0
#define POS_Y_YEAR          0
#define POS_Y_MON           0
#define POS_Y_DAY           0
#define POS_Y_HOU           1
#define POS_Y_MIN           1
#define POS_Y_SEC           1
#define POS_X_HAN_NIAN      (POS_X_YEAR + 2)
#define POS_Y_HAN_NIAN      (POS_Y_YEAR + 0)
#define POS_X_HAN_YUE       (POS_X_MON + 2)
#define POS_Y_HAN_YUE       (POS_Y_MON + 0)
#define POS_X_HAN_RI        (POS_X_DAY + 2)
#define POS_Y_HAN_RI        (POS_Y_DAY + 0)
#define POS_X_COLON_1       (POS_X_HOU + 2)
#define POS_Y_COLON_1       (POS_Y_HOU + 0)
#define POS_X_COLON_2       (POS_X_MIN + 2)
#define POS_Y_COLON_2       (POS_Y_MIN + 0)
// temp and humi
#define POS_X_TEMP_1        16
#define POS_Y_TEMP_1        0
#define POS_X_HUMI_1        16
#define POS_Y_HUMI_1        1
#define POS_X_TEMP_2        (POS_X_TEMP_1 + 3)
#define POS_Y_TEMP_2        (POS_Y_TEMP_1 + 0)
#define POS_X_HUMI_2        (POS_X_HUMI_1 + 3)
#define POS_Y_HUMI_2        (POS_Y_HUMI_1 + 0)
#define POS_X_DIAN_1        (POS_X_TEMP_1 + 2)
#define POS_Y_DIAN_1        (POS_Y_TEMP_1 + 0)
#define POS_X_DIAN_2        (POS_X_HUMI_1 + 2)
#define POS_Y_DIAN_2        (POS_Y_HUMI_1 + 0)
#define POS_X_HUO           (POS_X_TEMP_1 + 5)
#define POS_Y_HUO           (POS_Y_TEMP_1 + 0)
#define POS_X_SHUI          (POS_X_HUMI_1 + 5)
#define POS_Y_SHUI          (POS_Y_HUMI_1 + 0)
//**************************************************************//
// state machine
#define STATE_MEASURE_TEMP  0
#define STATE_CHECK_TEMP    1
#define STATE_MEASURE_HUMI  2
#define STATE_CHECK_HUMI    3
#define STATE_ERROR         4
#define STATE_DISPLAY       5
//**************************************************************//
#define KEY_ENTER_down      k1_down_flag
#define KEY_ENTER_up        k1_up_flag
#define KEY_ENTER_ok        k1_ok_flag
#define KEY_UP_down         k2_down_flag
#define KEY_UP_up           k2_up_flag
#define KEY_UP_ok           k2_flag
#define KEY_DOWN_down       k3_down_flag
#define KEY_DOWN_up         k3_up_flag
#define KEY_DOWN_ok         k3_flag
#define KEY_LEFT_down       k4_down_flag
#define KEY_LEFT_up         k4_up_flag
#define KEY_LEFT_ok         k4_flag
#define KEY_RIGHT_down      k5_down_flag
#define KEY_RIGHT_up        k5_up_flag
#define KEY_RIGHT_ok        k5_flag
#define KEY_ESC_down        k4_flag
#define KEY_ESC_up          k4_flag
#define KEY_ESC_ok          k4_flag
#define KEY_BACK_down       k5_flag
#define KEY_BACK_up         k5_flag
#define KEY_BACK_ok         k5_flag
//**************************************************************//

















//****************************************************************
// External Variable Declearations
//****************************************************************








//**************************************************************//
//********************** BIT SECTION ***************************//
//**************************************************************//
extern volatile bit data rtc_ud_flag;
extern volatile bit data rtc_alarm_flag;

extern volatile bit data k1_flag;
extern volatile bit data k2_flag;
extern volatile bit data k3_flag;
extern volatile bit data k4_flag;
extern volatile bit data k5_flag;
extern volatile bit data k1_down_flag;
extern volatile bit data k2_down_flag;
extern volatile bit data k3_down_flag;
extern volatile bit data k4_down_flag;
extern volatile bit data k5_down_flag;
extern volatile bit data k1_up_flag;
extern volatile bit data k2_up_flag;
extern volatile bit data k3_up_flag;
extern volatile bit data k4_up_flag;
extern volatile bit data k5_up_flag;
extern volatile bit data lcd_bkl_time_flag;
extern volatile bit data lcd_bkl_time_flag_bak;
//**************************************************************//






//**************************************************************//
//********************* DATA SECTION ***************************//
//**************************************************************//
//system tick timer
extern data volatile unsigned char tick;

//**************************************************************//









//**************************************************************//
//******************** IDATA SECTION ***************************//
//**************************************************************//
extern idata unsigned char tick_inc;
extern idata unsigned char tick_bak1;
extern idata unsigned char tick_bak2;


//**************************************************************//









//**************************************************************//
//******************** XDATA SECTION ***************************//
//**************************************************************//
extern TIME_STRUCT xdata real_time;
extern TIME_STRUCT xdata *pRTC;
extern SEN_STRUCT xdata sen;

extern xdata unsigned char chk_read;
extern xdata unsigned char sensor_state;
extern xdata unsigned char sensor_error;
extern xdata unsigned char sensor_rong;

extern xdata unsigned int sensor_time;
extern xdata unsigned int sleep_time;
extern xdata unsigned int sleep_end;
extern xdata unsigned int bkl_time;
extern xdata unsigned char set_tmp[8];
//**************************************************************//




//**************************************************************//
//********************* CODE SECTION ***************************//
//**************************************************************//
extern code const char CONST_CGCODE[];
extern code const char *CONST_CGCODE_STANDBY;
extern code const char *CONST_CGCODE_ALARM;
extern code const char *CONST_CGCODE_FIRE;
extern code const char *CONST_CGCODE_WATER;
extern code const char *CONST_CGCODE_INDICTOR;
extern code const char *CONST_CGCODE_DAY;
extern code const char *CONST_CGCODE_MONTH;
extern code const char *CONST_CGCODE_YEAR;
//**************************************************************//

















//**************************************************************//
//******************** Function Declearations ******************//
//**************************************************************//
void SystemInit(void);
void SystemStart (void);
void TickChk (void);
void LcdDrawTime (void);
void LcdDrawTempHumi (void);
void FigureAaaInit (void);
void FigureBbbInit (void);
void SensorRefresh (void);
void Welcome (void);
void KeyScan (void);

//**************************************************************//



#endif
