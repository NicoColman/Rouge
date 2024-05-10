// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterPlayer.generated.h"

UCLASS()
class ROUGE_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Begin ICharacterBaseInterface */
	virtual int32 GetCharacterLevel() const override;
	/** End ICharacterBaseInterface */

protected:
	virtual void BeginPlay() override;

	/** Being CharacterBase */
	virtual void InitializeAbilitySystem() override;
	virtual void OnRep_IsBurned() override;
	virtual void OnRep_IsStunned() override;
	virtual void OnRep_IsHealed() override;
	/** End CharacterBase */

	/** Being Basic Character Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCameraComponent> FollowCamera;
	/** End Basic Character Components */
};
