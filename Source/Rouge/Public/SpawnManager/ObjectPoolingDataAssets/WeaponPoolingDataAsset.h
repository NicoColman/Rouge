// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CoreUtilites/RougeWeaponUtilities.h"
#include "Engine/DataAsset.h"
#include "WeaponPoolingDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWeaponPoolingData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimaryDataAsset* WeaponDataAsset;
};

/**
 * 
 */
UCLASS()
class ROUGE_API UWeaponPoolingDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FWeaponPoolingData> WeaponPool;
};
