# ARM Cortex-M7



## OVERALL 知识点

* ARM芯片：
  * `V系列`指的是**ARM的架构版本**，比如ARMv7、ARMv8等。这些版本定义了**处理器**的指令集架构（ISA）和相关的功能特性。
  * `M系列`指的ARM公司设计的一系列**基于ARMv架构的微控制器处理器内核**，主要特点是低功耗、低成本、高效能，适合用于嵌入式系统和IoT（物联网）设备
  
* ARM Cortex-M 处理器中，一个字（word）通常是 32 位，也就是 4 字节。

* `CMSIS`：**Cortex Microcontroller Software Interface Standard**，是由ARM公司开发的一套标准化的软件接口。它旨在简化微控制器软件开发，特别是针对基于ARM Cortex-M处理器的微控制器。CMSIS为开发人员提供了一致的编程接口，以便更轻松地进行嵌入式系统的开发和移植

* 处理器的配置基于`little-endian` 格式

* 存储器：

  * **RAM**：断电后数据丢失，快，贵
    * SRAM
      * TCM:
      * DCM:
  * **ROM**：断电数据依然在，慢，便宜
    * EEPROM：可擦除，支持单字节擦除和编程
    * FLASH：可擦除，但只在页/块的颗粒度上擦除，大容量低成本

* 对于M7核来说，毫无疑问它是ARM架构的，所以会遵循***AAPCS协议（ARM Architecture Procedure Call Standard）***，在AAPCS中规定，**==SP（栈指针）必须是4字节对齐==**，这是一个非常重要的概念，对此可以引申出两个例子

   1. 在进入一个函数A时，C语言的反汇编会自动将相关寄存器压入堆栈，如果在函数A中定义了一个uint32的变量`a`，并在函数A中再次调用函数B，在函数B传参时，将变量`a`强转成一个uint64的指针`（uint64 *）&a`。这个操作会导致严重的错误：**已知局部变量，函数传递的参数都会在栈中，且向下生长**。那么目前栈的情况是：

      > 【 进入函数A时最后一个被压入栈里的寄存器的值 】 --- 4字节（最高地址）
      >
      > ​								|
      >
      > 【进入函数A时倒数第二个被压入栈里的寄存器的值 】 --- 4字节
      >
      > ​								|
      >
      > ​							.........
      >
      > ​								|
      >
      > 【 进入函数A时第一个被压入栈里的寄存器的值 】 --- 4字节
      >
      > ​								|
      >
      > ​						【局部变量`a`】 --- 4字节（uint32）

      此时，调用函数B，会将`a`的地址传给函数B，但是由于此时强转成了uint64，因此，**编译器需要给`a`的地址分配大小为uint64的空间来存储，这就会导致`进入函数A时第一个被压入栈里的寄存器的值`被覆盖！所以当函数退出A想要push当时保存的寄存器值时，就会造成错误！**如果变量`a`一开始赋值为uint8，并在函数B传参时扩展成`（uint32 *）&a`，同样可能发生错误！！因为uint8变量通常存放在4字节的最高字节，以最高字节为地址向上扩展为uint32，同样会覆盖上一个4字节的低3字节！**==所以，在函数传参的时候，如果需要传入地址，地址的类型的大小一定不能超过参数类型的大小！==**  *但如果在函数B中对非指针类型变量进行非指针类型的类型扩展将不会导致问题，因为这种情况下，编译器只会操作有效数据，虽然类型变大了，但是有效数据的大小没有变*

   2. 同样，由于SP是四字节对齐的，所以如果连续向栈中压入uint64和uint8两个变量，栈的情况会变成：
   
      > 【[uint8 变量存储的空间，位于地址最高的1字节] + **[低三字节]**】
      >
      > ​								|
      >
      > ​				【uint64的高4字节数据】
      >
      > ​								|
      >
      > ​				【uint64的低4字节数据】
   
      uint64并不会直接连续的存储在uint8后的空间，而是在下一个4字节对齐的地方开始写，**uint8下方的低三字节将不会存储有效数据**

* 



## 内存模型 Memory Model

### ITCM/DTCM(ARM核存储空间)

* 在 ARM 处理器架构中，紧耦合存储器 (Tightly-Coupled Memory, TCM) 是一种专用的高性能内存，用于存储时间敏感的数据和指令。TCM 分为两种类型：指令紧耦合存储器 (Instruction TCM, ITCM) 和 数据紧耦合存储器 (Data TCM, DTCM)。这两种存储器通常直接连接到处理器核心，提供比外部存储器更快的访问速度。
* 应用场景：
  * 涉及DMA需要搬运的数据，可以为其加上`__attribute__ ((section (".mcal_data_dtcm")))`的属性；使用 DTCM 作为数据存储区域，并通过 DMA 进行数据传输，可以显著提升系统的响应时间和数据处理效率
  * 对于需要快速处理的函数/代码，在定义前指定`__attribute__((section(".mcal_text_itcm")))`属性，但注意，__这句话的作用域仅限紧跟的一个函数__
    ![image-20240809200837914](pic/image-20240809200837914.png)



