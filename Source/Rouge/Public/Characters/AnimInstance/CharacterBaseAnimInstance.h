// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UCharacterBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	TObjectPtr<ACharacter> CachedCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

private:
	ACharacter* GetCharacter();
};
