// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerShockWaveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CoreUtilites/RougeLibrary.h"
#include "GlobalManagers/RougeGameplayTags.h"


void UPlayerShockWaveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FVector StartLocation = AvatarActor->GetActorLocation();
	
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
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == AvatarActor) continue;
		if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor) && AvatarActor->HasAuthority())
		{
			URougeLibrary::ApplyDamageEffect(MakeDamageEffectParamsFromClassDefaults(HitActor));
		}
		
	}
	
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
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
