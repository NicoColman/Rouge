// Rouge


#include "UIManager/WidgetControllers/OverlayWidgetController.h"

#include "GASManager/AbilitySystem/ASCBase.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "GASManager/GASDataAssets/AbilityInfoDataAsset.h"
#include "GASManager/GASDataAssets/LevelUpInfoDataAsset.h"
#include "PlayerState/PlayerStateBase.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAttributeSetBase* AttributeSetBase = CastChecked<UAttributeSetBase>(AttributeSet);
	
	OnHealthChanged.Broadcast(AttributeSetBase->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSetBase->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	APlayerStateBase* PlayerStateBase = CastChecked<APlayerStateBase>(PlayerState);
	PlayerStateBase->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::XPChanged);
	PlayerStateBase->OnLevelChangedDelegate.AddLambda(
		[this](const int32 NewLevel) { OnLevelChanged.Broadcast(NewLevel); }
	);
	
	const UAttributeSetBase* AttributeSetBase = CastChecked<UAttributeSetBase>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	if (UASCBase* ASC = CastChecked<UASCBase>(AbilitySystemComponent))
	{
		if (ASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(ASC);
		}
		else
		{
			ASC->OnAbilitiesGiven.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);

}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::XPChanged(const int32 NewXP) const
{
	const APlayerStateBase* PlayerStateBase = CastChecked<APlayerStateBase>(PlayerState);
	const ULevelUpInfoDataAsset* LevelUpInfo = PlayerStateBase->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("LevelUpInfoDataAsset is not set!"));

	
	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInfo.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfo[Level].LevelUpRequirement;
		const int32 PreviousLevelRequirement = LevelUpInfo->LevelUpInfo[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPChanged.Broadcast(XPBarPercent);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UASCBase* ASC)
{
	if (!ASC->bStartupAbilitiesGiven) return;

	FForEachAbility ExecuteForEachAbility;
	ExecuteForEachAbility.BindLambda(
		[this, ASC](const FGameplayAbilitySpec& Spec)
		{
			FRougeAbilityInfo Info = AbilityInfoDataAsset->GetAbilityInfoFromTag(ASC->GetAbilityTagFromSpec(Spec));
			Info.InputTag = ASC->GetInputTagFromSpec(Spec);
			OnAbilityInfo.Broadcast(Info);
		}
	);
	ASC->ForEachAbility(ExecuteForEachAbility);
}
