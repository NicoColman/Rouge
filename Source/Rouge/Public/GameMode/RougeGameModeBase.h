// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameModeInterfaces/RougeGameModeInterface.h"
#include "RougeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API ARougeGameModeBase : public AGameModeBase, public IRougeGameModeInterface
{
	GENERATED_BODY()

public:
	ARougeGameModeBase();

	/** Begin IRougeGameModeInterface */
	virtual AActor* GetWeaponFromPool(const FGameplayTag& WeaponTag) override;
	virtual void ReturnWeaponToPool(AActor* Weapon) override;
	/** End IRougeGameModeInterface */

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UWeaponPoolObject* WeaponPoolObject;
};
