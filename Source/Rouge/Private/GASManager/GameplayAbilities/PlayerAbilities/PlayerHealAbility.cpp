// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerHealAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "GASManager/EffectActors/BasicSphereEffectActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerHealAbility::UPlayerHealAbility()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
}

void UPlayerHealAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	SphereComponent->SetSphereRadius(GetSphereRadius());
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FVector StartLocation = AvatarActor->GetActorLocation();

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
		const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(HealEffectClass, GetAbilityLevel(), EffectContext);
		SphereActor->SphereComponent->SetSphereRadius(GetSphereRadius());
		SphereActor->EffectSpecToApply = SpecHandle;
		
		SphereActor->FinishSpawning(SpawnTransform);
	}
	if (ACharacter* AvatarCharacter = Cast<ACharacter>(AvatarActor))
	{
		AvatarCharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
}

void UPlayerHealAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	SphereActor->Destroy();
	Cast<ACharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UPlayerHealAbility::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
		EffectContext.AddSourceObject(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(HealEffectClass, GetAbilityLevel(), EffectContext);
		TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}


float UPlayerHealAbility::GetSphereRadius() const
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
