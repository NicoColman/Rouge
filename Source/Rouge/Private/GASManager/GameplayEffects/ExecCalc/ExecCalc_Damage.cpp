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

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
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

		const FRougeGameplayTags& RougeTags = FRougeGameplayTags::Get();
		
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Secondary_CriticalHitDamage, CriticalHitDamageDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(RougeTags.Attribute_Resistance_Lightning, LightningResistanceDef);
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
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const ICharacterBaseInterface* InterfaceSourceCharacter = Cast<ICharacterBaseInterface>(SourceActor);
	const ICharacterBaseInterface* InterfaceTargetCharacter = Cast<ICharacterBaseInterface>(TargetActor);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	for (const auto& Pair : FRougeGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag ResistanceType = Pair.Value;

		checkf(RougeDamageStatics().TagsToCaptureDefs.Contains(ResistanceType), TEXT("ResistanceType not found in TagsToCaptureDefs"));
		const FGameplayEffectAttributeCaptureDefinition DamageCaptureDef = RougeDamageStatics().TagsToCaptureDefs[ResistanceType];

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
	const float ArmorPenetrationCoefficient =  ArmorPenetrationCurve->Eval(InterfaceSourceCharacter->GetCharacterLevel());
	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100;

	const FRealCurve* EffectiveArmorCurve = SourceDataAsset->DamageCalculationsCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectArmorCoefficient =  EffectiveArmorCurve->Eval(InterfaceTargetCharacter->GetCharacterLevel());
	
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
	const float CriticalHitResistanceCoefficient =  CriticalHitResistanceCurve->Eval(InterfaceTargetCharacter->GetCharacterLevel());
	
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) <= EffectiveCriticalHitChance;

	URougeLibrary::SetCriticalHit(EffectContext, bCriticalHit);
	
	Damage = bCriticalHit ? 2.5f * Damage + SourceCriticalHitDamage : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAttributeSetBase::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
