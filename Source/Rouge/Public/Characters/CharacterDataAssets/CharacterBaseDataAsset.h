// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "CoreUtilites/RougeAbilityUtilities.h"
#include "Engine/DataAsset.h"
#include "CharacterBaseDataAsset.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	None UMETA(DisplayName = "None"),
	Player UMETA(DisplayName = "Player"),
	Melee UMETA(DisplayName = "Melee"),
	Range UMETA(DisplayName = "Range")
};

UENUM(BlueprintType)
enum class EAttachedNiagaraSystems : uint8
{
	None UMETA(DisplayName = "None"),
	Burned UMETA(DisplayName = "Burned"),
	Stunned UMETA(DisplayName = "Stunned"),
	Healed UMETA(DisplayName = "Healed")
};

/**
 * 
 */
UCLASS()
class ROUGE_API UCharacterBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UPaperFlipbook> CharacterFlipbook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	TSubclassOf<class UPaperZDAnimInstance> CharacterAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	ECharacterClass CharacterClass = ECharacterClass::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NiagaraSystems")
	TMap<EAttachedNiagaraSystems, FAbilityCuesBase> AttachedNiagaraSystems;

	/** Gas */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> PassiveStartupAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> PrimaryAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> SecondaryAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> VitalAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UCurveTable> DamageCalculationsCoefficients;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP")
	FScalableFloat XPReward = FScalableFloat();
	
};
