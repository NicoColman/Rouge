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

	TArray<FHitResult> HitResults;
	GetWorld()->SweepMultiByProfile(
		HitResults,
		ActorInfo->OwnerActor->GetActorLocation(),
		ActorInfo->OwnerActor->GetActorLocation() + FVector(0, 0, -1000),
		FQuat::Identity,
		FName(),
		FCollisionShape::MakeSphere(500),
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
		const FGameplayEffectSpecHandle DamageEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), AbilitySystemComponent->MakeEffectContext());

		const float ScaleDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle, FRougeGameplayTags::Get().Damage, ScaleDamage);
		
		TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
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
