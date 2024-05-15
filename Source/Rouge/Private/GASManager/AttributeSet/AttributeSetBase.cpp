// Rouge


#include "GASManager/AttributeSet/AttributeSetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "CoreUtilites/RougeLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/GameModeInterfaces/RougeGameModeInterface.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"
#include "Interfaces/CharacterInterfaces/CharacterPlayerInterface.h"

UAttributeSetBase::UAttributeSetBase()
{
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();

	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Vigor, GetVigorAttribute);

	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxMana, GetMaxManaAttribute);

	/* Vital Attributes */
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_Mana, GetManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_Speed, GetSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Vital_JumpHeight, GetJumpHeightAttribute);
	
	/* Resistance Attributes */
	TagsToAttributes.Add(GameplayTags.Attribute_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Resistance_Lightning, GetLightningResistanceAttribute);
}

void UAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Speed, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, HealthRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, ManaRegeneration, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, MaxMana, COND_None, REPNOTIFY_Always);

	// Resistance Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, PhysicalResistance, COND_None, REPNOTIFY_Always);
	
	// Vital Attributes
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, JumpHeight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Sanity, COND_None, REPNOTIFY_Always);
}

/** Only used for clamp attributes, this function fires everytime a value gets updated, it's not permanently changed */
void UAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Source = cause of the effect, Target = target of the effect (owner of this ASC)
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage(Props);
	}
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		HandleIncomingXP(Props);
	}
}

void UAttributeSetBase::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!Props.SourceController && Props.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetCharacter);
	}
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		Props.TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = GetSpeed();
	}
}

void UAttributeSetBase::HandleIncomingDamage(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);
	if (LocalIncomingDamage < 0.f) return;
	const float NewHealth = GetHealth() - LocalIncomingDamage;
	SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
	if (NewHealth <= 0.f)
	{
		Props.TargetCharacter->Destroy();
		if (IRougeGameModeInterface* GameMode = Cast<IRougeGameModeInterface>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->RequestRespawn(Props.TargetController);
		}
		SendXPEvent(Props);
	}
	else
	{
		FGameplayTagContainer TagContainer;
		//TagContainer.AddTag(FRougeGameplayTags::Get().Effect_HitReact);
		Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
		const FVector& KnockbackForce = URougeLibrary::GetKnockbackForce(Props.EffectContextHandle);
		if (!KnockbackForce.IsNearlyZero(1.f))
		{
			Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
		}
	}
	const bool bBlock = URougeLibrary::IsBlockedHit(Props.EffectContextHandle);
	const bool bCritical = URougeLibrary::IsCriticalHit(Props.EffectContextHandle);

	if (URougeLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
	{
		Debuff(Props);
	}
}

void UAttributeSetBase::Debuff(const FEffectProperties& Props)
{ 
	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceAvatarActor);
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();

	const FGameplayTag DamageType = URougeLibrary::GetDamageType(Props.EffectContextHandle);
	const float DebuffDamage = URougeLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuration = URougeLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = URougeLibrary::GetDebuffFrequency(Props.EffectContextHandle);
	
	const FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuration);
	
	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	const FGameplayTag DebuffTag = GameplayTags.DamageTypesToDebuffs[DamageType];
	UTargetTagsGameplayEffectComponent& Component = Effect->FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	TagContainer.Added.AddTag(DebuffTag);
	TagContainer.CombinedTags.AddTag(DebuffTag);
	if (DebuffTag.MatchesTagExact(GameplayTags.Debuff_Stun))
	{
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputHeld);
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputPressed);
		TagContainer.Added.AddTag(GameplayTags.Player_Block_InputReleased);
	}
	Component.SetAndApplyTargetTagChanges(TagContainer); 
	
	
	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	const int32 Index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = GetIncomingDamageAttribute();

	if (const FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
	{
		FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(MutableSpec->GetContext().Get());
		const TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DamageType));
		RougeEffectContext->SetDamageType(DebuffDamageType);

		Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
	}
}

