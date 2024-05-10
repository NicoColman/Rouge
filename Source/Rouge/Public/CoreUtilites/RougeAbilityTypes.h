#pragma once


#include "GameplayEffectTypes.h"
#include "RougeAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<class UGameplayEffect> DamageEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	float BaseDamage = 0.f;
	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag::EmptyTag;

	UPROPERTY()
	float DebuffChance = 0.f;
	UPROPERTY()
	float DebuffDuration = 0.f;
	UPROPERTY()
	float DebuffDamage = 0.f;
	UPROPERTY()
	float DebuffFrequency = 0.f;

	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;
	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY()
	float KnockbackForceMagnitude = 0.f;
	UPROPERTY()
	float KnockbackChance = 0.f;
	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FRougeGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(const bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsSuccessfulDebuff(const bool bInIsSuccessfulDebuff) { bIsSuccessfulDebuff = bInIsSuccessfulDebuff; }
	void SetDebuffDamage(const float InDebuffDamage) { DebuffDamage = InDebuffDamage; }
	void SetDebuffDuration(const float InDebuffDuration) { DebuffDuration = InDebuffDuration; }
	void SetDebuffFrequency(const float InDebuffFrequency) { DebuffFrequency = InDebuffFrequency; }
	void SetDamageType(const TSharedPtr<FGameplayTag>& InDamageType) { DamageType = InDamageType; }
	void SetDeathImpulse(const FVector& InDeathImpulse) { DeathImpulse = InDeathImpulse; }
	void SetKnockbackForce(const FVector& InKnockbackForce) { KnockbackForce = InKnockbackForce; }
	
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FRougeGameplayEffectContext* Duplicate() const
	{
		FRougeGameplayEffectContext* NewContext = new FRougeGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
	FVector DeathImpulse = FVector::ZeroVector;

	UPROPERTY()
	FVector KnockbackForce = FVector::ZeroVector;

public:
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsSuccessfulDebuff() const { return bIsSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }
	FVector GetDeathImpulse() const { return DeathImpulse; }
	FVector GetKnockbackForce() const { return KnockbackForce; }
};

template<>
struct TStructOpsTypeTraits<FRougeGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FRougeGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};