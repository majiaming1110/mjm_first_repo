## 学习地址
* gcc： `gcc.gnu.org`
* ld：`ftp.gnu.org`
* llvm：`lld.llvm.org`



## 疑问&思考

* llvm是和gcc完全平行的概念，这二者属于不同的编译器
* 对于一般的非RTOS/非操作系统，代码中出现类似`__attribute__ ((section (".XXX")))`的作用是将紧跟的一个函数划分到XXX段，但这句话只是做一个语义识别，只有在`ld`(gcc)/`lld`(llvm)指令执行时，根据ld语法的定义，才会真正将XXX段来划分到实际的存储空间，比如flash/itcm等，`ld`的作用就是将输入的`.o`文件输出成`.elf`文件
* `.o`和`.elf`文件?
* `llvm`中的编译选项`-ffunction_section`？



# 学习总结

* 
* 

