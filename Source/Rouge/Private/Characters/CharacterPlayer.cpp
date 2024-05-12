// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterPlayer.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState/PlayerStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreUtilites/CoreComponents/AttachedNiagaraComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "UIManager/HUD/RougeHUD.h"

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
	APlayerStateBase* PS = Cast<APlayerStateBase>(GetPlayerState());
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(PS);
	check(PS);
	if (AbilitySystemInterface)
	{
		AbilitySystemInterface->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
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
	AbilitySystemComponent->RegisterGameplayTagEvent(FRougeGameplayTags::Get().Debuff_Burn, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACharacterPlayer::BurnTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FRougeGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACharacterPlayer::StunTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FRougeGameplayTags::Get().Buff_Heal, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACharacterPlayer::HealTagChanged);
	AttributeSet = PS->GetAttributeSet();
	InitializeAttributes();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ARougeHUD* HUD = Cast<ARougeHUD>(PC->GetHUD()))
		{
			HUD->InitOverlay(PC, PS, AbilitySystemComponent, AttributeSet);
		}
	}
	
}

void ACharacterPlayer::OnRep_IsBurned()
{
	BurnComponent->ActivateComponents(bIsHealed);
}

void ACharacterPlayer::OnRep_IsStunned()
{
	// Here we don't use "StunComponent->ActivateComponents(bIsStunned);" because we are already replicating the FGameplayTags
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

void ACharacterPlayer::OnRep_IsHealed()
{
	HealComponent->ActivateComponents(bIsHealed);
}
