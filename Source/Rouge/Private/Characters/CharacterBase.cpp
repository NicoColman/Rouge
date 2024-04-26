// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterBase.h"
#include "Rouge/Public/DataAssets/CharacterDataAssets/CharacterBaseDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, -90.0f));
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}