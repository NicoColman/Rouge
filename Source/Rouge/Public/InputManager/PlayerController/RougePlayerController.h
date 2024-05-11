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

public:
	ARougePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<APawn> CachedPawn;
	UPROPERTY()
	class ACharacterBase* CachedCharacter;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> PlayerBaseContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> LookAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	/** Data Asset */
	UPROPERTY(EditAnywhere, Category="DataAsset")
	TObjectPtr<class UInputConfigDataAsset> InputConfigDataAsset;
	class IRougeAbilitySystemInterface* AbilityInterface;

	ACharacterBase* GetCharacter();
	IRougeAbilitySystemInterface* GetAbilityInterface();
	TObjectPtr<class UAbilitySystemComponent> PawnASC;
	UAbilitySystemComponent* GetASC();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
