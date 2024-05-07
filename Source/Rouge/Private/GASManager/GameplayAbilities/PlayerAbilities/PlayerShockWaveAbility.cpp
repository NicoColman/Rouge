// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerShockWaveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"


void UPlayerShockWaveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	
	TArray<FHitResult> HitResults;
	GetWorld()->SweepMultiByProfile(
		HitResults,
		StartLocation,
		StartLocation + FVector(0, 0, -1000),
		FQuat::Identity,
		FName(),	
		FCollisionShape::MakeSphere(GetSphereRadius()),
		FCollisionQueryParams()
		);

	FGameplayCueParameters CueParameters;
	CueParameters.AggregatedSourceTags.AddTag(FRougeGameplayTags::Get().Ability_Shockwave);
	GetAbilitySystemComponentFromActorInfo()->ExecuteGameplayCue(FRougeGameplayTags::Get().GameplayCue_Ability_Base, CueParameters);
	for (FHitResult HitResult : HitResults)
	{
		if (HitResult.GetActor() == GetAvatarActorFromActorInfo()) continue;
		ApplyDamageEffect(HitResult.GetActor());
		ApplyStunEffect(HitResult.GetActor());
	}
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UPlayerShockWaveAbility::ApplyDamageEffect(AActor* HitActor) const
{
	if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
	{
		const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();

		TargetAsc->ApplyGameplayEffectSpecToSelf(*AssignDamageTypes(AbilitySystemComponent, ContextHandle).Data.Get());
	}
}

void UPlayerShockWaveAbility::ApplyStunEffect(AActor* HitActor) const
{
	if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
	{
		const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		const FGameplayEffectSpecHandle StunEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(StunEffectClass, GetAbilityLevel(), AbilitySystemComponent->MakeEffectContext());

		TargetAsc->ApplyGameplayEffectSpecToSelf(*StunEffectSpecHandle.Data.Get());
	}
}

float UPlayerShockWaveAbility::GetSphereRadius() const
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
