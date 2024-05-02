// Rouge


#include "GASManager/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UAbilityTask_TargetDataUnderMouse* MyObj = NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
	
	
	return MyObj;
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(AbilitySpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAbilityTask_TargetDataUnderMouse::SendMouseCursorData() const
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	const APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData->HitResult = HitResult;
	TargetDataHandle.Add(TargetData);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
		);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetData.Broadcast(TargetDataHandle);
	}
}

void UAbilityTask_TargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data,
	FGameplayTag ActivationTag) const
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetData.Broadcast(Data);
	}
}
