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
  * 关于自动生成SENT代码的优化编写，支持自定义信号...
* Pflash 和 SRAM的同步写入/读取



---



### 暂存问题

1. bsp工程下port模块初始化传参问题

2. SENT.TST：
   1. `TaskActionCallback`中`if(task_idx < TST_Runtime.TimeDurations)`有什么意义？后者难道不是地址吗？
   2. `TST_INIT`中，为什么要清除`D_CACHE`？
   
   

---



### 临时问题
1. `A8V3_Sent_DMAWorkMode_Normal_Test_Case("MCAL_Sent_003[NORMAL]")`为啥可以这么写
2. SENT：为什么Sent_Systick_Init()执行前index还会走？
3. 为什么有些段在.map文件中的LMA和VMA是一样的，有些则不一样



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

1. 



---
