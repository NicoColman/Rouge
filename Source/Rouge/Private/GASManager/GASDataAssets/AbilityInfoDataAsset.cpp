// Rouge


#include "GASManager/GASDataAssets/AbilityInfoDataAsset.h"

#include "Rouge/RougeLogChannels.h"

FRougeAbilityInfo UAbilityInfoDataAsset::GetAbilityInfoFromTag(const FGameplayTag& AbilityTag, bool bLogNotFound)
{
	for (const FRougeAbilityInfo& Ability : AbilityInfo)
	{
		if (Ability.AbilityTag == AbilityTag)
		{
			return Ability;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogRouge, Error, TEXT("AbilityInfoDataAsset: Could not find AbilityInfo for Tag: %s, on AbilityInfo: %s"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return FRougeAbilityInfo();
}
