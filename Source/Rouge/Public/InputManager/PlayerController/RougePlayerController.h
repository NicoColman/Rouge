// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "RougePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API ARougePlayerController : public APlayerController
{
	GENERATED_BODY()

	ARougePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> PlayerBaseContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	/** Data Asset */
	//UPROPERTY(EditAnywhere, Category="DataAsset")
	//TObjectPtr<class UInputConfigDataAsset> InputConfigDataAsset;
	//class IAbilityBaseInterface* AbilityInterface;

	//IAbilityBaseInterface* GetAbilityInterface();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
