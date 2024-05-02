// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCue_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UGameplayCue_Pickup : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UNiagaraSystem> PickupParticles;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USoundCue> PickupSound;
};
