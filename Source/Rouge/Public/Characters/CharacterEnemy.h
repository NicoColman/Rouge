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

protected:
	virtual void BeginPlay() override;
};
