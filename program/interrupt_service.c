//*********************************************************
//  File Name   : interrupt.c
//  Created On  : 201501161834
//  Author      : Ming
//  Description : here are interrupt service routines
//*********************************************************


#include	"interrupt_service.h"


// Timer0 Interrupt
void t0_interrupt_service (void) interrupt 1 using 1
{
    TL0     = TICK_TMR_LOW;
    TH0     = TICK_TMR_HIGH;
    tick ++;
}





//// External Interrupt 0
//void ExtInt0_servece (void) interrupt 0 using 2
//{
//    unsigned char val;
//
//    // read ds12c887 interrupt flag
//    val = RtcRead (RTC_ADDR_C);
//
//    // interrupt alarm check
//    if (val & RTC_INT_AF)
//    {
//        rtc_alarm_flag = 1;
//    }
//
//    // interrupt update check
//    if (val & RTC_INT_UF)
//    {
//        rtc_ud_flag = 1;
//    }
//}



// External Interrupt 4
void ExtInt2_servece (void) interrupt 10 using 2
{
    unsigned char val;

    // read ds12c887 interrupt flag
    val = RtcRead (RTC_ADDR_C);

    // interrupt alarm check
    if (val & RTC_INT_AF)
    {
        rtc_alarm_flag = 1;
    }

    // interrupt update check
    if (val & RTC_INT_UF)
    {
        rtc_ud_flag = 1;
    }
}












