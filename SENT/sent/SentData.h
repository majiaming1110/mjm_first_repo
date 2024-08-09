#include "Base_Drv.h"
#include "timer.h"
/******************************************************************************
*                       Definition
******************************************************************************/
//short 1 nibble
extern float32 SentStaticData_0x01[160];
//short 2 nibble
extern float32 SentStaticData_0x02[192];
//short 3 nibble
extern float32 SentStaticData_0x03[224];
//short 4 nibble
extern float32 SentStaticData_0x04[256];
//short 5 nibble
extern float32 SentStaticData_0x05[288];
//short 6 nibble
extern float32 SentStaticData_0x06[319];
//short 6 nibble normal crc
extern float32 SentStaticData_0x2c[319];
//short 7 nibble
extern float32 SentStaticData_0x07[352];
//short 8 nibble
extern float32 SentStaticData_0x08[384];
//short 4 nibble normal crc
extern float32 SentStaticData_0x09[255];
//enhance cfg0_1
extern float32 SentStaticData_0x0a[180];
//enhance cfg0_2
extern float32 SentStaticData_0x0b[216];
//enhance cfg0_3 normal crc
extern float32 SentStaticData_0x0c[252];
//enhance cfg0_4
extern float32 SentStaticData_0x0d[288];
//enhance cfg0_5 normal crc
extern float32 SentStaticData_0x0e[324];
//enhance cfg0_6 normal crc
extern float32 SentStaticData_0x0f[360];
//enhance cfg0_7 normal crc
extern float32 SentStaticData_0x10[396];
//enhance cfg0_8
extern float32 SentStaticData_0x11[432];
//enhance cfg0_4 normal crc
extern float32 SentStaticData_0x12[288];
//enhance cfg1_1
extern float32 SentStaticData_0x13[180];
//enhance cfg1_2 normal crc
extern float32 SentStaticData_0x14[216];
//enhance cfg1_3 normal crc
extern float32 SentStaticData_0x15[252];
//enhance cfg1_4
extern float32 SentStaticData_0x16[288];
//enhance cfg1_5 normal crc
extern float32 SentStaticData_0x17[324];
//enhance cfg1_6 normal crc
extern float32 SentStaticData_0x18[360];
//enhance cfg1_7 normal crc
extern float32 SentStaticData_0x19[396];
//enhance cfg1_8
extern float32 SentStaticData_0x1a[432];
//enhance cfg1_4 normal crc
extern float32 SentStaticData_0x1b[288];
//Short serial Bit3 error
extern float32 SentStaticData_0x1c[160];
//Enhance serial Bit3 error
extern float32 SentStaticData_0x1d[180];
//Enhance serial Bit3 error
extern float32 SentStaticData_0x1e[180];
//Pause Pulse error 11
extern float32 SentStaticData_0x1f[24];
//Pause Pulse error 770
extern float32 SentStaticData_0x20[24];
//Calibrate Pulse error 70
extern float32 SentStaticData_0x21[10];
//Calibrate Pulse error 84
extern float32 SentStaticData_0x22[10];
//Calibrate Pulse error 41
extern float32 SentStaticData_0x23[160];
// Data Tick error
extern float32 SentStaticData_0x24[160];
// Data Tick error
extern float32 SentStaticData_0x25[160];
//Burr waveform 25us
extern float32 SentStaticData_0x26[170];
//Burr waveform 10us
extern float32 SentStaticData_0x27[32];
//reverse short 1 nibble
extern float32 SentStaticData_0x28[160];
//reverse short 1 nibble
extern float32 SentStaticData_0x29[320];
//reverse short 1 nibble
extern float32 SentStaticData_0x2a[320];
//short 1 nibble glitch
extern float32 SentStaticData_0x2b[192];

//short 3 nibble + alter crc + no PausePulse
extern float32 SentStaticData_0x2d[191];
//short 3 nibble + alter crc
extern float32 SentStaticData_0x2e[223];


extern TT_RetType sent_config(const uint32 ticks, uint32 message_type);
