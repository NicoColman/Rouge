// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "WeaponPoolObject.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UWeaponPoolObject : public UObject
{
	GENERATED_BODY()

public:
	UWeaponPoolObject();

	void WeaponPoolManager(UObject* WorldContextObject);
	AActor* GetWeaponFromPool(const FGameplayTag& WeaponTag);
	void ReturnWeaponToPool(AActor* Weapon);

private:
	UPROPERTY()
	TObjectPtr<class UWeaponPoolingDataAsset> WeaponPoolingDataAsset;
	
	UPROPERTY()
	TMap<FGameplayTag, AActor*> WeaponPool;
	
	void SetActive(AActor* Weapon, bool bActive);
};
