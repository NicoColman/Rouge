// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance/CharacterBaseAnimInstance.h"
#include "GameFramework/Character.h"

void UCharacterBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
}

void UCharacterBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!GetCharacter()) return;

	MovementSpeed = CachedCharacter->GetVelocity().Length();
}

ACharacter* UCharacterBaseAnimInstance::GetCharacter()
{
	if (CachedCharacter) return CachedCharacter;
	return CachedCharacter = Cast<ACharacter>(TryGetPawnOwner());
}
