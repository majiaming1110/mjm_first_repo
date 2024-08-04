### Typora激活码

`uOIqj26Dz3nNSYF00s4paGgzfoGSh1zpP94V59p5s84son7syzCR0w1iaXPb/GNWwpzVQDBHd6vgyHXptveBGG5YL5tAMbjBxm8BiGCFhyQ0HGC0OXFv0KIHG4XD4RO5RHjOzfcsozxVyHVVVaLqTA==`



---



### 长远学习计划
* TTStudio工程结构整理
* 编译器，ld方向学习
* 写一个能自动化运行windows `.exe`的脚本



---



### 一周总结

* SENT测试代码
  * SENT的看门狗
  * SENT DMA传输的中断入参
  * SENT FIFO & FRAMEDATA & 毛刺
  * SENTG --- ALTER CRC
  * 关于自动生成SENT代码的优化编写，支持自定义信号...



---



### 暂存问题

1. bsp工程下port模块初始化传参问题
2. SENT.TST：
   1. `TaskActionCallback`中`if(task_idx < TST_Runtime.TimeDurations)`有什么意义？后者难道不是地址吗？
   2. `TST_INIT`中，为什么要清除`D_CACHE`？



---



### 临时问题
1. `A8V3_Sent_DMAWorkMode_Normal_Test_Case("MCAL_Sent_003[NORMAL]")`为啥可以这么写



---



### 临时TODO LIST

- [ ] **SENT_TST**: 测试一下TST，如果不删除信号最后一位，生成的波形是什么样的？

- [ ] **SNET_自己写的sent_signal_produce:** 
  - [ ] 完善代码不使用malloc
  - [ ] 完善CRC函数的编码
  - [ ] 根据MIZAR C规范，为每一个if写一个else
  - [ ] 优化实现逻辑，让信号生成的更加实时
- [ ] ~~SENT: 结构体的nibble数量定义成一个枚举，使得程序中可以直接命名~~



---



### tmp思路

1. 定义数组时，默认给数据段分配8个nibble，这样就不用使用malloc申请堆的空间了

2. ~~length固定了,别忘了是8*2！~~，length的大小根据nibble的大小来，不用刻意填满整个数组

3. 对于每一帧中的赋值，使用mask来和枚举

    1. 用一个程序定义各个nibble情况，比如:

        > 或许写成宏的方式更好？
        
        ```
        static uint32 Get_Data_Mask( nibble_num )
        {
            uint32 data_mask;
        
            if (nibble_num == 1) 
            {
                data_mask = 0x20;	
            }
            else if (nibble_num == 2) 
            {
                data_mask = 0xA0;	
            }
            else if (nibble_num == 3) 
            {
                data_mask = 0x2A0;	
            }
            else if (nibble_num == 4) 
            {
                data_mask = 0xAA0;	
            }
            else if (nibble_num == 5) 
            {
                data_mask = 0x2AA0;	
            }
            else if (nibble_num == 6) 
            {
                data_mask = 0xAAA0;	
            }
            else if (nibble_num == 7) 
            {
                data_mask = 0x2AAA0;	
            }
            else if (nibble_num == 8) 
            {
                data_mask = 0xAAAA0;	
            }
            else
            {
                //do nothing
            }
        
            return data_mask;
        }
        ```
        
    2. 然后在每一帧的有效值赋值时，使用如下的语法：**且额外定义bit15为level位，用于指示该有效数据是否为高电平

        ```
        #define HIGH 1
        #define LOW 0
        
        if (j == 0)
        {
        	Signal[index] = 6;
        	// low level 不用操作
        }
        else if (j == 1)
        {
        	Signal[index] = 50;
        	/* level位置起*/
        	Signal[index] &= （0x1 << 15);
        }
        else if ((0x1 << j) & data_mask)
        {
        	Signal[index] = XXX;
        	Signal_Level[index] = HIGH;
        	/* level位置起*/
        	Signal[index] &= （0x1 << 15);
        }
        ...
        ...
        ```

4. ~~关于除数据段之外的赋值逻辑不需要大改，只需要基于"length固定这一点来改就OK"~~

5. ~~关于数据段，根据结构体的NIBBLE数量来赋值~~
    ~~3.1 对于每一帧，有8个数据空间，且前面的有固定2帧（同步段和校验段）,所以赋值固定从“j == 5”开始~~
    ~~3.2 第一个数据j=5  第二个数据j=7  第三个数据j=9~~

6. ~~在生成信号的时候，需要增加对于数据段的判断~~
   
    * ~~在生成信号时，也需要在for里面嵌套一个对每一帧的循环：在每一帧中，从j==5后：~~
    ```
    if ((j >= 5) && (j < = (5 + (2 * (nibblenum - 1)))) && (j % 2 != 0))
    ```
    
7. 在生成信号时，同时遍历`Signal`：

   * 对于高低电平：`Signal[index] & 0x8000`
   * 对于真实数据：`Signal[index] & 0xFF`

8. 关于翻转的实时性：

   * 仿照TST.c中的逻辑来写，使用systick？



---
