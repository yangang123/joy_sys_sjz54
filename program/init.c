//*********************************************************
//  File Name   : init.c
//  Created On  : 201501161906
//  Author      : Ming
//  Description : device initiation routines
//*********************************************************


#include	"init.h"









void CpuInit (void)
{
    // STC15W401AS Configure
    //************************************
    //* T0x12, T1x12, UART_M0x6
    //* T2R, T2_C/T, T2x12, EXRAM, S1ST2
    //*     EXRAM: enable
    //*     S1ST2: T2 for bandrate gen
    //************************************
    AUXR        = 0x01;
    //************************************
    //* PIN
    //*     UART([7:6]) : P3.0, P3.1
    //*     CCP([5:4])  : P3.5, P3.6, P3.7
    //************************************
    AUXR1       = 0x10;
    //************************************
    //* EX4, EX3, EX2
    //* T2CLKO, T1CLKO, T0CLKO
    //*     EXTINT: INT2, 3, 4 disable
    //*     CLKO: T0, T1, T2 output disable
    //************************************
    AUXR2       = 0x00;
    //************************************
    //* MCLKO_S1, MCLKO_S0, ADRJ, Tx_Rx, MCLKO_2
    //* CLK_S2, CLK_S1, CLK_S0
    //*     CLK do not output;
    //*     Uart work mode: normal
    //*     Main_CLK: div1
    //************************************
    CLK_DIV     = 0x00;
    //************************************
    //* IAP_EN, SWBS, SWRST, CMD_FAIL
    //* WT2, WT1, WT0
    //*     IAP: disable
    //*     SWRST: clear
    //************************************
    IAP_CONTR   = 0x00;
    //************************************
    //* WDT_FLAG, EN_WDT, CLR_WDT, IDLE_WDT
    //* PS2, PS1, PS0
    //*     WDT: disable
    //************************************
    WDT_CONTR   = 0x00;
    //************************************
    //* SMOD, SMOD0, LVDF, POF, GF1, GF0
    //* PD, DIL
    //************************************
    PCON        = 0x00;
    //************************************
    //* WKTCL: timer_L
    //* WKTCH: timer_H, enable
    //************************************
    WKTCL       = 0xFF;
    WKTCH       = 0xEF;
    //************************************
    //* P1, P2, P3, I/O mode
    //*     dual-dir
    //************************************
    P1M1        = 0x00;
    P1M0        = 0x00;
    P2M1        = 0x00;
    P2M0        = 0x00;
    P3M1        = 0x00;
    P3M0        = 0x00;
    //************************************


    // interrupt
    IE = 0;

    // T0
    ET0 = 1;

//    // INT0
//    IT0 = 1;    // INT0_trig    : falling_edge
//    PX0 = 0;    // INT0 prio    : 0
//    EX0 = 1;    // INT0         : enable

    // INT2
    // Enable EX2
    AUXR2       = 0x10;


    EA = 1;

    // timer 0: timer, mode 1
    TMOD = 0x01;
    TH0 = TICK_TMR_HIGH;
    TL0 = TICK_TMR_LOW;
    TF0 = 0;
    TR0 = 0;
}





void DeviceInit (void)
{
    CpuInit ();
    LcdInit ();
    ShtInit ();
    RtcInit ();
}

