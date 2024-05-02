// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterBase.h"

#include "GameplayEffectTypes.h"
#include "Rouge/Public/Characters/CharacterDataAssets/CharacterBaseDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetSprite()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetSprite()->SetRelativeLocation(FVector(0.f, 0.0f, -39.5f));
	GetSprite()->SetRelativeRotation(FRotator(0.f, -270.f, 0.f));
	GetSprite()->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetSprite());
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, -90.f, 0.f));
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->SetActive(true);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterDataAsset) return;
	GetSprite()->SetFlipbook(CharacterDataAsset->CharacterFlipbook);
	GetAnimationComponent()->SetAnimInstanceClass(CharacterDataAsset->CharacterAnimInstance);
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
	if (AbilitySystemComponent)
	{
		CastChecked<IRougeAbilitySystemInterface>(AbilitySystemComponent)->AddCharacterAbilities(CharacterDataAsset->StartupAbilities);
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

int32 ACharacterBase::GetCharacterLevel() const
{
	return 1;
}

void ACharacterBase::SetPlayerWeapon(AActor* Weapon)
{
}
