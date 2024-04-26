// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class ROUGE_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCameraComponent> FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<class UCharacterBaseDataAsset> CharacterDataAsset;
};
