## 综述

TTA8的程序内存空间分配大致遵循**C语言的内存分区法则**：

<img src="C:\Users\admin\Desktop\MJM_personal_repo\Markdwon_casual_repo\pic\image-20240807140045486.png" alt="image-20240807140045486" style="zoom:50%;" />

### 栈区：

> 1. 局部变量
> 2. const定义的局部变量
> 3. 函数调用和返回时，其入口参数和返回值

* **栈区**由编译器**自动分配释放**，由操作系统自动管理，无须手动管理
* **栈区**上的内容只在函数范围内存在，当函数运行结束，这些内容也会**自动被销毁**
* **栈区**按内存地址**由高到低**方向生长，其最大大小由编译时确定，速度快，但自由性差
* **栈区**是**先进后出**原则，即先进去的被堵在屋里的最里面，后进去的在门口，释放的时候门口的先出去
* ==根据TTA8的链接脚本，TTA8的栈区大小为`0x00002000`(**8KB**)==

### 堆区

>1. 使用malloc函数申请的空间

* **堆区**由程序员分配内存和释放
* **堆区**按内存地址**由低到高**方向生长，其大小由系统内存/虚拟内存上限决定，速度较慢，但自由性大
* ==根据TTA8的链接脚本，TTA8的堆区大小为`0x00002000`(**8KB**)==（和栈区空间一样）

### 全局（静态）区

* 通常是用于那些在编译期间就能确定存储大小的变量的存储区，但它用于的是在整个程序运行期间都可见的全局变量和静态变量

* BSS：

  > 1. 未初始化的全局变量
  > 2. 未初始化的静态变量

  * .bss段不占用可执行文件空间，其内容由操作系统初始化

* DATA：

  > 1. 已初始化的全局变量
  > 2. 已初始化的静态变量

  * .data段占用可执行文件空间，其内容有程序初始化

### 常量区：

> 1. **字符串、数字**等常量
> 2. **const修饰的全局变量**

* 程序运行期间，**常量**区的内容不可以被修改

### 代码区：

* 程序执行代码存放在代码区，其值不能修改（若修改则会出现错误）
* 字符串常量和define定义的常量也有可能存放在代码区



## TTA8 存储架构

<img src="C:\Users\admin\Desktop\MJM_personal_repo\TT_learn\pic\image-20240807131119111.png" alt="image-20240807131119111" style="zoom:50%;" />



## TTStudio的`.MemMap`文件

位于`/src/bsp/drivers/Base_XXX/interface/memmap_inc/模块名_MemMap.h`，其中会出现大量与下面代码块类似的代码：

```c
#ifdef BASE_START_SEC_VAR_INIT_32
    /**
    * @file 模块名_MemMap.h
    * @violates @ref 模块名_MemMap.h_MemMap_h_REF_1 MISRA 2012 Required Rule 19.6, use of '#undef' is discouraged
    */
    #undef BASE_START_SEC_VAR_INIT_32
    #define ENTERED_BASE_START_SEC_VAR_INIT_32
    #ifndef MEMMAP_MATCH_ERROR
       #define MEMMAP_MATCH_ERROR
    #else
        #ifndef BASE_STOP_SEC_VAR_INIT_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /**
    * @file Base_MemMap.h
    * @violates @ref Base_MemMap.h_REF_1 MISRA 2012 Required Rule 19.6, use of '#undef' is discouraged
    */
    #undef MEMMAP_ERROR
    #pragma clang section bss="" data=".mcal_data_init_32.base" rodata="" text=""
#endif
```

核心语句：

	1. `#ifdef BASE_START_SEC_VAR_INIT_32`
 	2. `#pragma clang section bss="" data=".mcal_data_init_32.base" rodata="" text=""`

这个代码块的核心思想就是：**如果在某个.c/.h文件中定义了`BASE_START_SEC_VAR_INIT_32`这个宏，那么这个文件的data段会被==语义划分==到`.mcal_data_init_32.base`段中**

> `语义划分`的意思是，`.mcal_data_init_32.base`此处更像是一个标签，并没有真正的划分到某个物理空间中，这也是`_MemMap.h`中的任务，即，在指定宏被定义时，将定义所在的文件的相应段打上标签或保持原样。而真正进行实际物理存储空间分配的是`.ld链接脚本`



## TTStudio的`.ld`链接脚本

位于`/src/bsp/env/linker_flash_m7.ld`，其中**声明之前语义划分的那些标签，具体应该归属到哪个物理内存空间**：

<img src="C:\Users\admin\Desktop\MJM_personal_repo\Markdwon_casual_repo\pic\image-20240807145052565.png" alt="image-20240807145052565" style="zoom:50%;" />



## TTStudio的`.map`文件

位于`/Debug/{project_name}.map`。在编译项目完成后，链接脚本会生成`.elf`文件，同时也会附带`.map`，`.dis`（反汇编）等文件，其中`.map`文件中的内容**指示了编译后实际的内存分配**：

> 关于.map文件中的LMA和VMA，参考`builder_learn.md`

地址从低到高，大致的排序是：(大致遵循**C语言的内存分区法则**)

> .text段	---	vector_table_m7.o中的`.isr_vector`
>
> ​										|
>
> ​						startup_m7.o中的`.startup`
>
> ​										|
>
> ​						vector_table_m7.o中的`.text`
>
> ​										|
>
> ​							llvm工具链相关代码
>
> ​										|
>
> ​					./src/bsp/nano_stubs/write.o中的各个段
>
> ​										|
>
> ​							**main.o的代码**
>
> ​										|
>
> ​									... ... ...
>
> .ARM段
>
> .tt_table段
>
> .eh_frame段
>
> **.sram_data段**	---	**main函数中初始化的全局变量**
>
> ​														|
>
> ​													... ... ...
>
> .sram_bss段	---	./src/bsp/env/exceptions_m7.o:(.bss.hardfault_sp)
>
> ​																|
>
> ​															... ... ...
>
> ​																|
>
> ​										**main函数中未初始化的全局变量**
>
> ​																|
>
> ​															... ... ...	

