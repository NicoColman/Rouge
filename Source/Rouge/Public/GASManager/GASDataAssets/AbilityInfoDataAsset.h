// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AbilityInfoDataAsset.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FRougeAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UTexture2D> AbilityIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UPaperSprite> BackgroundMaterial = nullptr;
};

/**
 * 
 */
UCLASS()
class ROUGE_API UAbilityInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInfo")
	TArray<FRougeAbilityInfo> AbilityInfo;

	FRougeAbilityInfo GetAbilityInfoFromTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false);
};
