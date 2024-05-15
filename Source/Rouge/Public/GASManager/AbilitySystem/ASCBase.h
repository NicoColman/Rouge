// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "ASCBase.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UASCBase : public UAbilitySystemComponent, public IRougeAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual void AbilityActorInfoSet() override;
	
	virtual void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) override;
	virtual void AddPassiveCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) override;

	virtual void AbilityInputTagHeld(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagPressed(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(const FGameplayTag InputTag) override;

	FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayAbilitySpec*GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAbility(const FGameplayTag& AbilityTag);
	
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	
};
