// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterEnemy.generated.h"

UCLASS()
class ROUGE_API ACharacterEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterEnemy();
	virtual void Tick(float DeltaTime) override;

	/** Begin ICharacterBaseInterface */
	virtual int32 GetCharacterLevel() const override { return Level; }
	/** End ICharacterBaseInterface */

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;

};
