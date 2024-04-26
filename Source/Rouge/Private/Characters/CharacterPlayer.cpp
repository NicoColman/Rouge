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

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

