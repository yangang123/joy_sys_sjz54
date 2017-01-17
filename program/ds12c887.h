

#ifndef __DS12C887_H__
#define __DS12C887_H__


//******************************************************
//* headers
//******************************************************
#include "pin_conf.h"
#include "delay.h"
//******************************************************








//******************************************************
//* pin definitions
//******************************************************
#define PIN_RTC_AS                      sbit_pin_rtc_as
#define PIN_RTC_DS                      sbit_pin_rtc_ds
#define PIN_RTC_RW                      sbit_pin_rtc_rw
#define PIN_RTC_DATA                    def_pin_rtc_data
//******************************************************



//******************************************************
//* DS12C887 Command Definitions
//******************************************************
#define RTC_ADDR_SEC                    0x00
#define RTC_ADDR_MIN                    0x02
#define RTC_ADDR_HOUR                   0x04
#define RTC_ADDR_WEEK                   0x06
#define RTC_ADDR_DAY                    0x07
#define RTC_ADDR_MON                    0x08
#define RTC_ADDR_YEAR                   0x09
#define RTC_ADDR_CENT                   0x32
//******************************************************
#define RTC_ALAM_SEC                    0x01
#define RTC_ALAM_MIN                    0x03
#define RTC_ALAM_HOUR                   0x05
//******************************************************
// bit[7]   : UIP, Updata-In-Progress
// bit[:4]  : DV2/1/0, "010" Run normally, 11x, no update
// bit[:0]  : RS3/2/1/0, Rate Selector
#define RTC_ADDR_A                      0x0A


// bit[7]   : SET, 0: normal; 1: update is inhibited
// bit[6]   : PIE, Periodic Interrupt Enable
// bit[5]   : AIE, Alarm Interrupt Enable
// bit[4]   : UIE, Updata-Ended Interrupt Enable
// bit[3]   : SQWE, Square-Wave Enable
// bit[2]   : DM, Data Mode, 0: BCD; 1: binary
// bit[1]   : 24/12, 0: 12-hour; 1: 24-hour
// bit[0]   : DSE, Daylight Saving Enable ??
#define RTC_ADDR_B                      0x0B


// bit[7]   : IRQF, Interrupt Request Flag
// bit[6]   : PF, Periodic Interrupt Flag
// bit[5]   : AF, Alarm Interrupt Flag
// bit[4]   : UF, Updata-Ended Interrupt Flag
#define RTC_ADDR_C                      0x0C



// bit[7]   : VRT, Valid RAM and Time, readonly
#define RTC_ADDR_D                      0x0D
//******************************************************
#define RTC_INT_PF                      0xC0
#define RTC_INT_AF                      0xA0
#define RTC_INT_UF                      0x90
//******************************************************













//******************************************************
//* Time Store Struct
//******************************************************
typedef struct {
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char week;
    unsigned char mon;
    unsigned char year;
    unsigned char cent;
} TIME_STRUCT;
//******************************************************











//***************************************************************
//* func declearations
//***************************************************************
void RtcWrite (unsigned char addr, unsigned char dat);
unsigned char RtcRead (unsigned char addr);
unsigned char RtcChkVRT (void);
void RtcInit (void);

void RtcLoadTime (TIME_STRUCT *p);
//void RtcUpdateTime (TIME_STRUCT *p);
//***************************************************************









#endif