void UAttributeSetBase::HandleIncomingXP(const FEffectProperties& Props)
{
	const float LocalIncomingXP = GetIncomingXP();
	SetIncomingXP(0.f);

	if (ICharacterPlayerInterface* PlayerInterface = Cast<ICharacterPlayerInterface>(Props.TargetCharacter))
	{
		const int32 CurrentLevel = Cast<ICharacterBaseInterface>(Props.SourceCharacter)->GetCharacterLevel();
		const int32 CurrentXP = PlayerInterface->GetXP();

		const int32 NewLevel = PlayerInterface->FindLevelForXP(CurrentXP + LocalIncomingXP);
		const int32 NumLevelUps = NewLevel - CurrentLevel;
		if (NumLevelUps > 0)
		{
			for (int32 i = 0; i < NumLevelUps; i++)
			{
				const int32 AttributePointsReward = PlayerInterface->GetAttributesPointsRewards(CurrentLevel + i);
				const int32 SpellPointsReward = PlayerInterface->GetSpellPointsRewards(CurrentLevel + i);
				PlayerInterface->AddToPlayerLevel(NumLevelUps);
				PlayerInterface->AddToAttributesPoints(AttributePointsReward);
				PlayerInterface->AddToSpellPoints(SpellPointsReward);
				PlayerInterface->LevelUp();
			}
		}
			
		PlayerInterface->AddToXP(LocalIncomingXP);
	}
}

void UAttributeSetBase::SendXPEvent(const FEffectProperties& Props)
{
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(Props.TargetCharacter))
	{
		const int32 XPReward = URougeLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, CharacterInterface->GetCharacterLevel());
		const FGameplayTag XPEventTag = FRougeGameplayTags::Get().SetByCaller_Attribute_IncomingXP;
		FGameplayEventData Payload;
		Payload.EventTag = XPEventTag;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, XPEventTag, Payload);
	}
}

void UAttributeSetBase::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	
	if (Attribute == GetSpeedAttribute())
	{
		AActor* Actor = GetOwningAbilitySystemComponent()->AbilityActorInfo->AvatarActor.Get();
		if (const ACharacter* Character = Cast<ACharacter>(Actor))
		{
			Character->GetCharacterMovement()->MaxWalkSpeed = NewValue;
		}
	}
	if (Attribute == GetJumpHeightAttribute())
	{
		AActor* Actor = GetOwningAbilitySystemComponent()->AbilityActorInfo->AvatarActor.Get();
		if (const ACharacter* Character = Cast<ACharacter>(Actor))
		{
			Character->GetCharacterMovement()->JumpZVelocity = NewValue;
		}
	}
}

void UAttributeSetBase::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Speed, OldSpeed);
}

void UAttributeSetBase::OnRep_JumpHeight(const FGameplayAttributeData& OldJumpHeight) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, JumpHeight, OldJumpHeight);
}

void UAttributeSetBase::OnRep_Sanity(const FGameplayAttributeData& OldSanity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Sanity, OldSanity);
}

void UAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Health, OldHealth);
}

void UAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Mana, OldMana);
}

void UAttributeSetBase::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Strength, OldStrength);
}

void UAttributeSetBase::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Intelligence, OldIntelligence);
}

void UAttributeSetBase::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Resilience, OldResilience);
}

void UAttributeSetBase::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Vigor, OldVigor);
}

void UAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Armor, OldArmor);
}

void UAttributeSetBase::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, ArmorPenetration, OldArmorPenetration);
}

void UAttributeSetBase::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, BlockChance, OldBlockChance);
}

void UAttributeSetBase::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, CriticalHitChance, OldCriticalHitChance);
}

void UAttributeSetBase::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, CriticalHitDamage, OldCriticalHitDamage);
}

void UAttributeSetBase::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, CriticalHitResistance, OldCriticalHitResistance);
}

void UAttributeSetBase::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, HealthRegeneration, OldHealthRegeneration);
}

void UAttributeSetBase::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, ManaRegeneration, OldManaRegeneration);
}

void UAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UAttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, MaxMana, OldMaxMana);
}

void UAttributeSetBase::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, FireResistance, OldFireResistance);
}

void UAttributeSetBase::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, LightningResistance, OldLightningResistance);
}

void UAttributeSetBase::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, ArcaneResistance, OldArcaneResistance);
}

void UAttributeSetBase::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, PhysicalResistance, OldPhysicalResistance);
}