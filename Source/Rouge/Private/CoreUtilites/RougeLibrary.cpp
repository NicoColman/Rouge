// Rouge


#include "CoreUtilites/RougeLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CoreUtilites/RougeAbilityTypes.h"
#include "GlobalManagers/RougeAssetManager.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"

URougeLibrary::URougeLibrary()
{
}

UObject* URougeLibrary::GetPrimaryObjectFromTag(const FGameplayTag& Tag, const ANSICHAR* InName)
{
	FPrimaryAssetId PrimaryAssetId = GetPrimaryAssetIdFromTag(Tag, InName);
	if (PrimaryAssetId.IsValid())
	{
		URougeAssetManager& AssetManager = URougeAssetManager::Get();
		UObject* LoadedAsset = AssetManager.GetPrimaryAssetObject(PrimaryAssetId);
		if (!LoadedAsset)
		{
			TSharedPtr<FStreamableHandle> Handle = AssetManager.LoadPrimaryAsset(PrimaryAssetId);
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				LoadedAsset = Handle->GetLoadedAsset();
			}
		}
		if (LoadedAsset)
		{
			return LoadedAsset;
		}
	}
	return nullptr;
}

FPrimaryAssetId URougeLibrary::GetPrimaryAssetIdFromTag(const FGameplayTag& Tag, const ANSICHAR* InName)
{
	const FString AssetName = Tag.GetTagName().ToString();
	return FPrimaryAssetId(FPrimaryAssetType(InName), FName(*AssetName));
}

FRotator URougeLibrary::GetFlipbookRotation(EFlipbookRotation FlipbookRotation)
{
	switch (FlipbookRotation)
	{
	case EFlipbookRotation::EFR_North:
		return FRotator(0, 0, 0);
	case EFlipbookRotation::EFR_South:
		return FRotator(0, 180, 0);
	case EFlipbookRotation::EFR_East:
		return FRotator(0, 90, 0);
	case EFlipbookRotation::EFR_West:
		return FRotator(0, -90, 0);
	default:
		return FRotator::ZeroRotator;
	}
}

UCharacterBaseDataAsset* URougeLibrary::GetCharacterBaseDataAsset(AActor* Actor)
{
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(Actor))
	{
		return CharacterInterface->GetCharacterDataAsset();
	}
	return nullptr;
}

bool URougeLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->IsBlockedHit();
	}
	return false;
}

bool URougeLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->IsCriticalHit();
	}
	return false;
}

bool URougeLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float URougeLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->GetDebuffDamage();
	}
	return 0.f;
}

float URougeLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->GetDebuffDuration();
	}
	return 0.f;
}

float URougeLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->GetDebuffFrequency();
	}
	return 0.f;
}

FGameplayTag URougeLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		if (RougeEffectContext->GetDamageType().IsValid())
		{
			return *RougeEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

FVector URougeLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->GetDeathImpulse();
	}
	return FVector::ZeroVector;
}

FVector URougeLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContext)
{
	if (const FRougeGameplayEffectContext* RougeEffectContext = static_cast<const FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		return RougeEffectContext->GetKnockbackForce();
	}
	return FVector::ZeroVector;
}

void URougeLibrary::SetBlockedHit(FGameplayEffectContextHandle& EffectContext, bool bBlockedHit)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetIsBlockedHit(bBlockedHit);
	}
}

void URougeLibrary::SetCriticalHit(FGameplayEffectContextHandle& EffectContext, bool bCriticalHit)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetIsCriticalHit(bCriticalHit);
	}
}

void URougeLibrary::SetSuccessfulDebuff(FGameplayEffectContextHandle& EffectContext, bool bSuccessfulDebuff)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetIsSuccessfulDebuff(bSuccessfulDebuff);
	}
}

void URougeLibrary::SetDebuffDamage(FGameplayEffectContextHandle& EffectContext, float DebuffDamage)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetDebuffDamage(DebuffDamage);
	}
}

void URougeLibrary::SetDebuffDuration(FGameplayEffectContextHandle& EffectContext, float DebuffDuration)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetDebuffDuration(DebuffDuration);
	}
}

void URougeLibrary::SetDebuffFrequency(FGameplayEffectContextHandle& EffectContext, float DebuffFrequency)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetDebuffFrequency(DebuffFrequency);
	}
}

void URougeLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContext, const FGameplayTag& DamageType)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		const TSharedPtr<FGameplayTag> SharedDamageType = MakeShared<FGameplayTag>(DamageType);
		RougeEffectContext->SetDamageType(SharedDamageType);
	}
}

void URougeLibrary::SetDeathImpulse(FGameplayEffectContextHandle& EffectContext, FVector DeathImpulse)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetDeathImpulse(DeathImpulse);
	}
}

void URougeLibrary::SetKnockbackForce(FGameplayEffectContextHandle& EffectContext, FVector KnockbackForce)
{
	if (FRougeGameplayEffectContext* RougeEffectContext = static_cast<FRougeGameplayEffectContext*>(EffectContext.Get()))
	{
		RougeEffectContext->SetKnockbackForce(KnockbackForce);
	}
}

FGameplayEffectContextHandle URougeLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FRougeGameplayTags& RougeGameplayTags = FRougeGameplayTags::Get();
	const AActor* SourceActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	
	FGameplayEffectContextHandle EffectContext = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(SourceActor);
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageEffectClass, DamageEffectParams.AbilityLevel, EffectContext);
	SetDeathImpulse(EffectContext, DamageEffectParams.DeathImpulse);
	SetKnockbackForce(EffectContext, DamageEffectParams.KnockbackForce);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, RougeGameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, RougeGameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, RougeGameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, RougeGameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContext;
}
