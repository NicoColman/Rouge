// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterPlayer.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState/PlayerStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "GASManager/Debuffs/DebuffNiagaraComponent.h"

ACharacterPlayer::ACharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetSprite());
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, -90.f, 0.f));
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetActive(true);
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
	OnASCRegistered.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FRougeGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACharacterPlayer::StunTagChanged);
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

void ACharacterPlayer::OnRep_IsBurned()
{
	if (bIsBurned)
	{
		BurnDebuffComponent->Activate();
	}
	else
	{
		BurnDebuffComponent->Deactivate();
	}
}

void ACharacterPlayer::OnRep_IsStunned()
{
	if (AbilitySystemComponent)
	{
		const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
		FGameplayTagContainer StunTagContainer;
		StunTagContainer.AddTag(GameplayTags.Debuff_Stun);
		StunTagContainer.AddTag(GameplayTags.Player_Block_InputHeld);
		StunTagContainer.AddTag(GameplayTags.Player_Block_InputPressed);
		StunTagContainer.AddTag(GameplayTags.Player_Block_InputReleased);
		if (bIsStunned)
		{
			AbilitySystemComponent->AddLooseGameplayTags(StunTagContainer);
		}
		else
		{
			AbilitySystemComponent->RemoveLooseGameplayTags(StunTagContainer);
		}
	}
}
