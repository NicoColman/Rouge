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

	virtual void AbilityActorInfoSet() override;
	
	virtual void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) override;

	virtual void AbilityInputTagHeld(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagPressed(const FGameplayTag InputTag) override;
	virtual void AbilityInputTagReleased(const FGameplayTag InputTag) override;
	
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	
};
