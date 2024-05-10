// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "RougeAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RougeLibrary.generated.h"

UENUM(BlueprintType)
enum class EFlipbookRotation : uint8
{
	EFR_None UMETA(DisplayName = "None"),
	EFR_North UMETA(DisplayName = "North"),
	EFR_South UMETA(DisplayName = "South"),
	EFR_East UMETA(DisplayName = "East"),
	EFR_West UMETA(DisplayName = "West"),
};

/**
 * 
 */
UCLASS()
class ROUGE_API URougeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	URougeLibrary();

	static UObject* GetPrimaryObjectFromTag(const FGameplayTag& Tag, const ANSICHAR* InName);

	static FRotator GetFlipbookRotation(EFlipbookRotation FlipbookRotation);
	
	static class UCharacterBaseDataAsset* GetCharacterBaseDataAsset(AActor* Actor);

	/** Begin RougeAbilityTypes Functions */
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContext);
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContext);
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContext);
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContext);
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContext);
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContext);
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContext);
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContext);
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContext);

	// If exposed to BP add "UPARAM(ref) FGameplayEffectContextHandle& EffectContext" instead of "FGameplayEffectContextHandle& EffectContext"
	static void SetBlockedHit(FGameplayEffectContextHandle& EffectContext, bool bBlockedHit);
	static void SetCriticalHit(FGameplayEffectContextHandle& EffectContext, bool bCriticalHit);
	static void SetSuccessfulDebuff(FGameplayEffectContextHandle& EffectContext, bool bSuccessfulDebuff);
	static void SetDebuffDamage(FGameplayEffectContextHandle& EffectContext, float DebuffDamage);
	static void SetDebuffDuration(FGameplayEffectContextHandle& EffectContext, float DebuffDuration);
	static void SetDebuffFrequency(FGameplayEffectContextHandle& EffectContext, float DebuffFrequency);
	static void SetDamageType(FGameplayEffectContextHandle& EffectContext, const FGameplayTag& DamageType);
	static void SetDeathImpulse(FGameplayEffectContextHandle& EffectContext, FVector DeathImpulse);
	static void SetKnockbackForce(FGameplayEffectContextHandle& EffectContext, FVector KnockbackForce);
	/** End RougeAbilityTypes Functions */
	
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	
private:
	static FPrimaryAssetId GetPrimaryAssetIdFromTag(const FGameplayTag& Tag, const ANSICHAR* InName);
};


