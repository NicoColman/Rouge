// Rouge


#include "GASManager/GameplayEffects/MMCs/MMC_MaxHealth.h"

#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAttributeSetBase::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	int32 PlayerLevel = 1;
	if (const ICharacterBaseInterface* TargetCharacter = Cast<ICharacterBaseInterface>(Spec.GetContext().GetSourceObject()))
	{
		PlayerLevel = TargetCharacter->GetCharacterLevel();
	}

	return 80.f + Vigor * 2.5f + PlayerLevel * 12.f;
}
