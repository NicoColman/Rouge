// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "PlayerHealAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerHealAbility : public UInputBaseAbility
{
	GENERATED_BODY()

public:
	UPlayerHealAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void WaitInputReleased(float TimeHeld);
	void EndAbilityAndClearHandle();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> HealEffectClass;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat HealTimer;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat HealAmount;
private:
	float GetSphereRadius() const;
	UPROPERTY()
	class ABasicSphereEffectActor* SphereActor;
	FTimerHandle TimerHandle;
};
