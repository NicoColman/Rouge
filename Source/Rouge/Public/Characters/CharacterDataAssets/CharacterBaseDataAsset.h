// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterBaseDataAsset.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NiagaraSystems")
	TObjectPtr<class UNiagaraSystem> BurnSystem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NiagaraSystems")
	TObjectPtr<class UNiagaraSystem> StunSystem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NiagaraSystems")
	TObjectPtr<class UNiagaraSystem> HealSystem;

	/** Gas */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> PrimaryAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> SecondaryAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> VitalAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UCurveTable> DamageCalculationsCoefficients;
};
