// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class ROUGE_API ACharacterBase : public APaperZDCharacter, public IAbilitySystemInterface, public ICharacterBaseInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Begin IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	/** End IAbilitySystemInterface */

	/** Begin ICharacterBaseInterface */
	virtual FVector2D GetDirectionality() const override {return Directionality;}
	virtual int32 GetCharacterLevel() const override;
	virtual void SetPlayerWeapon(class AActor* Weapon) override;
	virtual UCharacterBaseDataAsset* GetCharacterDataAsset() const override {return CharacterDataAsset;}
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override {return OnASCRegistered;}
	virtual FOnDeath& GetOnDeathDelegate() override {return OnDeath;}
	/** End ICharacterBaseInterface */

	FOnASCRegistered OnASCRegistered;
	FOnDeath OnDeath;

	UPROPERTY(ReplicatedUsing=OnRep_IsBurned, BlueprintReadOnly)
	bool bIsBurned;
	UPROPERTY(ReplicatedUsing=OnRep_IsStunned, BlueprintReadOnly)
	bool bIsStunned;
	UPROPERTY(ReplicatedUsing=OnRep_IsHealed, BlueprintReadOnly)
	bool bIsHealed;

	virtual void BurnTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void HealTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	/** Called on RougePlayerController and used for animations */
	UFUNCTION(Server, Reliable)
	void SetDirectionality(const FVector2D Direction);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float OldWalkSpeed;

	UPROPERTY(Replicated)
	FVector2D Directionality;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	TObjectPtr<class UCharacterBaseDataAsset> CharacterDataAsset;

	virtual void Death();
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastOnDeath();
	UFUNCTION()
	virtual void OnRep_IsBurned();
	UFUNCTION()
	virtual void OnRep_IsStunned();
	UFUNCTION()
	virtual void OnRep_IsHealed();

	/** Begin Ability System */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;
	virtual void InitializeAbilitySystem();
	virtual void InitializeAttributes();
	virtual void AddCharacterAbilities();
	virtual void ApplyEffectToSelf(TSubclassOf<class UGameplayEffect> const Effect, const int32 Level) const;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAttachedNiagaraComponent> BurnComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttachedNiagaraComponent> StunComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttachedNiagaraComponent> HealComponent;
	/** End Ability System */

public:
	/** Getters */

};
