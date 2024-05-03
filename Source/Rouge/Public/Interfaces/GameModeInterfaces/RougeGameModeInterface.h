// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "RougeGameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URougeGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ROUGE_API IRougeGameModeInterface
{
	GENERATED_BODY()

public:
	virtual AActor* GetWeaponFromPool(const FGameplayTag& WeaponTag) = 0;
	virtual void ReturnWeaponToPool(AActor* Weapon) = 0;
	virtual void RequestRespawn(APlayerController* PlayerController) = 0;
};