## 异常模型 Exception Model

### 不同中断的属性对照表

![image-20240809200858500](pic/image-20240809200858500.png)

![image-20240809200913507](pic/image-20240809200913507.png)

* CMSIS使用的是IRQ号
* 异常的处理：
  * *IRQ0~239* 由 **Interrupt Service Routines (ISRs)**来处理
  * *HardFault, MemManage fault, UsageFault, and BusFault* 由 **Fault handlers**来处理
  * *NMI, PendSV, SVCall, SysTick 和上述 fault exceptions* 都属于系统异常 由**System handlers**来处理
* **Vector Table**:

> <img src="pic/image-20240809200931763.png" alt="image-20240809200931763" style="zoom:67%;" />
>
> PS：这个表格展示的是最多中断情况下的状态
>
> * 各个中断在VectorTable中相对偏移的计算：`Exception_num x 4(Byte) `



### VTOR寄存器

`VTOR寄存器`：**SCB模块的一个寄存器**，32位，有效位bit7~31，存储中断向量表的基地址，也就是说，**存放的是整个`Vextor Table`的首地址于0x00000000的偏移** 

> 如果Vector Table的起始地址是0x00000005, 那VTOR中就从bit7开始存0x00000005；

* 在`src/bsp/env/vector_table_m7.S`中，用汇编定义了详细的中断向量表，且将16位之后的外部中断函数全部定义成了可以被重写的`weak`函数；在`Platform_IntCtrl_Cfg.h`中，将所有外部中断的weak函数重新定义。如果在配置的时候，将某个外部中断打开，那么程序会读取配置生成的`Platform_IntCtrl_PBCfg.c`，找到开启的中断号并通过操控`NVIC`模块的`IESR`寄存器打开中断
  <img src="pic/image-20240809201026330.png" alt="image-20240809201026330" style="zoom:50%;" />

* 如果前15个中断号有对应的模块且该模块开启了中断，那么中断处理函数就会默认在`src/bsp/env/exceptions_m7.c`中被定义，且在这个文件中被赋予`weak`属性
  <img src="pic/image-20240809201048413.png" alt="image-20240809201048413" style="zoom:50%;" />

* 在中断向量表中，每个ISR占一个`word`的大小（4字节）
  __由于上述这些中断都是weak属性的，所以可以选择动态重写这些函数，我们现在已经知道VectorTable的起始地址存储在`SCB->VTOR`中，那么根据C语言语法，VectorTable就是每个元素为一个字（4字节，32位，uint32）且数组名为`SCB->VTOR`的数组: `((uint32 *)SCB->VTOR)[ ] `。且根据VectorTable不难看出每个ISR函数的相对偏移，比如我想重写SYSTick的回调函数，SYSTick是VectorTable的第15个元素，那么*SYSTick的ISR函数入口地址*就可以表示为`((uint32 *)SCB->VTOR)[15]`__

  * 将SYSTICK中断回调动态设置的典型示例：

    ```    
    ((volatile uint32 *)TT_SCB->VTOR)[16+SysTick_IRQn]
    = (uint32)&TST_IRQHandler;
    ```

    这样，当 SysTick 发生中断时，处理器会跳转到 TST_IRQHandler 函数执行相应的中断处理程序



## 外设 Peripherals

### CORE Peripherals

* **Nested Vectored Interrupt Controller** --- **NVIC模块**

  The NVIC is an embedded interrupt controller that supports low latency interrupt 

  processing.

  

*  **System Control Block** --- **SCB模块**

  * The *System Control Block* (SCB) is the programmers model interface to the processor. It provides system implementation information and system control, including configuration, control, and reporting of system exceptions.

  * 提供系统实现信息和系统控制，它包括系统异常的配置、控制和报告

    

* **System timer** --- **Systick模块**

  * The system timer, SysTick, is a 24-bit count-down timer. Use it as a *Real Time* *Operating System* (RTOS) tick timer or as a simple counter.
  * 本质是一个24bit，向下且循环计数的计数器；在处理器时钟上运行
  * CSR寄存器的bit0用于开启计数；bit1用于开启中断

  

* **Integrated instruction and data caches (optional)** 

  The instruction and data caches provide fast access to frequently accessed data 

  and instructions, that support increased average performance when using system 

  based memory.

  

* **Memory Protection Unit (optional)** 

  The *Memory Protection Unit* (MPU) improves system reliability by defining the 

  memory attributes for different memory regions. Depending on your 

  implementation, it provides up to 8 or 16 different regions, and an optional 

  predefined background region.

  

*  **Floating-point unit (optional)** 

  The FPU provides IEEE754-compliant operations on 32-bit single-precision and 

  implementation-defined 64-bit double-precision floating-point values.


