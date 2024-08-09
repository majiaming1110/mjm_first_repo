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

2. 测试：`A8V3_Sent_DMAWorkMode_Normal_Test_Case("MCAL_Sent_003[NORMAL]")`为啥可以这么写

3. SENT.TST：
   1. `TaskActionCallback`中`if(task_idx < TST_Runtime.TimeDurations)`有什么意义？后者难道不是地址吗？
   2. `TST_INIT`中，为什么要清除`D_CACHE`？

   

---



### 临时问题
1. DFlash空间在map文件中为什么没有占用
2. 哪种方案更好？
   1. 将DFlash和PFlash的sync_read/write 写成一个函数，函数传入的值是真实地址
   2. 将DFlash和PFlash分开，各写一套sync_read/write函数，函数传入的地址是偏移



---



### 临时TODO LIST

- [x] **SENT_TST**: 测试一下TST，如果不删除信号最后一位，生成的波形是什么样的？
- [ ] **SNET_自己写的sent_signal_produce:** 
  - [x] 完善代码不使用malloc
  - [ ] 完善CRC函数的编码
  - [x] 根据MIZAR C规范，为每一个if写一个else
  - [ ] 优化实现逻辑，让信号生成的更加实时
  - [ ] 问题找到了！？不能在函数传参的时候强转成更大的数据
- [x] 将LMA, VMA整理到别处
- [x] 记录如何在程序中调用map中的符号地址



---



### tmp思路

1. 



---
