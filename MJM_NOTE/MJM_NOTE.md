### Typora激活码
`uOIqj26Dz3nNSYF00s4paGgzfoGSh1zpP94V59p5s84son7syzCR0w1iaXPb/GNWwpzVQDBHd6vgyHXptveBGG5YL5tAMbjBxm8BiGCFhyQ0HGC0OXFv0KIHG4XD4RO5RHjOzfcsozxVyHVVVaLqTA==`



---



### 长远学习计划
* TTStudio工程结构整理
* 编译器，ld方向学习
* 写一个能自动化运行windows `.exe`的脚本



---



### 一周总结

* SENT的看门狗
* SENT DMA传输的中断入参
* SENT FIFO & FRAMEDATA & 毛刺
* SENT测试代码



---



### 暂存问题

1. bsp工程下port模块初始化传参问题



---



### 临时问题
1. `A8V3_Sent_DMAWorkMode_Normal_Test_Case("MCAL_Sent_003[NORMAL]")`为啥可以这么写



---



### 临时TODO LIST

- [ ] SNET: 完善代码不使用malloc
- [ ] SENT: 完善CRC函数的编码
- [ ] SENT: 根据MIZAR C规范，为每一个if写一个else
- [ ] SENT: 优化实现逻辑，让信号生成的更加实时
- [ ] SENT: 结构体的nibble数量定义成一个枚举，使得程序中可以直接命名



---



### tmp思路

1. 定义数组时，默认给数据段分配8个nibble，这样就不用使用malloc申请堆的空间了

2. length固定了,别忘了是8*2！

3. 关于除数据段之外的赋值逻辑不需要大改，只需要基于"length固定这一点来改就OK"

3. 关于数据段，根据结构体的NIBBLE数量来赋值
    3.1 对于每一帧，有8个数据空间，且前面的有固定2帧（同步段和校验段）,所以赋值固定从“j == 5”开始
    3.2 第一个数据j=5  第二个数据j=7  第三个数据j=9
    
4. 在生成信号的时候，需要增加对于数据段的判断
    * 在生成信号时，也需要在for里面嵌套一个对每一帧的循环：在每一帧中，从j==5后：
    ```
    if ((j >= 5) && (j < = (5 + (2 * (nibblenum - 1)))) && (j % 2 != 0))
    ```
    



---

