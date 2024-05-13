// Rouge

#pragma once

#include "CoreMinimal.h"
#include "RougeAbilityUtilities.generated.h"

USTRUCT(BlueprintType)
struct FAbilityCuesBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Cue")
	TObjectPtr<class USoundBase> AbilitySound;
	UPROPERTY(EditDefaultsOnly, Category = "Cue")
	TObjectPtr<class UNiagaraSystem> AbilityParticles;
};
