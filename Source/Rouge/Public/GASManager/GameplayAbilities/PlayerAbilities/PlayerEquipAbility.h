// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/EffectActors/EffectActorBase.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "PlayerEquipAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerEquipAbility : public UInputBaseAbility
{
	GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	AEffectActorBase* UPlayerEquipAbility::GetEffectActorFromActiveEffects(
		UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& EffectTag);
};
