// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "PlayerChangeWorldAbility.generated.h"


/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerChangeWorldAbility : public UInputBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CurrentWorld;

	UPROPERTY(EditDefaultsOnly)
	FVector WorldStartSecondPosition;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> SlowEnemiesEffect;

private:
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle ,AActor*> HitActors; 
};
