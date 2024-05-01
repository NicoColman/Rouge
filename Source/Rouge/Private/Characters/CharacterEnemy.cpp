// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterEnemy.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

ACharacterEnemy::ACharacterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));

	Level = 1;
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}
