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

protected:
	virtual void BeginPlay() override;
	
};
