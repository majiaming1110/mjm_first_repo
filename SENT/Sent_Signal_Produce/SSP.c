#include "Port_Drv.h"
#include "Dio_Drv.h"
#include "SSP.h"
#include "SentCrc.h"
#include "Platform_Drv.h"
#include "A8V2E_NVIC.h"
#include "A8V2E_SYSTICK.h"
#include "Base_Drv.h"

volatile int index;
volatile int range;
Dio_PortLevelType Bit = 0u;
/*能够容纳最长SENT信号组的数组*/
uint32 Signal[SIGNAL_SIZE] = {0};
/*能够容纳最长数据段的数组*/
uint32 DATA[8] = {0};

SENT_SIGNAL_CONFIG SENT_SIGNAL =
{
    .type = SHORT, 
    .tick = 3.0f,
    .time_unit = US,
    .nibble_num = 6,
    .frame_data = 0x0,
    .default_lowpulse = 5,
    .pause_pulse = ON,
    .output_port = DioPort_0_DioChannel_0,
    .CRC_mode = RECOMMEND,
    .run_time = IDLE,
    .reverse = OFF
};

LOCAL_INLINE void NextIndex(void)
{
	/* 关闭SYSTICK */
	TT_SYSTICK->CSRr |= TT_SYSTICK_CSR_ENABLE(0u);

	/* 如果当前的index还没有超出有效值范围 */
	if (index < range)
	{
		/* 装载数组中的下一个有效值，屏蔽LEVEL位 */
		TT_SYSTICK->RVR = TT_SYSTICK_RVR_RELOAD(Signal[index] & 0xFFFF);
		/* 开启SYSTICK */
		TT_SYSTICK->CSRr |= TT_SYSTICK_CSR_ENABLE(1u);
	}
    else
	{
		/*全局变量清0，非常重要*/
		index = 0;
        range = 0;
        SENT_SIGNAL.run_time = IDLE;
        //TT_GPIO0->DATA_SET = (uint32)(0x1UL << Bit);
        /* 也就是说，如果当前index超出了有效值范围，那么SYSTICK会直接关闭不会再打开 */
	}

}


void TST_IRQHandler(void)
{
    if ((Signal[index] & 0x80000) || (index == range))
	//if (Signal[index] & 0x80000)
    {
        /*level位置起，说明有效数据期望以高电平的形式模拟*/
        TT_GPIO0->DATA_SET = (uint32)(0x1UL << Bit);
    }
    else
    {
        TT_GPIO0->DATA_CLR = (uint32)(0x1UL << Bit);
    }

    index++;
    NextIndex();
}

void TST_IRQHandler_Reverse(void)
{
    if ((Signal[index] & 0x80000) || (index == range))
	//if (Signal[index] & 0x80000)
    {
        /*level位置起，说明有效数据期望以高电平的形式模拟*/
        TT_GPIO0->DATA_CLR = (uint32)(0x1UL << Bit);
    }
    else
    {
        TT_GPIO0->DATA_SET = (uint32)(0x1UL << Bit);
    }

    index++;
    NextIndex();
}

LOCAL_INLINE void Clean_Signal(void)
{
    for (int i = 0; i < SIGNAL_SIZE; i++)
    {
        Signal[i] = (uint32)0;
    }
}

LOCAL_INLINE void Sent_Systick_Init(void)
{
    Bit = (Dio_PortLevelType)(SENT_SIGNAL.output_port % 32);
    TT_SYSTICK->CSRr = 0U;
	TT_SYSTICK->CVR = TT_SYSTICK_CVR_CURRENT(0U);
	/*打开SYSTICK中断 + 使用处理器时钟*/
	TT_SYSTICK->CSRr |= TT_SYSTICK_CSR_CLKSOURCE(1u) | TT_SYSTICK_CSR_TICKINT(1u);
	/*MJM: 将 TST_IRQHandler 函数的地址设置为中断向量表中与 SysTick 中断对应的入口处*/
	/*这样，当 SysTick 发生中断时，处理器会跳转到 TST_IRQHandler/TST_IRQHandler_Reverse 函数执行相应的中断处理程序*/
    if (SENT_SIGNAL.reverse == OFF)
    {
        ((volatile uint32 *)TT_SCB->VTOR)[16+SysTick_IRQn] = (uint32)&TST_IRQHandler;
    }
    else
    {
        ((volatile uint32 *)TT_SCB->VTOR)[16+SysTick_IRQn] = (uint32)&TST_IRQHandler_Reverse;
    }
	

	Platform_Drv_Cache_CleanDCache();
    index = 0;
}

LOCAL_INLINE void Sent_Systick_Start(void)
{
    /*设置信号状态*/
    SENT_SIGNAL.run_time = BUSY;
    /* 关闭SYSTICK */
	TT_SYSTICK->CSRr |= TT_SYSTICK_CSR_ENABLE(0u);
	/* 装载数组中的第一个有效值，屏蔽LEVEL位*/
	TT_SYSTICK->RVR = TT_SYSTICK_RVR_RELOAD(Signal[index] & 0xFFFF);
	/* 打开SYSTICK */
	TT_SYSTICK->CSRr |= TT_SYSTICK_CSR_ENABLE(1u);
}


