// Rouge


#include "GASManager/GameplayEffects/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "Characters/CharacterDataAssets/CharacterBaseDataAsset.h"
#include "CoreUtilites/RougeAbilityTypes.h"
#include "CoreUtilites/RougeLibrary.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"

struct RougeDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	
	RougeDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, LightningResistance, Target, false);
	}
};

static const RougeDamageStatics& DamageStatics()
{
	static RougeDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
		
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_Armor, DamageStatics().ArmorDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Resistance_Fire, DamageStatics().FireResistanceDef);
	TagsToCaptureDefs.Add(GameplayTags.Attribute_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	
	const ICharacterBaseInterface* InterfaceSourceCharacter = Cast<ICharacterBaseInterface>(SourceActor);
	const ICharacterBaseInterface* InterfaceTargetCharacter = Cast<ICharacterBaseInterface>(TargetActor);

	int32 SourceActorLevel = InterfaceSourceCharacter ? InterfaceSourceCharacter->GetCharacterLevel() : 1;
	int32 TargetActorLevel = InterfaceTargetCharacter ? InterfaceTargetCharacter->GetCharacterLevel() : 1;
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Debuffs
	DetermineDebuff(ExecutionParams, Spec, EvaluationParameters, TagsToCaptureDefs);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const auto& Pair : GameplayTags.DamageTypesToResistances)
	{
		const FGameplayTag ResistanceType = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceType), TEXT("ResistanceType not found in TagsToCaptureDefs"));
		const FGameplayEffectAttributeCaptureDefinition DamageCaptureDef = TagsToCaptureDefs[ResistanceType];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);
		
		float ResistanceValue = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageCaptureDef, EvaluationParameters, ResistanceValue);
		ResistanceValue = FMath::Clamp(ResistanceValue, 0.f, 100.f);
		DamageTypeValue *= (100 - ResistanceValue) / 100.f;
		Damage += DamageTypeValue;
	}
	
	// Capture BlockChance on Target, and check for successful Block
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1, 100) <= TargetBlockChance;

	FGameplayEffectContextHandle EffectContext = Spec.GetContext();
	URougeLibrary::SetBlockedHit(EffectContext, bBlocked);
	
	Damage = bBlocked ? 0.f : Damage;
	
	// Calculate Armor and Armor Penetration
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetBlockChance = FMath::Max<float>(TargetArmor, 0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	const UCharacterBaseDataAsset* SourceDataAsset = URougeLibrary::GetCharacterBaseDataAsset(SourceActor);
	const FRealCurve* ArmorPenetrationCurve = SourceDataAsset->DamageCalculationsCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient =  ArmorPenetrationCurve->Eval(SourceActorLevel);
	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100;

	const FRealCurve* EffectiveArmorCurve = SourceDataAsset->DamageCalculationsCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectArmorCoefficient =  EffectiveArmorCurve->Eval(TargetActorLevel);
	
	Damage *= (100 - EffectiveArmor * EffectArmorCoefficient) / 100.f;

	// Calculate Critical Hit Chance and Damage
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	const FRealCurve* CriticalHitResistanceCurve = SourceDataAsset->DamageCalculationsCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient =  CriticalHitResistanceCurve->Eval(TargetActorLevel);
	
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) <= EffectiveCriticalHitChance;

	URougeLibrary::SetCriticalHit(EffectContext, bCriticalHit);
	
	Damage = bCriticalHit ? 2.5f * Damage + SourceCriticalHitDamage : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                       const FGameplayEffectSpec& Spec,
                                       FAggregatorEvaluateParameters EvaluationParameters,
                                       const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& TagsToDefs)
const
{
	const FRougeGameplayTags& GameplayTags = FRougeGameplayTags::Get();
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key
		;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > 0.9f)
		{
			const float SourceDebuffChange = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagsToDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChange = SourceDebuffChange * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChange;
			if (!bDebuff) return;

			FGameplayEffectContextHandle ContextHandle = Spec.GetContext();
			URougeLibrary::SetSuccessfulDebuff(ContextHandle, true);
			URougeLibrary::SetDamageType(ContextHandle, DamageType);

			const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
			const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
			const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

			URougeLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
			URougeLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
			URougeLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
		}
	}
}