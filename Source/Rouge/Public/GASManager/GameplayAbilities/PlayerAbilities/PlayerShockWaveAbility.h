// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/RougeDamageBaseAbility.h"
#include "PlayerShockWaveAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerShockWaveAbility : public URougeDamageBaseAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StunEffectClass;

	void ApplyDamageEffect(AActor* HitActor) const;
	void ApplyStunEffect(AActor* HitActor) const;\
	float GetSphereRadius() const;
};
