// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterPlayer.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState/PlayerStateBase.h"

ACharacterPlayer::ACharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeAbilitySystem();
	AddCharacterAbilities();
}

void ACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializeAbilitySystem();
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 ACharacterPlayer::GetCharacterLevel() const
{
	const APlayerStateBase* PS = Cast<APlayerStateBase>(GetPlayerState());
	return PS ? PS->GetCharacterLevel() : 1;
}

void ACharacterPlayer::InitializeAbilitySystem()
{
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPlayerState());
	check(GetPlayerState());
	if (AbilitySystemInterface)
	{
		AbilitySystemInterface->GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
		AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	}
	if (AbilitySystemComponent)
	{
		if (IRougeAbilitySystemInterface* AbilitySystemBaseInterface = Cast<IRougeAbilitySystemInterface>(AbilitySystemComponent))
		{
			AbilitySystemBaseInterface->AbilityActorInfoSet();
		}
	}
	/*
	if (IAttributeSetBaseInterface* AttributeSetInterface = Cast<IAttributeSetBaseInterface>(GetPlayerState()))
	{
		AttributeSet = AttributeSetInterface->GetAttributeSet();
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (IHUDOnUpdateInterface* HUDInterface = Cast<IHUDOnUpdateInterface>(PC->GetHUD()))
		{
			HUDInterface->InitOverlay(PC, GetPlayerState(), AbilitySystemComponent, AttributeSet);
		}
	}
	*/
	InitializeAttributes();
}
