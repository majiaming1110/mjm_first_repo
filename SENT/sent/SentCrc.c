#include "SentCrc.h"

static uint64 Crc4Poly = 0x1D;
static uint64 polyBitLength = 5;
static uint64 Seed = 0x5;

//static uint64 BitLength(uint64 Data, uint64* Length)
//{
//    // pow of 2, 2^0 - 2 ^31
//	uint64 powof16[9] =
//	{
//			0x0,
//			0x10,
//			0x100,
//			0x1000,
//			0x10000,
//			0x100000,
//			0x1000000,
//			0x10000000,
//			0x100000000,
//
//	};
//
//	uint64 left = 0 ;
//	uint64 right = 8 ;
//	uint64 mid = 0;
//
//    while (left <= right)
//    {
//    	mid = (left + right) / 2 ;
//
//        if (powof16[mid] <= Data)
//        {
//            if (powof16[mid + 1] > Data)
//            {
//            	*Length =  mid + 1; // got it!
//            	break;
//            }
//            else
//            {
//                left = mid + 1 ;// powof2[mid] < n, search right part
//            }
//        }
//        else
//        {
//        	right = mid - 1 ;// powof2[mid] > n, search left part
//        }
//    }
//
//    // not found
//    return TT_RET_SUCCESS ;
//}

/* 传统CRC计算不需要末尾加入4位0进行计算 */
TT_RetType Sent_Legend_Crc_Calc(uint64 Data, uint64 Nibble, uint64* Legend_Crc)
{
    TT_RetType Ret = TT_RET_SUCCESS ;
    uint64 CombData = 0;
    uint64 bitcount = 0;
    uint64 crc_reg = 0;
    uint64 res_reg = 0;

    if((Data < 0) || (Data > 0xFFFFFFFF))
    {
    	Ret = TT_RET_PARAM_ERR;
    }
    else
    {
    	/* 确认计算数据的长度，带种子进行计算 */
    	bitcount = 4 + Nibble * 4;
    	CombData = Data | (Seed << (Nibble * 4));
    	/* crc计算 */
    	crc_reg = CombData;
    	res_reg = CombData;
    	while(1)
    	{
    		if(bitcount < polyBitLength)
    		{
    			break;
    		}
    		else
    		{
    			/* 移位需要计算的部分，准备与多项式进行异或操作 */
    			crc_reg = (crc_reg >> (bitcount - polyBitLength));
    			/* 保留不需要计算的部分，其他置0 */
    			res_reg = ((1ULL << (bitcount - polyBitLength)) - 1) & res_reg;
    			/* 如果此步骤的计算部分首位不为0，进行异或，否则跳过, 添加ULL防止1在左移超过31位的情况下出现异常 */
    			if(((crc_reg >> (polyBitLength - 1)) & 0x1) != 0)
    			{
    				crc_reg ^= Crc4Poly;
    			}
    			else
    			{

    			}
    			/* 重新组合 */
    			crc_reg = (crc_reg << (bitcount - polyBitLength));
    			crc_reg = crc_reg | res_reg;
    			res_reg = crc_reg;
    		}
    		bitcount--;
    	}

    	*Legend_Crc = crc_reg;
    }

	return Ret;
}

/* 推荐CRC计算需要末尾加入4位0进行计算 */
TT_RetType Sent_Recommend_Crc_Calc(uint64 Data, uint64 Nibble, uint64* Recommend_Crc)
{
    TT_RetType Ret = TT_RET_SUCCESS ;
    uint64 CombData = 0;
    uint64 bitcount = 0;
    uint64 crc_reg = 0;
    uint64 res_reg = 0;

    if((Data < 0) || (Data > 0xFFFFFFFF))
    {
    	Ret = TT_RET_PARAM_ERR;
    }
    else
    {
    	/* 确认计算数据的长度，带种子并且在末尾加入四位0进行计算 */
    	bitcount = 4 + Nibble * 4 + 4;
    	CombData = (Data << 4) | (Seed << ((1 + Nibble) * 4));
    	/* crc计算 */
    	crc_reg = CombData;
    	res_reg = CombData;
    	while(1)
    	{
    		if(bitcount < polyBitLength)
    		{
    			break;
    		}
    		else
    		{
    			/* 移位需要计算的部分，准备与多项式进行异或操作 */
    			crc_reg = (crc_reg >> (bitcount - polyBitLength));
    			/* 保留不需要计算的部分，其他置0, 添加ULL防止1在左移超过31位的情况下出现异常 */
    			res_reg = ((1ULL << (bitcount - polyBitLength)) - 1) & res_reg;
    			/* 如果此步骤的计算部分首位不为0，进行异或，否则跳过 */
    			if(((crc_reg >> (polyBitLength - 1)) & 0x1) != 0)
    			{
    				crc_reg ^= Crc4Poly;
    			}
    			else
    			{

    			}
    			/* 重新组合 */
    			crc_reg = (crc_reg << (bitcount - polyBitLength));
    			crc_reg = crc_reg | res_reg;
    			res_reg = crc_reg;
    		}
    		bitcount--;
    	}

    	*Recommend_Crc = crc_reg;
    }

	return Ret;
}

/*Alter CRC：默认带状态位的CRC计算！！！*/
TT_RetType Sent_Alter_Crc_Calc(uint64 Nibble_Num, uint64 FRAME_DATA, uint64 Status, uint64* Alter_Crc)
{
	TT_RetType Ret = TT_RET_SUCCESS ;
    uint64 DATA[Nibble_Num + 1];
    uint64 tmp;
    uint64 MSB_Mask = 0x10;
    uint64 SEED = 0x5; //0b0101
    uint64 POLY = 0x1D; //0b11101

    /*将状态段加到数据段最前*/
    DATA[0] = Status;
    for (uint32 i = 1; i < (Nibble_Num + 1); i++)
    {
        tmp = (uint64)(FRAME_DATA << ((i - 1) * 4)) >> (((8 - i) * 4) + ((i - 1) * 4));
        DATA[i] = tmp;
    }

    for (uint32 i = 0; i < (Nibble_Num + 1); i++)
    {
        tmp = DATA[i];
        tmp ^= SEED;
        for (uint32 j = 0; j < 4; j++)
        {
            tmp <<= 1;
            if (tmp & MSB_Mask)
            {
                tmp ^= POLY;
            }
        }  
        SEED = tmp;
    }
    
	tmp &= 0xF;
    *Alter_Crc = tmp;
	
	return Ret;
}
