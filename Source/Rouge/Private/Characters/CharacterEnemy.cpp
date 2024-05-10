// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterEnemy.h"
#include "AbilitySystemComponent.h"
#include "GASManager/AbilitySystem/ASCBase.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"

ACharacterEnemy::ACharacterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UASCBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));

	Level = 1;
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UASCBase>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeAttributes();
	}
	AddCharacterAbilities();
}

//OnASCRegistered.BroadCast(AbilitySystemComponent);