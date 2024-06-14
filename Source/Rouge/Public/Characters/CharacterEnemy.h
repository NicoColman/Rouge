// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "CharacterEnemy.generated.h"

class UBehaviorTree;
class ARougeAIController;

UCLASS()
class ROUGE_API ACharacterEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterEnemy();
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;

	/** Begin ICharacterBaseInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual int32 GetCharacterLevel() const override { return Level; }
	/** End ICharacterBaseInterface */

	void SetLevel(const int32 NewLevel) { Level = NewLevel; }

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<ARougeAIController> AIController;
};
