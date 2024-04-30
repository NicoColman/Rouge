// Rouge

#pragma once

#include "CoreMinimal.h"
#include "CoreUtilites/RougeWeaponUtilities.h"
#include "UObject/Object.h"
#include "WeaponFactory.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UWeaponFactory : public UObject
{
	GENERATED_BODY()

public:
	static AActor* CreateWeapon(EWeaponTypes WeaponType ,UObject* WorldContextObject, UPrimaryDataAsset* WeaponDataAsset);

private:
	static class AWeaponBase* CreateWeaponBase(UObject* WorldContextObject, UPrimaryDataAsset* WeaponDataAsset);
};