LOCAL_INLINE uint32 status_build(uint32 i)
{
    int type = SENT_SIGNAL.type;
    uint32 value = (uint32)0;

    if (type == SHORT)
    {
        if ((0x1 << i) & short_mask_11)
        {
            value = (uint32)11;
        }
        else if ((0x1 << i) & short_mask_7)
        {
            value = (uint32)7;
        }
        else if ((0x1 << i) & short_mask_19)
        {
            value = (uint32)19;
        }
        else
        {
        	value = 0;
        }
    }
    else if (type == ENHANCE)
    {
        if ((0x1 << i) & enhance__mask_19)
        {
            value = (uint32)19;
        }
        else if ((0x1 << i) & enhance__mask_15)
        {
            value = (uint32)15;
        }
        else if ((0x1 << i) & enhance__mask_11)
        {
            value = (uint32)11;
        }
        else if ((0x1 << i) & enhance__mask_7)
        {
            value = (uint32)7;
        }
        else
        {
        	value = 0;
        }

    }
    else
    {
    	value = 0;
    }

    return value;
}

TT_RetType Sent_Signal_Build(void)
{
    /*期望SENT模拟信号的一帧长度*/
    int length = 2 * (1 + 1 + SENT_SIGNAL.nibble_num + 1 + SENT_SIGNAL.pause_pulse);
    /*期望SENT模拟信号的有效值长度*/
    int len = (SENT_SIGNAL.type) * length;
    uint64 CRC = 0;
    int inner_index = 0;
    uint32 status = 0;
    uint32 Systick_CountPerUs = (uint32)(SENT_SIGNAL.tick * (float32)(CLOCK_SRC / SENT_SIGNAL.time_unit));

    range = len;

    Sent_Systick_Init();

    /*非必要，省略可以大大节省时间*/
    //Clean_Signal();

    //printf("expected data = 0x%x\r\n",SENT_SIGNAL.frame_data);

    for (int i = 0; i < (SENT_SIGNAL.nibble_num); i++)
    {
        DATA[i] = (SENT_SIGNAL.frame_data << (i * 4)) >> (((7 - i) * 4) + (i * 4));
        //printf("DATA[%d]=0x%x\r\n",i,DATA[i]);
    }

    for (int i = 0; i < (SENT_SIGNAL.type); i++)
    {
        for (int j = 0; j < length; j++)
        {
            inner_index = i * length + j;
            /*非0偶数项*/
            if (LOW_PULSE)
            {
                Signal[inner_index] = (uint32)SENT_SIGNAL.default_lowpulse;
                Signal[inner_index] *= Systick_CountPerUs;
            }
            else if (SYNC_LOW)
            {
                Signal[inner_index] = (uint32)6;
                Signal[inner_index] *= Systick_CountPerUs;
            }
            else if (SYNC_HIGH)
            {
                Signal[inner_index] = (uint32)50;
                Signal[inner_index] *= Systick_CountPerUs;
                /* level位置起*/
	            Signal[inner_index] |= (0x1 << 19);
            }
            else if (STATUS_HIGH)
            {
                /*状态段*/
//                if (SENT_SIGNAL.pause_pulse == ON)
//                {
                    Signal[inner_index] = status_build(i);
                    status = status_build(i) + SENT_SIGNAL.default_lowpulse - 12;
//                }
//                else
//                {
//                    /*若没有暂停脉冲，则默认状态段值一直为3*/
//                    Signal[inner_index] = (uint32)(3 + 12 - SENT_SIGNAL.default_lowpulse);
//                }
                Signal[inner_index] *= Systick_CountPerUs;
                /* level位置起*/
	            Signal[inner_index] |= (0x1 << 19);
            }
            else if (PAUSE_HIGH)
            {
                Signal[inner_index] = (uint32)12;
                Signal[inner_index] *= Systick_CountPerUs;
                /* level位置起*/
	            Signal[inner_index] |= (0x1 << 19);
            }
            else if (CRC_HIGH)
            {
                uint64 Data = (uint64)((SENT_SIGNAL.frame_data) >> (4 * (8 - SENT_SIGNAL.nibble_num)));
                if (SENT_SIGNAL.CRC_mode == TRADITION)
                {
                    Sent_Legend_Crc_Calc(Data, (uint64)SENT_SIGNAL.nibble_num, &CRC);
                }
                else if (SENT_SIGNAL.CRC_mode == RECOMMEND)
                {
                    Sent_Recommend_Crc_Calc(Data, (uint64)SENT_SIGNAL.nibble_num, &CRC);
                }
                else if (SENT_SIGNAL.CRC_mode == ALTER)
                {
                    /*ALTER CRC时，默认选择带状态的CRC*/
                    Sent_Alter_Crc_Calc((uint64)SENT_SIGNAL.nibble_num, (uint64)SENT_SIGNAL.frame_data, status, &CRC);
                }
                else
                {
                    //do nothing
                }
                Signal[inner_index] = (uint32)((int)CRC + 12 - SENT_SIGNAL.default_lowpulse);
                Signal[inner_index] *= Systick_CountPerUs;
                /* level位置起*/
	            Signal[inner_index] |= (0x1 << 19);
            }
            /*数据段*/
            else
            {
                Signal[inner_index] = (uint32)(DATA[j/2 - 2] + 12 - SENT_SIGNAL.default_lowpulse);
                Signal[inner_index] *= Systick_CountPerUs;
                /* level位置起*/
	            Signal[inner_index] |= (0x1 << 19);
            } 
            //printf("%d, ", (Signal[inner_index]&0xFFFF)/Systick_CountPerUs);        
        }
        //printf("\r\n");
    }

    /*打开systick，开始输出信号*/
    Sent_Systick_Start();

    while (SENT_SIGNAL.run_time == BUSY)
    {
        //等待SENT信号生成完毕
    }

    return TT_RET_SUCCESS; 
}
