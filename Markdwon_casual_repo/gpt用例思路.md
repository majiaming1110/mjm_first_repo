
* Timeit函数测量的是接口的时间
* 虽然Base_drv_delay的定时可能不准，但是可以按照步骤run一次然后记录cnt的值，然后说预期cnt值应该是多少；就是不知道Base_drv_delay的不准是体现在每一次都会不一样？同一块芯片每次调用会不会不一样？还是每次都一样只是单纯让定时1ms它每次都定时1.2ms
  * 所以还是在IRQ里翻转IO，并查看翻转IO的脉宽


* 这次写的是SAT，可以参考以前颗粒度更细的SIT集成和SST合格
* 写代码的时候一般用两个assert，一个要观察API输出结果一个不用

# CASE1
* 涉及到中断和cnt++的，在start的时候testlib/timeit以下；然后象征性的base_drv_delay以下，在stop的时候在timeit以下；__两次timeit的时间差对应gpt开启的精确时间，应该可以和cnt的大小对应__

### GPT0
连续模式，120Mhz
1. init
2. 开中断
3. start 60000
4. 两个时间戳
5. 进中断，cnt++（程序外初始cnt
   
### GPT1
单次模式
就进依次中断

### GPT2
给外部时钟
20Mhz
比较中断进入次数

### GPT3
DIV 128/1   `128*60000/20Mhz`
比较中断进入次数

### GPT4
predef timer 16s



