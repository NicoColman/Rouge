// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class ROUGE_API ACharacterBase : public APaperZDCharacter, public IAbilitySystemInterface, public ICharacterBaseInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	/** Begin IAbilitySystemInterface */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	/** End IAbilitySystemInterface */

	/** Begin ICharacterBaseInterface */
	virtual int32 GetCharacterLevel() const override;
	virtual void SetPlayerWeapon(class AActor* Weapon) override;
	/** End ICharacterBaseInterface */

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
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;
	virtual void InitializeAbilitySystem();
	virtual void InitializeAttributes();
	virtual void AddCharacterAbilities();
	virtual void ApplyEffectToSelf(TSubclassOf<class UGameplayEffect> const Effect, const int32 Level) const;
	/** End Ability System */
};
