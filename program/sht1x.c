


#include "sht1x.h"





//******************************************************
//* func definitions
//******************************************************
char ShtWriteByte (unsigned char val)
{
    unsigned char i, error;
    error = 0;

    // write byte
    for (i = 0x80; i > 0; i/=2)
    {
        if (i & val)
            PIN_SHT_DATA = 1;
        else
            PIN_SHT_DATA = 0;
        _nop_();
        PIN_SHT_CLK = 1;
        _nop_();
        PIN_SHT_CLK = 0;
        _nop_();
    }

    // ack
    PIN_SHT_DATA = 1;
    _nop_();
    PIN_SHT_CLK = 1;
    error = PIN_SHT_DATA;
    PIN_SHT_CLK = 0;

    return error;
}





// when ack = 1, send ack
char ShtReadByte (unsigned char ack)
{
    unsigned char i, val;
    val = 0;

    PIN_SHT_DATA = 1;


    // write byte
    for (i = 0x80; i > 0; i/=2)
    {
        PIN_SHT_CLK = 1;
        if (PIN_SHT_DATA) val = (val | i);
        PIN_SHT_CLK = 0;
    }

    PIN_SHT_DATA = !ack;
    _nop_();
    PIN_SHT_CLK = 1;
    _nop_();
    _nop_();
    _nop_();
    PIN_SHT_CLK = 0;
    _nop_();
    PIN_SHT_DATA = 1;


    return val;
}











void ShtTranStart (void)
{
    // init
    PIN_SHT_DATA = 1;
    PIN_SHT_CLK = 0;
    _nop_();

    // first change
    PIN_SHT_CLK = 1;
    _nop_();
    PIN_SHT_DATA = 0;
    _nop_();
    PIN_SHT_CLK = 0;
    _nop_();
    _nop_();
    _nop_();

    // second change
    PIN_SHT_CLK = 1;
    _nop_();
    PIN_SHT_DATA = 1;
    _nop_();
    PIN_SHT_CLK = 0;
}





void ShtConnectReset (void)
{
    unsigned char i;


    PIN_SHT_DATA = 1;
    PIN_SHT_CLK = 0;

    // wait at least 9 clks
    for (i = 0; i < 9; i++)
    {
        PIN_SHT_CLK = 1;
        PIN_SHT_CLK = 0;
    }

    // start
    ShtTranStart();
}



char ShtSoftReset (void)
{
    unsigned char error = 0;

    ShtConnectReset ();
    error += ShtWriteByte (SHT_CMD_INTF_RST);

    DelayMs(20);

    return error;
}




char ShtReadStatusReg (unsigned char *p_val, unsigned char *p_chk)
{
    unsigned char error = 0;

    ShtTranStart ();
    error = ShtWriteByte (SHT_CMD_STATUS_RD);
    *p_val = ShtReadByte (SHT_ACK);
    *p_chk = ShtReadByte (SHT_NO_ACK);

    return error;
}





char ShtWriteStatusReg (unsigned char *p_val)
{
    unsigned char error = 0;

    ShtTranStart ();
    error += ShtWriteByte (SHT_CMD_STATUS_WR);
    error += ShtWriteByte (*p_val);

    return error;
}





char ShtMeasSet (unsigned char mode)
{
    unsigned char error = 0;

    ShtTranStart ();

    switch (mode)
    {
        case 0x00: 
            error += ShtWriteByte (SHT_CMD_MEAS_TEMP);
            break;
        case 0x01:
            error += ShtWriteByte (SHT_CMD_MEAS_HUMI);
            break;
    }

    return error;
}






char ShtMeasChk (void)
{
    if (PIN_SHT_DATA == 0)  // finish
        return 1;
    else
        return 0;
}





void ShtMeasRead (unsigned char *p_val, unsigned char *p_chk)
{
    *(p_val) = ShtReadByte (SHT_ACK);
    *(p_val + 1) = ShtReadByte (SHT_ACK);
    *(p_chk) = ShtReadByte (SHT_NO_ACK);
}






/*
void ShtCalHumiTemp (float *p_humi, float *p_temp)
{
    const float c1 = -2.0468;
    const float c2 = +0.0367;
    const float c3 = -0.0000015955;
    const float T1 = +0.01;
    const float T2 = +0.00008;


    float rh = *p_humi;
    float t = *p_temp;

    float rh_line;
    float rh_true;
    float t_C;

    t_C = t*0.01 - 40.1;
    rh_line = c3*rh*rh + c2*rh + c1;
    rh_true = (t_C - 25)*(T1 + T2*rh) + rh_line;

    if (rh_true > 100)
        rh_true = 100;
    if (rh_true < 0.1)
        rh_true = 0.1;

    *p_temp = t_C;
    *p_humi = rh_true;
}


            
float ShtCalDewPoint (float h, float t)
{
    float k, dew_point;

    k = (log10(h) - 2)/0.4343 + (17.62*t)/(243.12 + t);
    dew_point = 243.12*k/(17.62 - k);

    return dew_point;
}
*/






void ShtInit (void)
{
    unsigned char val = 0;

    ShtSoftReset ();

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    ShtWriteStatusReg (&val);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}






void ShtCalHumiTemp2 (SEN_STRUCT * ps)
{
    const float c1 = -2.0468;
    const float c2 = +0.0367;
    const float c3 = -0.0000015955;
    const float T1 = +0.01;
    const float T2 = +0.00008;


    float rh = (float)(ps->humi_read);
    float t = (float)(ps->temp_read);

    float rh_line;
    float rh_true;
    float t_C;

    t_C = t*0.01 - 40.1;
    rh_line = c3*rh*rh + c2*rh + c1;
    rh_true = (t_C - 25)*(T1 + T2*rh) + rh_line;

    if (rh_true > 100)
        rh_true = 99.9;
    if (rh_true < 0.1)
        rh_true = 0.1;

    ps->temp_int = (unsigned char )(t_C);
    ps->temp_fra = (unsigned char )((t_C - (ps->temp_int)) * 100);
    ps->humi_int = (unsigned char )(rh_true);
    ps->humi_fra = (unsigned char )((rh_true - (ps->humi_int)) * 100);
}
