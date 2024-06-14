// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/RougeDamageBaseAbility.h"
#include "AIMeleeDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UAIMeleeDamageAbility : public URougeDamageBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	void GetActorsInRangeAndApplyDamage() const;
};
