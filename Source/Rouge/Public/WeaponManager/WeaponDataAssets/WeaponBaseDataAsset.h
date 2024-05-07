// Rouge

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "WeaponBaseDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UWeaponBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag WeaponTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Base")
	TSoftObjectPtr<class UPaperFlipbook> WeaponFlipbook;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Damage")
	TSoftClassPtr<class AFireBallProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Damage")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;
	
	UPROPERTY()
	TObjectPtr<class UPaperFlipbookComponent> WeaponFlipbookComponent;
	
	UPROPERTY()
	TObjectPtr<AActor> WeaponActor;
};
