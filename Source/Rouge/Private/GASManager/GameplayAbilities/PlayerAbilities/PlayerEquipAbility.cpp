// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerEquipAbility.h"

#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"

void UPlayerEquipAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (!AbilitySystemComponent->HasMatchingGameplayTag(FRougeGameplayTags::Get().StateTag_Player_AbleEquip))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	if (ActorInfo->AvatarActor.Get()->HasAuthority())
	{
		
	}
}

AEffectActorBase* UPlayerEquipAbility::GetEffectActorFromActiveEffects(
	UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& EffectTag)
{
	FGameplayEffectQuery Query;
	Query.EffectTagQuery = FGameplayTagQuery::MakeQuery_MatchTag(EffectTag);
	TArray<FActiveGameplayEffectHandle> ActiveEffectHandles = AbilitySystemComponent->GetActiveEffects(Query);

	for (const FActiveGameplayEffectHandle& EffectHandle : ActiveEffectHandles)
	{
		const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(EffectHandle);
		if (ActiveEffect && ActiveEffect->Spec.GetEffectContext().GetInstigator())
		{
			UObject* SourceObject = ActiveEffect->Spec.GetEffectContext().GetSourceObject();
			AEffectActorBase* EffectActor = Cast<AEffectActorBase>(SourceObject);
			if (EffectActor)
			{
				return EffectActor;
			}
		}
	}
	return nullptr;
}