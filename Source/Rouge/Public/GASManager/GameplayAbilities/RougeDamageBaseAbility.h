// Rouge

#pragma once

#include "CoreMinimal.h"
#include "CoreUtilites/RougeAbilityTypes.h"

#include "GASManager/GameplayAbilities/InputBaseAbility.h"
#include "RougeDamageBaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API URougeDamageBaseAbility : public UInputBaseAbility
{
	GENERATED_BODY()

public:
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr /* TargetASC*/) const; 
	
protected:
	/** The "EditAnywhere" is ONLY used for Abilities with no DataAssets, i.e. ShockWave */
	UPROPERTY(EditAnywhere, Category = "Damage")
	FGameplayTag DamageType;
	UPROPERTY(EditAnywhere, Category = "Damage")
	FScalableFloat Damage;
	// TODO: Make them FScaledFloats
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 20.f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackForceMagnitude = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackChance = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
