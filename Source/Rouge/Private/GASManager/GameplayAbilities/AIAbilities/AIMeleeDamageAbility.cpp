// Rouge


#include "GASManager/GameplayAbilities/AIAbilities/AIMeleeDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CoreUtilites/RougeLibrary.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/CharacterInterfaces/CharacterPlayerInterface.h"

void UAIMeleeDamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	GetActorsInRangeAndApplyDamage();
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UAIMeleeDamageAbility::GetActorsInRangeAndApplyDamage() const
{
	const AActor* AvatarActor = GetAvatarActorFromActorInfo();
	const FVector StartLocation = AvatarActor->GetActorLocation();
	const float SourceStrength = GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UAttributeSetBase::GetStrengthAttribute());

	TArray<FHitResult> ActorsInRange;
	const bool bHit = GetWorld()->SweepMultiByChannel(ActorsInRange, StartLocation, StartLocation + FVector(0, 0, -1000), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(100.f));
	if (!bHit) return;

	for (FHitResult HitResult : ActorsInRange)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == AvatarActor) continue;
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
		if (TargetASC && HitActor->Implements<UCharacterPlayerInterface>() && AvatarActor->HasAuthority())
		{
			FDamageEffectParams DamageParams = MakeDamageEffectParamsFromClassDefaults(HitActor);
			DamageParams.BaseDamage = SourceStrength;
			URougeLibrary::ApplyDamageEffect(DamageParams);

			FGameplayCueParameters CueParams;
			const FVector ParticlesLocation = HitActor->GetActorLocation() - FVector(0, 0, 100);
			CueParams.Location = ParticlesLocation;
			TargetASC->ExecuteGameplayCue(FRougeGameplayTags::Get().GameplayCue_Ability_AI_Damage, CueParams);

			ApplyCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo());
		}
	}
}
