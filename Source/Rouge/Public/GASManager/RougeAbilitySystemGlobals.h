// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "RougeAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
