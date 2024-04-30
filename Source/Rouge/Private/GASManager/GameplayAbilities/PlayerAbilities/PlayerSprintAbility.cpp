// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerSprintAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerSprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
									const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!GetAvatarActorFromActorInfo()->HasAuthority() || !SpeedBoostEffectClass) return;

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	ActiveEffectHandle = BP_ApplyGameplayEffectToOwner(SpeedBoostEffectClass, 1, 1);

	/*
	IPlayerMovementCpInterface* PlayerMovementCpInterface = Cast<IPlayerMovementCpInterface>(GetActorInfo().MovementComponent.Get());
	if (PlayerMovementCpInterface)
	{
		PlayerMovementCpInterface->SetSprint(true);
	}
	*/
}

void UPlayerSprintAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UPlayerSprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	BP_RemoveGameplayEffectFromOwnerWithHandle(ActiveEffectHandle, -1);
	//IPlayerMovementCpInterface* PlayerMovementCpInterface = Cast<IPlayerMovementCpInterface>(GetActorInfo().MovementComponent.Get());
	//if (PlayerMovementCpInterface)
	//{
	//	PlayerMovementCpInterface->SetSprint(false);
	//}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

