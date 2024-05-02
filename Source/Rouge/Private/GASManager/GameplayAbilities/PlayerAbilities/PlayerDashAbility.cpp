// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerDashAbility.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDCharacter.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "GameFramework/RootMotionSource.h"


void UPlayerDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const APaperZDCharacter* Character = Cast<APaperZDCharacter>(GetAvatarActorFromActorInfo());
	if (!Character) return;
	const FVector CharacterForwardVector = Character->GetVelocity();
	constexpr float Strength = 4000.f;
	constexpr float Duration = 0.5f;
	const FVector Velocity = GetOwningActorFromActorInfo()->GetVelocity();
	UAbilityTask_ApplyRootMotionConstantForce* ApplyRootMotionConstantForce = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
		this,
		FName(),
		CharacterForwardVector,
		Strength,
		Duration,
		false,
		nullptr,
		ERootMotionFinishVelocityMode::SetVelocity,
		Velocity,
		0.f,
		false
		);
	ApplyRootMotionConstantForce->OnFinish.AddDynamic(this, &UPlayerDashAbility::OnDashFinished);
	ApplyRootMotionConstantForce->ReadyForActivation();
}

void UPlayerDashAbility::OnDashFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
