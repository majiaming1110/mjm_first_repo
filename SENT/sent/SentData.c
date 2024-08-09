#include "SentData.h"

/******************************************************************************
*                       Definition
******************************************************************************/
//short 1 nibble
float32 SentStaticData_0x01[160] = {0};
//short 2 nibble
float32 SentStaticData_0x02[192] = {0};
//short 3 nibble
float32 SentStaticData_0x03[224] = {0};
//short 4 nibble
float32 SentStaticData_0x04[256] = {0};
//short 5 nibble
float32 SentStaticData_0x05[288] = {0};
//short 6 nibble
float32 SentStaticData_0x06[319] = {0};
//short 6 nibble normal crc
float32 SentStaticData_0x2c[319] = {0};
//short 7 nibble
float32 SentStaticData_0x07[352] = {0};
//short 8 nibble
float32 SentStaticData_0x08[384] = {0};
//short 4 nibble normal crc
float32 SentStaticData_0x09[255] = {0};
//enhance cfg0_1
float32 SentStaticData_0x0a[180] = {0};
//enhance cfg0_2
float32 SentStaticData_0x0b[216] = {0};
//enhance cfg0_3 normal crc
float32 SentStaticData_0x0c[252] = {0};
//enhance cfg0_4
float32 SentStaticData_0x0d[288] = {0};
//enhance cfg0_5 normal crc
float32 SentStaticData_0x0e[324] = {0};
//enhance cfg0_6 normal crc
float32 SentStaticData_0x0f[360] = {0};
//enhance cfg0_7 normal crc
float32 SentStaticData_0x10[396] = {0};
//enhance cfg0_8
float32 SentStaticData_0x11[432] = {0};
//enhance cfg0_4 normal crc
float32 SentStaticData_0x12[288] = {0};
//enhance cfg1_1
float32 SentStaticData_0x13[180] = {0};
//enhance cfg1_2 normal crc
float32 SentStaticData_0x14[216] = {0};
//enhance cfg1_3 normal crc
float32 SentStaticData_0x15[252] = {0};
//enhance cfg1_4
float32 SentStaticData_0x16[288] = {0};
//enhance cfg1_5 normal crc
float32 SentStaticData_0x17[324] = {0};
//enhance cfg1_6 normal crc
float32 SentStaticData_0x18[360] = {0};
//enhance cfg1_7 normal crc
float32 SentStaticData_0x19[396] = {0};
//enhance cfg1_8
float32 SentStaticData_0x1a[432] = {0};
//enhance cfg1_4 normal crc
float32 SentStaticData_0x1b[288] = {0};
//Short serial Bit3 error
float32 SentStaticData_0x1c[160] = {0};
//Enhance serial Bit3 error
float32 SentStaticData_0x1d[180] = {0};
//Enhance serial Bit3 error
float32 SentStaticData_0x1e[180] = {0};
//Pause Pulse error 11
float32 SentStaticData_0x1f[24] = {0};
//Pause Pulse error 770
float32 SentStaticData_0x20[24] = {0};
//Calibrate Pulse error 70
float32 SentStaticData_0x21[10] = {0};
//Calibrate Pulse error 84
float32 SentStaticData_0x22[10] = {0};
//Calibrate Pulse error 41
float32 SentStaticData_0x23[160] = {0};
// Data Tick error
float32 SentStaticData_0x24[160] = {0};
// Data Tick error
float32 SentStaticData_0x25[160] = {0};
//Burr waveform 25us
float32 SentStaticData_0x26[170] = {0};
//Burr waveform 10us
float32 SentStaticData_0x27[32] = {0};
//reverse short 1 nibble
float32 SentStaticData_0x28[160] = {0};
//reverse short 1 nibble
float32 SentStaticData_0x29[320] = {0};
//reverse short 1 nibble
float32 SentStaticData_0x2a[320] = {0};
//short 1 nibble glitch
float32 SentStaticData_0x2b[192] = {0};

//short 3 nibble + alter crc + no PausePulse
float32 SentStaticData_0x2d[191] = {0};
//short 3 nibble + alter crc
float32 SentStaticData_0x2e[223] = {0};


