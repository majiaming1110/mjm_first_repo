#include "SentHella.h"

/******************************************************************************
*                       Definition
******************************************************************************/
#define SyncMin 	56
#define SyncMax 	56
#define Comm		Random
#define LowPulse	5
#define SentCalc	12

//Fast 6 nibble Recomended
static float32 Hella_Rs[19] = {
	6, 50, 5, 7, 5, 22, 5, 22, 5, 22, 5, 22, 5, 22, 5, 22, 5, 22, 5
};
float32 Hella_Rs_Output[19] = {0};

static TT_RetType Hella_Update(void)
{
	uint64 CombData = 0;
	uint64 RecommendCrc = 0;
	Hella_Rs[1] = 50;
	Hella_Rs[3] = 10;

	if(Hella_Rs[15] != (float32)(SentCalc - LowPulse))
	{
		Hella_Rs[15]--;
	}
	else
	{
		Hella_Rs[15] = SentCalc + 0xF - LowPulse;
		if(Hella_Rs[13] != (float32)(SentCalc - LowPulse))
		{
			Hella_Rs[13]--;
		}
		else
		{
			Hella_Rs[13] = SentCalc + 0xF- LowPulse;
			if(Hella_Rs[11] != (float32)(SentCalc - LowPulse))
			{
				Hella_Rs[11]--;
			}
			else
			{
				Hella_Rs[11] = SentCalc + 0xF - LowPulse;
				if(Hella_Rs[9] != (float32)(SentCalc - LowPulse))
				{
					Hella_Rs[9]--;
				}
				else
				{
					Hella_Rs[9] = SentCalc + 0xF - LowPulse;
					if(Hella_Rs[7] != (float32)(SentCalc - LowPulse))
					{
						Hella_Rs[7]--;
					}
					else
					{
						Hella_Rs[7] = SentCalc + 0xF - LowPulse;
						if(Hella_Rs[5] != (float32)(SentCalc - LowPulse))
						{
							Hella_Rs[5]--;
						}
						else
						{
							Hella_Rs[5] = SentCalc + 0xF - LowPulse;
						}
					}
				}
			}
		}
	}
	for(uint64 i = 0; i < 6; i++)
	{
		CombData |=  ((uint64)Hella_Rs[2 * i + 5] + LowPulse- SentCalc) << ((5 - i) * 4);
	}
	Sent_Recommend_Crc_Calc(CombData, 6ULL, &RecommendCrc);
	Hella_Rs[17] = (float32)RecommendCrc - LowPulse + SentCalc;

	return 0;
}

TT_RetType Hella(void)
{
	if(SyncMin > SyncMax)
	{

	}
	else
	{
		Hella_Update();
		for(uint32 i = 0; i < 20; i++)
		{
			Hella_Rs_Output[i] = Hella_Rs[i] * 3;
		}
	}

	return 0;
}
