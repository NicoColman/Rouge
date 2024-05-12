// Rouge


#include "GASManager/GASDataAssets/LevelUpInfoDataAsset.h"

int32 ULevelUpInfoDataAsset::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInfo[1] = Level 1 Information
		// LevelUpInfo[2] = Level 1 Information
		if (LevelUpInfo.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInfo[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
