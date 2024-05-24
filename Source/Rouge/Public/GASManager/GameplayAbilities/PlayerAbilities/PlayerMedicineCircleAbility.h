// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "PlayerMedicineCircleAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPlayerMedicineCircleAbility : public UInputBaseAbility
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void WaitInputReleased(float TimeHeld);
	void EndAbilityAndClearHandle();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> CircleEffectClass;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat CircleTimer;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat CircleAmount;
private:
	float GetSphereRadius() const;
	UPROPERTY()
	class ABasicSphereEffectActor* SphereActor;
	FTimerHandle TimerHandle;
};
