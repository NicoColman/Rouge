// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class ROUGE_API ACharacterBase : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	/** Begin IAbilitySystemInterface */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	/** End IAbilitySystemInterface */

protected:
	virtual void BeginPlay() override;

	/** Being Basic Character Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCameraComponent> FollowCamera;
	/** End Basic Character Components */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<class UCharacterBaseDataAsset> CharacterDataAsset;

	/** Begin Ability System */
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;
	virtual void InitializeAbilitySystem();
	virtual void AddCharacterAbilities();
	/** End Ability System */
};
