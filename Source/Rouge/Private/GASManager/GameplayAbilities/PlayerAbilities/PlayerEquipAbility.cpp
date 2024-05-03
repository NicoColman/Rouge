// Rouge


#include "GASManager/GameplayAbilities/PlayerAbilities/PlayerEquipAbility.h"

#include "AbilitySystemComponent.h"
#include "PaperZDCharacter.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "PaperFlipbookComponent.h"
#include "Interfaces/GameModeInterfaces/RougeGameModeInterface.h"
#include "GameFramework/GameModeBase.h"

void UPlayerEquipAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayCueParameters CueParams;
	FGameplayTagContainer SourceTags;
	SourceTags.AddTag(FRougeGameplayTags::Get().Ability_Pickup);
	CueParams.AggregatedSourceTags = SourceTags;
	GetCurrentActorInfo()->AbilitySystemComponent->ExecuteGameplayCue(FRougeGameplayTags::Get().GameplayCue_Ability_Base, CueParams);
	
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (ActorInfo->AvatarActor.Get()->HasAuthority())
	{
		if (AEffectActorBase* EffectActor = GetEffectActorFromActiveEffects(AbilitySystemComponent, FRougeGameplayTags::Get().WeaponType_Proxy))
		{
			const FGameplayTag& EffectActorTag = EffectActor->GetEffectActorDataAsset()->EffectActorTag;
			EquipActor(EffectActorTag);
			EffectActor->SetActorLocation(FVector::ZeroVector);
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

AEffectActorBase* UPlayerEquipAbility::GetEffectActorFromActiveEffects(
	const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& EffectTag)
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
			if (AEffectActorBase* EffectActor = Cast<AEffectActorBase>(SourceObject))
			{
				return EffectActor;
			}
		}
	}
	return nullptr;
}

void UPlayerEquipAbility::EquipActor(const FGameplayTag& EffectActorTag) const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	AbilitySystemComponent->AddLooseGameplayTag(EffectActorTag);
	AbilitySystemComponent->AddReplicatedLooseGameplayTag(EffectActorTag);
	IRougeGameModeInterface* GameMode = Cast<IRougeGameModeInterface>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	
	AActor* Weapon = GameMode->GetWeaponFromPool(EffectActorTag);
	if (!Weapon) return;

	const APaperZDCharacter* Avatar = Cast<APaperZDCharacter>(GetActorInfo().AvatarActor.Get());
	if (!Avatar) return;
	Weapon->AttachToComponent(Avatar->GetSprite(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SOCKET_Weapon"));
}
