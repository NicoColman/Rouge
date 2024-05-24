// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerMedicineCircleAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "GASManager/EffectActors/BasicSphereEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerMedicineCircleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	UAbilityTask_WaitInputRelease* WaitInputRelease = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	WaitInputRelease->OnRelease.AddDynamic(this, &UPlayerMedicineCircleAbility::WaitInputReleased);
	WaitInputRelease->ReadyForActivation();

	const float Timer = CircleTimer.GetValueAtLevel(GetAbilityLevel());
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerMedicineCircleAbility::EndAbilityAndClearHandle, Timer, false);
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(AvatarActor->GetActorLocation());
	SphereActor = GetWorld()->SpawnActorDeferred<ABasicSphereEffectActor>(
		ABasicSphereEffectActor::StaticClass(),
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
	if (SphereActor)
	{
		FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
		EffectContext.AddSourceObject(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(CircleEffectClass, GetAbilityLevel(), EffectContext);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FRougeGameplayTags::Get().SetByCaller_Ability_HealAmount, CircleAmount.GetValueAtLevel(GetAbilityLevel()));
		SphereActor->SphereComponent->SetSphereRadius(GetSphereRadius());
		SphereActor->EffectSpecToApply = SpecHandle;
		
		SphereActor->FinishSpawning(SpawnTransform);
	}
	if (const ACharacter* AvatarCharacter = Cast<ACharacter>(AvatarActor))
	{
		AvatarCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
}

void UPlayerMedicineCircleAbility::WaitInputReleased(float TimeHeld)
{
	EndAbilityAndClearHandle();
}

void UPlayerMedicineCircleAbility::EndAbilityAndClearHandle()
{
	TimerHandle.Invalidate();
	ApplyCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo());
	SphereActor->Destroy();
	Cast<ACharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

float UPlayerMedicineCircleAbility::GetSphereRadius() const
{
	switch (GetAbilityLevel())
	{
	case 1:
		return 250.f;
	case 2:
		return 300.f;
	case 3:
		return 350.f;
	case 4:
		return 400.f;
	case 5:
		return 450.f;
	case 6:
		return 500.f;
	default:
		return 250.f;
	}
}
