// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCue_EffectBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UGameplayCue_EffectBase : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> EffectParticles;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundCue> EffectSound;
};
