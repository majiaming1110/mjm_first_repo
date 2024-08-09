#include "Base_Drv.h"

extern TT_RetType Sent_Recommend_Crc_Calc(uint64 Data, uint64 Nibble, uint64* Recommend_Crc);
extern TT_RetType Sent_Legend_Crc_Calc(uint64 Data, uint64 Nibble, uint64* Legend_Crc);
extern TT_RetType Sent_Alter_Crc_Calc(uint64 Nibble_Num, uint64 FRAME_DATA, uint64 Status, uint64* Alter_Crc);

/*MJM: 在 .h 头文件中声明函数时，通常不需要加上 extern 关键字。\
实际上，extern 是一个可选的修饰符，通常用来表示一个变量或函数的定义在其他地方。\
头文件中的函数声明隐式地被视为 extern，即使你不显式地写出 extern。*/