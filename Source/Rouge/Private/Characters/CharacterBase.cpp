// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterBase.h"
#include "Rouge/Public/Characters/CharacterDataAssets/CharacterBaseDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperZDAnimationComponent.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

void ACharacterBase::AddCharacterAbilities()
{
}
