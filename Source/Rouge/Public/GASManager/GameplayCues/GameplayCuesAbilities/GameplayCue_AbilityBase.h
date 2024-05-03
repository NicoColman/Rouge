// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "CoreUtilites/RougeWeaponUtilities.h"
#include "GameplayCue_AbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UGameplayCue_AbilityBase : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FAbilityBaseCues> AbilityEffects;
};
