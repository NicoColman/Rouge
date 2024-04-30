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

	/** Gas */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> VitalAttributeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DamageAttributeEffect;
};
