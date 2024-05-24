// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Interfaces/CharacterInterfaces/CharacterPlayerInterface.h"
#include "CharacterPlayer.generated.h"


class UNiagaraComponent;

UCLASS()
class ROUGE_API ACharacterPlayer : public ACharacterBase, public ICharacterPlayerInterface
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

	/** Begin ICharacterPlayerInterface */
	virtual void AddToXP(const int32 InXP) override;
	virtual void AddToPlayerLevel(const int32 InLevel) override;
	virtual void AddToAttributesPoints(const int32 InPoints) override;
	virtual void AddToSpellPoints(const int32 InPoints) override;
	virtual void LevelUp() override;
	virtual int32 GetXP() const override;
	virtual int32 FindLevelForXP(const int32 InXP) const override;
	virtual int32 GetAttributesPointsRewards(const int32 Level) const override;
	virtual int32 GetSpellPointsRewards(const int32 Level) const override;
	virtual void SetChangeWorldLastLocation(const FGameplayTag& WorldTag, const FVector& Location) override;
	virtual FVector GetChangeWorldLastLocation(const FGameplayTag& WorldTag) const override;
	/** End ICharacterPlayerInterface */

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

private:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpNiagara();

	FVector FirstWorldLocation;
	FVector SecondWorldLocation;
	
public:
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
