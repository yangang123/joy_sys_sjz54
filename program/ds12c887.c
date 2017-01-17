


#include "ds12c887.h"

// Intel Interface Mode




// write data to rtc
void RtcWrite (unsigned char addr, unsigned char dat)
{
    bit ebk;
    ebk = EA;
    EA = 0;
    PIN_RTC_AS      = 1;
    PIN_RTC_DATA    = addr;
    DelayUs (0);
    PIN_RTC_AS      = 0;
    DelayUs (0);
    PIN_RTC_RW      = 0;
    PIN_RTC_DATA    = dat;
    DelayUs (1);
    PIN_RTC_RW      = 1;
    EA = ebk;
}



// read data from rtc
unsigned char RtcRead (unsigned char addr)
{
    unsigned char ret;

    bit ebk;
    ebk = EA;
    EA = 0;

    PIN_RTC_AS      = 1;
    PIN_RTC_DATA    = addr;
    DelayUs (0);
    PIN_RTC_AS      = 0;
    DelayUs (0);
    PIN_RTC_DS      = 0;
    DelayUs (1);
    PIN_RTC_DATA    = 0xFF;
    DelayUs (0);
    ret             = PIN_RTC_DATA;
    PIN_RTC_DS      = 1;

    EA = ebk;
    return ret;
}



// check state
unsigned char RtcChkVRT (void)
{
    unsigned char ret;

    ret = RtcRead (RTC_ADDR_D);
    ret = (ret & 0x80);

    return ret;
}


// read all time to struct
void RtcLoadTime (TIME_STRUCT *p)
{
    p->sec      = RtcRead (RTC_ADDR_SEC);
    p->min      = RtcRead (RTC_ADDR_MIN);
    p->hour     = RtcRead (RTC_ADDR_HOUR);
    p->week     = RtcRead (RTC_ADDR_WEEK);
    p->day      = RtcRead (RTC_ADDR_DAY);
    p->mon      = RtcRead (RTC_ADDR_MON);
    p->year     = RtcRead (RTC_ADDR_YEAR);
    p->cent     = RtcRead (RTC_ADDR_CENT);
}



// refrush changed time in struct
/*void RtcUpdateTime (TIME_STRUCT *p)
{
    unsigned char val;

    // sec
    val = RtcRead (RTC_ADDR_SEC);
    if ((p->sec) != val)
    {
        p->sec = val;
        // min
        val = RtcRead (RTC_ADDR_MIN);
        if ((p->min) != val)
        {
            p->min = val;

            // hour
            val = RtcRead (RTC_ADDR_HOUR);
            if ((p->hour) != val)
            {
                p->hour = val;

                // day
                val = RtcRead (RTC_ADDR_DAY);
                if ((p->day) != val)
                {
                    p->day = val;
                    p->week = RtcRead (RTC_ADDR_WEEK);

                    // month
                    val = RtcRead (RTC_ADDR_MON);
                    if ((p->mon) != val)
                    {
                        p->mon = val;

                        // year
                        val = RtcRead (RTC_ADDR_YEAR);
                        if ((p->year) != val)
                        {
                            p->year = val;

                            // century
                            val = RtcRead (RTC_ADDR_CENT);
                            p->cent = val;
                        }
                    }
                }
            }
        }
    }
}*/




void RtcInit (void)
{
    unsigned char val;

    // switch judge
    val = RtcRead (0x0A);
    if ((val & 0x70) != 0x20)
    {
        //RtcWrite (0x0A, 0x20);

        //RtcWrite (0x00, 0x00);      // sec 
        //RtcWrite (0x02, 0x05);      // min
        //RtcWrite (0x04, 0x22);      // hour
        //RtcWrite (0x06, 0x01);      // week
        //RtcWrite (0x07, 0x05);      // day
        //RtcWrite (0x08, 0x01);      // mon
        //RtcWrite (0x09, 0x15);
    }


//    // SET, Binray, 24 mode
//    RtcWrite (RTC_ADDR_B,       0x86);
//    // set up time
//    RtcWrite (RTC_ADDR_SEC,     0);         // sec 
//    RtcWrite (RTC_ADDR_MIN,     11);        // min
//    RtcWrite (RTC_ADDR_HOUR,    17);        // hour
//    RtcWrite (RTC_ADDR_WEEK,    6);         // week
//    RtcWrite (RTC_ADDR_DAY,     4);         // day
//    RtcWrite (RTC_ADDR_MON,     4);         // mon
//    RtcWrite (RTC_ADDR_YEAR,    15);        // year
//    RtcWrite (RTC_ADDR_CENT,    20);        // century
//    // NO SET, Binray, 24 mode
//    RtcWrite (RTC_ADDR_B,       0x06);


    // Enable Updata Interrupt
    // Binary Data
    // 24 hour mode
    RtcWrite (RTC_ADDR_B,       0x16);



    // clear interrupt flags
    // This is a must when using interrupt!!!
    RtcRead (RTC_ADDR_C);

    DelayMs (10);


    /*
	RtcWrite (0x00, 0x20);      // sec 
    RtcWrite (0x02, 0x51);      // min
    RtcWrite (0x04, 0x18);      // hour
    RtcWrite (0x06, 0x04);      // week
    RtcWrite (0x07, 0x05);      // day
    RtcWrite (0x08, 0x02);      // mon
    RtcWrite (0x09, 0x15);
    RtcWrite (RTC_ADDR_CENT, 0x20); // century
	*/


}





//**************************************************

