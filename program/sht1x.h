

#ifndef __SHT1X_H__
#define __SHT1X_H__


//******************************************************
//* headers
//******************************************************
#include <intrins.h>
#include <stdio.h>
#include <math.h>
#include <delay.h>
#include "sht1x.h"
#include "pin_conf.h"
//******************************************************








//******************************************************
//* pin definitions
//******************************************************
#define PIN_SHT_DATA                sbit_pin_sht1x_data
#define PIN_SHT_CLK                 sbit_pin_sht1x_clk
//******************************************************
#define SHT_NO_ACK                          0
#define SHT_ACK                             1
//******************************************************
//* command definitions
//******************************************************
#define SHT_CMD_MEAS_TEMP              0x03     // 00011
#define SHT_CMD_MEAS_HUMI              0x05     // 00101
#define SHT_CMD_STATUS_WR              0x06     // 00110
#define SHT_CMD_STATUS_RD              0x07     // 00111
#define SHT_CMD_INTF_RST               0x1E     // 11110
//******************************************************
typedef struct {
    unsigned int temp_read;
    unsigned int humi_read;
    unsigned char temp_int;
    unsigned char temp_fra;
    unsigned char humi_int;
    unsigned char humi_fra;
} SEN_STRUCT;
//******************************************************











//******************************************************
//* func definitions
//******************************************************
char ShtWriteByte (unsigned char val);
char ShtReadByte (unsigned char ack);
void ShtTranStart (void);
void ShtConnectReset (void);
char ShtSoftReset (void);
char ShtReadStatusReg (unsigned char *p_val, unsigned char *p_chk);
char ShtWriteStatusReg (unsigned char *p_val);
char ShtMeasSet (unsigned char mode);
char ShtMeasChk (void);
void ShtMeasRead (unsigned char *p_val, unsigned char *p_chk);
void ShtCalHumiTemp (float *p_humi, float *p_temp);
float ShtCalDewPoint (float h, float t);
void ShtInit (void);
void ShtCalHumiTemp2 (SEN_STRUCT *ps);

//******************************************************




#endif
