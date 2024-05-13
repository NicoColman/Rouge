// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterBase.h"

#include "GameplayEffectTypes.h"
#include "Rouge/Public/Characters/CharacterDataAssets/CharacterBaseDataAsset.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreUtilites/CoreComponents/AttachedNiagaraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "Net/UnrealNetwork.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	GetSprite()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	GetSprite()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetSprite()->SetRelativeLocation(FVector(0.f, 0.0f, -39.5f));
	GetSprite()->SetRelativeRotation(FRotator(0.f, -270.f, 0.f));
	GetSprite()->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	GetSprite()->SetGenerateOverlapEvents(true);

	BurnComponent = CreateDefaultSubobject<UAttachedNiagaraComponent>(TEXT("BurnComponent"));
	BurnComponent->SetupAttachment(GetSprite());
	BurnComponent->ComponentTag = FRougeGameplayTags::Get().Debuff_Burn;

	StunComponent = CreateDefaultSubobject<UAttachedNiagaraComponent>(TEXT("StunComponent"));
	StunComponent->SetupAttachment(GetSprite());
	StunComponent->ComponentTag = FRougeGameplayTags::Get().Debuff_Stun;

	HealComponent = CreateDefaultSubobject<UAttachedNiagaraComponent>(TEXT("HealComponent"));
	HealComponent->SetupAttachment(GetSprite());
	HealComponent->ComponentTag = FRougeGameplayTags::Get().Buff_Heal;

	bIsBurned = false;
	bIsStunned = false;
	bIsHealed = false;
}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterBase, bIsBurned);
	DOREPLIFETIME(ACharacterBase, bIsStunned);
	DOREPLIFETIME(ACharacterBase, bIsHealed);
	DOREPLIFETIME(ACharacterBase, Directionality);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterDataAsset) return;
	GetSprite()->SetFlipbook(CharacterDataAsset->CharacterFlipbook);
	GetAnimationComponent()->SetAnimInstanceClass(CharacterDataAsset->CharacterAnimInstance);
	
	BurnComponent->SetNiagaraAssets(CharacterDataAsset->AttachedNiagaraSystems[EAttachedNiagaraSystems::Burned]);
	StunComponent->SetNiagaraAssets(CharacterDataAsset->AttachedNiagaraSystems[EAttachedNiagaraSystems::Stunned]);
	HealComponent->SetNiagaraAssets(CharacterDataAsset->AttachedNiagaraSystems[EAttachedNiagaraSystems::Healed]);
	
}

void ACharacterBase::SetDirectionality_Implementation(const FVector2D Direction)
{
	Directionality = FVector2D(Direction.Y, Direction.X);
}

void ACharacterBase::InitializeAbilitySystem()
{
}

void ACharacterBase::InitializeAttributes()
{
	ApplyEffectToSelf(CharacterDataAsset->PrimaryAttributeEffect, 1);
	ApplyEffectToSelf(CharacterDataAsset->SecondaryAttributeEffect, 1);
	ApplyEffectToSelf(CharacterDataAsset->VitalAttributeEffect, 1);
}

void ACharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	if (IRougeAbilitySystemInterface* AbilitySystemInterface = Cast<IRougeAbilitySystemInterface>(AbilitySystemComponent))
	{
		AbilitySystemInterface->AddCharacterAbilities(CharacterDataAsset->StartupAbilities);
		AbilitySystemInterface->AddPassiveCharacterAbilities(CharacterDataAsset->PassiveStartupAbilities);
	}
}

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> const Effect, const int32 Level) const
{
	check(AbilitySystemComponent);
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, Level, EffectContext);
	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
	}
}

void ACharacterBase::Death()
{
	MulticastOnDeath();
}

void ACharacterBase::MulticastOnDeath_Implementation()
{
	OnDeath.Broadcast(this);
}

int32 ACharacterBase::GetCharacterLevel() const
{
	return 1;
}

void ACharacterBase::SetPlayerWeapon(AActor* Weapon)
{
}

void ACharacterBase::BurnTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsBurned = NewCount > 0;
}

void ACharacterBase::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	if (GetCharacterMovement()->MaxWalkSpeed > 0.f)
	{
		OldWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	}
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : OldWalkSpeed;
}

void ACharacterBase::HealTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsHealed = NewCount > 0;
}

void ACharacterBase::OnRep_IsBurned()
{
}

void ACharacterBase::OnRep_IsStunned()
{
}

void ACharacterBase::OnRep_IsHealed()
{
}

