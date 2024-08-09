#include <stdio.h>
#include "Mcu.h"
#include "Mcu_Drv.h"
#include "Base_Drv.h"
#include "Port_Drv.h"
#include "Uart_Drv.h"

extern const float32 short_1[160];//0x01
extern const float32 short_2[192];//0x02
extern const float32 short_3[224];//0x03
extern const float32 short_4[256];//0x04
extern const float32 short_5[288];//0x05
extern const float32 short_6[319];//0x06
extern const float32 short_6_crc[319];//0x2c
extern const float32 short_7[352];//0x07
extern const float32 short_8[384];//0x08
extern const float32 short_4_crc[255];//0x09
extern const float32 cfg0_1[180];//0x0a
extern const float32 cfg0_2[216];//0x0b
extern const float32 cfg0_3[252];//0x0c
extern const float32 cfg0_4[288];//0x0d
extern const float32 cfg0_5[324];//0x0e
extern const float32 cfg0_6[360];//0x0f
extern const float32 cfg0_7[396];//0x10
extern const float32 cfg0_8[432];//0x11
extern const float32 cfg0_4_crc[288];//0x12
extern const float32 cfg1_1[180];//0x13
extern const float32 cfg1_2[216];//0x14
extern const float32 cfg1_3[252];//0x15
extern const float32 cfg1_4[288];//0x16
extern const float32 cfg1_5[324];//0x17
extern const float32 cfg1_6[360];//0x18
extern const float32 cfg1_7[396];//0x19
extern const float32 cfg1_8[432];//0x1a
extern const float32 cfg1_4_crc[288];//0x1b
extern const float32 short_1_bit3_error[160];//0x1c
extern const float32 cfg0_1_bit3_error[180];//0x1d
extern const float32 cfg1_1_bit3_error[180];//0x1e
extern const float32 stop_error_11[24];//0x1f
extern const float32 stop_error_770[24];//0x20
extern const float32 fast_1_pulse_70[10];//0x21
extern const float32 fast_1_pulse_84[10];//0x22
extern const float32 short_1_pulse_41[160];//0x23
extern const float32 short_1_datatick_error_11tick[160];//0x24
extern const float32 short_1_datatick_error_28tick[160];//0x25
extern const float32 short_1_fil[170];//0x26
extern const float32 fast_8_fil[32];//0x27
extern const float32 short_1_Rsvd[160];//0x28
extern const float32 short_6a[320];//0x29
extern const float32 short_6b[320];//0x2a
extern const float32 short_1_glitch[192];//0x2b


extern const float32 short_3_alter_crc_nopause[191]; //0x2d
extern const float32 short_3_alter_crc[223]; //0x2e

