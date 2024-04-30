// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponBaseDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UWeaponBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Base")
	TSoftObjectPtr<class UPaperFlipbook> WeaponFlipbook;
};
