// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfoDataAsset.generated.h"

USTRUCT()
struct FRougeLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityPointAward = 1;
};

/**
 * 
 */
UCLASS()
class ROUGE_API ULevelUpInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "LevelUpInfo")
	TArray<FRougeLevelUpInfo> LevelUpInfo;

	int32 FindLevelForXP(int32 XP) const;
};
