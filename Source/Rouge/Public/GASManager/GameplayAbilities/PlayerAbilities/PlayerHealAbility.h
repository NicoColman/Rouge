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
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> HealEffectClass;
	
private:
	float GetSphereRadius() const;
	TObjectPtr<class USphereComponent> SphereComponent;
	UPROPERTY()
	class ABasicSphereEffectActor* SphereActor;
};
