// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCueActor_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API AGameplayCueActor_Pickup : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UNiagaraSystem> PickupParticles;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USoundCue> PickupSound;

private:
	TObjectPtr<class UNiagaraComponent> SpawnedParticles;
	TObjectPtr<class UAudioComponent> SpawnedSound;
};
