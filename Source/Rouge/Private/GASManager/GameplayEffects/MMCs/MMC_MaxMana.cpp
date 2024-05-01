// Rouge


#include "GASManager/GameplayEffects/MMCs/MMC_MaxMana.h"

#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAttributeSetBase::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	ICharacterBaseInterface* TargetCharacter = Cast<ICharacterBaseInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = TargetCharacter->GetCharacterLevel();

	return 50.f + Intelligence * 2.5f + PlayerLevel * 15.f;
}