TT_RetType sent_config(const uint32 ticks, uint32 message_type)
{
    uint32 i;
    switch(message_type)
    {
        case 0x01:	//short 1   /*MJM: short_1有16个SENT帧，每帧数据段为1个Nibble*/
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x01[i] = short_1[i] * ticks;
            }
            break;
        case 0x02:	//short 2   /*MJM: short_2有16个SENT帧，每帧数据段为2个Nibble*/
            for(i = 0; i < 192; i++)
            {
                 SentStaticData_0x02[i] = short_2[i] * ticks;
            }
            break;
        case 0x03:	//short 3   /*MJM: short_3有16个SENT帧，每帧数据段为3个Nibble*/
            for(i = 0; i < 224; i++)
            {
                 SentStaticData_0x03[i] = short_3[i] * ticks;
            }
            break;
        case 0x04:	//short 4
            for(i = 0; i < 256; i++)
            {
                 SentStaticData_0x04[i] = short_4[i] * ticks;
            }
            break;
        case 0x05:	//short 5
            for(i = 0; i < 288; i++)
            {
                 SentStaticData_0x05[i] = short_5[i] * ticks;
            }
            break;
        case 0x06:	//short 6
            for(i = 0; i < 319; i++)
            {
                 SentStaticData_0x06[i] = short_6[i] * ticks;
            }
            break;
        case 0x07:	//short 7
            for(i = 0; i < 352; i++)
            {
                 SentStaticData_0x07[i] = short_7[i] * ticks;
            }
            break;
        case 0x08:	//short 8
            for(i = 0; i < 384; i++)
            {
                 SentStaticData_0x08[i] = short_8[i] * ticks;
            }
            break;
        case 0x09:	//short 4 normal crc   /*MJM: short 4 normal crc有16个SENT帧，每帧数据段为4个Nibble，且使用传统CRC*/
            for(i = 0; i < 255; i++)
            {
                 SentStaticData_0x09[i] = short_4_crc[i] * ticks;
            }
            break;
        case 0x0a:	//enhance cfg0_1    /*MJM: enhance cfg0_1为增强串行消息，有18个SENT帧，每帧数据段为1个Nibble*/
            for(i = 0; i < 180; i++)
            {
                 SentStaticData_0x0a[i] = cfg0_1[i] * ticks;
            }
            break;
        case 0x0b:	//enhance cfg0_2    /*MJM: enhance cfg0_2为增强串行消息，有18个SENT帧，每帧数据段为2个Nibble*/
            for(i = 0; i < 216; i++)
            {
                 SentStaticData_0x0b[i] = cfg0_2[i] * ticks;
            }
            break;
        case 0x0c:	//enhance cfg0_3 normal crc  /*MJM: enhance cfg0_3为增强串行消息，有18个SENT帧，每帧数据段为3个Nibble，且使用传统CRC*/
            for(i = 0; i < 252; i++)
            {
                 SentStaticData_0x0c[i] = cfg0_3[i] * ticks;
            }
            break;
        case 0x0d:	//enhance cfg0_4
            for(i = 0; i < 288; i++)
            {
                 SentStaticData_0x0d[i] = cfg0_4[i] * ticks;
            }
            break;
        case 0x0e:	//enhance cfg0_5 normal crc
            for(i = 0; i < 324; i++)
            {
                 SentStaticData_0x0e[i] = cfg0_5[i] * ticks;
            }
            break;
        case 0x0f:	//enhance cfg0_6 normal crc
            for(i = 0; i < 360; i++)
            {
                 SentStaticData_0x0f[i] = cfg0_6[i] * ticks;
            }
            break;
        case 0x10:	//enhance cfg0_7 normal crc
            for(i = 0; i < 396; i++)
            {
                 SentStaticData_0x10[i] = cfg0_7[i] * ticks;
            }
            break;
        case 0x11:	//enhance cfg0_8
            for(i = 0; i < 432; i++)
            {
                 SentStaticData_0x11[i] = cfg0_8[i] * ticks;
            }
            break;
        case 0x12:	//enhance cfg0_4 normal crc
            for(i = 0; i < 288; i++)
            {
                 SentStaticData_0x12[i] = cfg0_4_crc[i] * ticks;
            }
            break;
        case 0x13:	//enhance cfg1_1    /*MJM: enhance cfg1_1为增强串行消息，有18个SENT帧，每帧数据段为1个Nibble*/
            for(i = 0; i < 180; i++)
            {
                 SentStaticData_0x12[i] = cfg1_1[i] * ticks;
            }
            break;
        case 0x14:	//enhance cfg1_2 normal crc
            for(i = 0; i < 216; i++)
            {
                 SentStaticData_0x14[i] = cfg1_2[i] * ticks;
            }
            break;
        case 0x15:	//enhance cfg1_3 normal crc
            for(i = 0; i < 252; i++)
            {
                 SentStaticData_0x15[i] = cfg1_3[i] * ticks;
            }
            break;
        case 0x16:	//enhance cfg1_4
            for(i = 0; i < 288; i++)
            {
                 SentStaticData_0x16[i] = cfg1_4[i] * ticks;
            }
            break;
        case 0x17:	//enhance cfg1_5 normal crc
            for(i = 0; i < 324; i++)
            {
                 SentStaticData_0x17[i] = cfg1_5[i] * ticks;
            }
            break;
        case 0x18:	//enhance cfg1_6 normal crc
            for(i = 0; i < 360; i++)
            {
                 SentStaticData_0x18[i] = cfg1_6[i] * ticks;
            }
            break;
        case 0x19:	//enhance cfg1_7 normal crc
            for(i = 0; i < 396; i++)
            {
                 SentStaticData_0x19[i] = cfg1_7[i] * ticks;
            }
            break;
        case 0x1a:	//enhance cfg1_8
            for(i = 0; i < 432; i++)
            {
                 SentStaticData_0x1a[i] = cfg1_8[i] * ticks;
            }
            break;
        case 0x1b:	//enhance cfg1_4 normal crc
            for(i = 0; i < 288; i++)
            {
                 SentStaticData_0x1b[i] = cfg1_4_crc[i] * ticks;
            }
            break;
        //Error waveform
        case 0x1c:	//Short serial Bit3 error
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x1c[i] = short_1_bit3_error[i] * ticks;
            }
            break;
        case 0x1d:	//Enhance serial Bit3 error
            for(i = 0; i < 180; i++)
            {
                 SentStaticData_0x1d[i] = cfg0_1_bit3_error[i] * ticks;
            }
            break;
        case 0x1e:	//Enhance serial Bit3 error
            for(i = 0; i < 180; i++)
            {
                 SentStaticData_0x1e[i] = cfg1_1_bit3_error[i] * ticks;
            }
            break;
        case 0x1f:	//Pause Pulse error
            for(i = 0; i < 24; i++)
            {
                 SentStaticData_0x1f[i] = stop_error_11[i] * ticks;
            }
            break;
        case 0x20:	//Pause Pulse error
            for(i = 0; i < 24; i++)
            {
                 SentStaticData_0x20[i] = stop_error_770[i] * ticks;
            }
            break;
        case 0x21:	//Calibrate Pulse error
            for(i = 0; i < 10; i++)
            {
                 SentStaticData_0x21[i] = fast_1_pulse_70[i] * ticks;
            }
            break;
        case 0x22:	//Calibrate Pulse error
            for(i = 0; i < 10; i++)
            {
                 SentStaticData_0x22[i] = fast_1_pulse_84[i] * ticks;
            }
            break;
        case 0x23:	//Calibrate Pulse error
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x23[i] = short_1_pulse_41[i] * ticks;
            }
            break;
        case 0x24:	//Data Tick error
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x24[i] = short_1_datatick_error_11tick[i] * ticks;
            }
            break;
        case 0x25:	//Data Tick error
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x25[i] = short_1_datatick_error_28tick[i] * ticks;
            }
            break;
        case 0x26:	//Burr waveform 25us
            for(i = 0; i < 170; i++)
            {
                 SentStaticData_0x26[i] = short_1_fil[i] * ticks;
            }
            break;
        case 0x27:	//Burr waveform 10us
            for(i = 0; i < 32; i++)
            {
                 SentStaticData_0x27[i] = fast_8_fil[i] * ticks;
            }
            break;
        case 0x28:	//reverse short 1 nibble
            for(i = 0; i < 160; i++)
            {
                 SentStaticData_0x28[i] = short_1_Rsvd[i] * ticks;
            }
            break;
        case 0x29:	//short 6 nibble a
            for(i = 0; i < 320; i++)
            {
                 SentStaticData_0x29[i] = short_6a[i] * ticks;
            }
            break;
        case 0x2a:	//short 6 nibble b
            for(i = 0; i < 320; i++)
            {
                 SentStaticData_0x2a[i] = short_6b[i] * ticks;
            }
            break;
        case 0x2b:	//short 1 nibble glitch
            for(i = 0; i < 192; i++)
            {
                 SentStaticData_0x2b[i] = short_1_glitch[i] * ticks;
            }
            break;
        case 0x2c: //short 6 normal crc
            for(i = 0; i < 319; i++)
            {
                 SentStaticData_0x2c[i] = short_6_crc[i] * ticks;
            }
            break;
        case 0x2d: //short 3 nibble + alter crc + no PausePulse
            for(i = 0; i < 191; i++)
            {
                 SentStaticData_0x2d[i] = short_3_alter_crc_nopause[i] * ticks;
            }
            break;
        case 0x2e: //short 3 nibble + alter crc
            for(i = 0; i < 223; i++)
            {
                 SentStaticData_0x2e[i] = short_3_alter_crc[i] * ticks;
            }
            break;
    }
    return TT_RET_SUCCESS;
}
