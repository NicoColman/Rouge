// Rouge

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameplayTagContainer.h"
#include "CoreUtilites/RougeAbilityUtilities.h"
#include "AttachedNiagaraComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROUGE_API UAttachedNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	UAttachedNiagaraComponent();
	
	UPROPERTY(VisibleAnywhere)
	FGameplayTag ComponentTag;

	void SetNiagaraAssets(const FAbilityCuesBase& AbilityCues);
	
	/** Used to activate/deactivate the component on OnRep functions */
	void ActivateComponents(const bool bActivate);
	
protected:
	virtual void BeginPlay() override;

	void TagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	UFUNCTION()
	void OnOwnerDeath(AActor* DeadActor);

private:
	UPROPERTY()
	class UAudioComponent* AudioComponent;
};
