// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "RougeDamageBaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeDamageBaseAbility : public UInputBaseAbility
{
	GENERATED_BODY()

protected:
	/** The "EditAnywhere" is ONLY used for Abilities with no DataAssets, i.e. ShockWave */
	UPROPERTY(EditAnywhere, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	FGameplayEffectSpecHandle AssignDamageTypes(const UAbilitySystemComponent* ASC, const FGameplayEffectContextHandle& ContextHandle) const;
};
