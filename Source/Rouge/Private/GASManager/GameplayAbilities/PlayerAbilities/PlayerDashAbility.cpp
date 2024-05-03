// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerDashAbility.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/RootMotionSource.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "InputManager/PlayerController/RougePlayerController.h"


void UPlayerDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ActiveEffectHandle = BP_ApplyGameplayEffectToOwner(DashEffect, 1, 1);
	
	ExecuteGameplayCue();
	
	const FVector2D Vector = Cast<ARougePlayerController>(ActorInfo->PlayerController)->Directionality;
	const FVector Direction = FVector(Vector.X, Vector.Y, 0.f).GetSafeNormal();
	constexpr float Strength = 2000.f;
	constexpr float Duration = 0.2f;
	const float Velocity = GetAvatarActorFromActorInfo()->GetVelocity().Length();
	const FVector MomentumVelocity = Direction * (Velocity * 1.2f);
	
	UAbilityTask_ApplyRootMotionConstantForce* ApplyRootMotionConstantForce = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
		this,
		FName(),
		Direction,
		Strength,
		Duration,
		false,
		nullptr,
		ERootMotionFinishVelocityMode::SetVelocity,
		MomentumVelocity,
		0.f,
		false
		);
	ApplyRootMotionConstantForce->OnFinish.AddDynamic(this, &UPlayerDashAbility::OnDashFinished);
	ApplyRootMotionConstantForce->ReadyForActivation();
}

void UPlayerDashAbility::ExecuteGameplayCue() const
{
	FGameplayCueParameters CueParams;
	FGameplayTagContainer SourceTags;
	SourceTags.AddTag(FRougeGameplayTags::Get().Ability_Dash);
	CueParams.AggregatedSourceTags = SourceTags;
	CueParams.AbilityLevel = 1.f;
	
	GetAbilitySystemComponentFromActorInfo()->ExecuteGameplayCue(FRougeGameplayTags::Get().GameplayCue_Ability_Base, CueParams);
}

void UPlayerDashAbility::OnDashFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UPlayerDashAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	BP_RemoveGameplayEffectFromOwnerWithHandle(ActiveEffectHandle, -1);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
