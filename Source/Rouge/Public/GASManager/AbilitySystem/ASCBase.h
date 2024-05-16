// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "ASCBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, class UASCBase*);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);

/**
 * 
 */
UCLASS()
class ROUGE_API UASCBase : public UAbilitySystemComponent, public IRougeAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UASCBase();
	virtual void AbilityActorInfoSet() override;
	
	virtual void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) override;
	virtual void AddPassiveCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) override;
	
	virtual void AbilityInputTagHeld(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagPressed(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(const FGameplayTag InputTag) override;

	void ForEachAbility(const FForEachAbility& Delegate);
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAbility(const FGameplayTag& AbilityTag);

	FAbilitiesGiven OnAbilitiesGiven;
	bool bStartupAbilitiesGiven;
	
protected:
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	
};
