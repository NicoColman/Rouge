// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterPlayer.h"

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
}

void ACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

