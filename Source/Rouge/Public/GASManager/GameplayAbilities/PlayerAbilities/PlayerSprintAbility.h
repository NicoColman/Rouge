// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "PlayerSprintAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerSprintAbility : public UInputBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayEffect> SpeedBoostEffectClass;
private:
	UPROPERTY()
	FActiveGameplayEffectHandle ActiveEffectHandle;
};
