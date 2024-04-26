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
	TObjectPtr<USkeletalMesh> CharacterMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	TSubclassOf<UAnimInstance> CharacterAnimInstance;
};
