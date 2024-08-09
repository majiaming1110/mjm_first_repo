#define CLOCK_SRC 240000000
#define US 1000000
#define MS 1000
#define S 1
#define SHORT 16
#define ENHANCE 18
#define ON 1
#define OFF 0
#define TRADITION 1
#define RECOMMEND 2
#define ALTER 3
#define IDLE 1
#define BUSY 2
#define SIGNAL_SIZE (18 * 2 * (1 + 1 + 8 + 1 + 1))

#define short_mask_11  0x95F8
#define short_mask_7  0x6A06
#define short_mask_19  0x1
#define enhance__mask_19  0x12C3B
#define enhance__mask_15  0x204
#define enhance__mask_11  0x5080
#define enhance__mask_7  0x28140

#define LOW_PULSE (((j % 2) == 0) && (j != 0))
#define SYNC_LOW (j == 0)
#define SYNC_HIGH (j == 1)
#define STATUS_HIGH (j == 3)
#define PAUSE_HIGH ((j == (length - 1)) && (SENT_SIGNAL.pause_pulse == ON))
#define CRC_HIGH (((j == (length - 3)) && (SENT_SIGNAL.pause_pulse == ON)) || ((j == (length - 1)) && (SENT_SIGNAL.pause_pulse == OFF)))


/*对于IRQ中可能会被修改的变量，要加上volatile防止编译器优化*/
typedef struct 
{
    int type; //SHORT or ENHANCE
    float32 tick;
    uint32 time_unit;
    int nibble_num;
    uint32 frame_data; //期望输出的FRAMEDATA
    int default_lowpulse; //每个Nibble的低电平持续时间，目前只支持设置成一样的 
    char pause_pulse; //暂停脉冲开关, 打开后固定为5tick
    uint32 output_port; //输出SENT信号的GPIO口
    char CRC_mode; //TRADITION or RECOMMEND or ALTER
    char reverse;
    
    /*runtime的定义非常重要，因为现在考SYSTICK的IRQ来进行翻转*/
    /*所以如果不设置一个runtime卡着，就会发生：
    “程序已经往下走了，但是有效值的数组还没有跑完，SYSTICK依然在不断进中断”
    的情况*/
    volatile char run_time; //用于指示当前SENT信号是否跑完
}SENT_SIGNAL_CONFIG;

extern SENT_SIGNAL_CONFIG SENT_SIGNAL;
extern TT_RetType Sent_Signal_Build(void);
