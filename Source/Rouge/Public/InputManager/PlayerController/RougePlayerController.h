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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FVector2D Directionality;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<APawn> CachedPawn;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> PlayerBaseContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
	UFUNCTION(Server, Reliable)
	void ServerMove(const FVector2D& Direction);
	
	/** Data Asset */
	UPROPERTY(EditAnywhere, Category="DataAsset")
	TObjectPtr<class UInputConfigDataAsset> InputConfigDataAsset;
	class IRougeAbilitySystemInterface* AbilityInterface;

	IRougeAbilitySystemInterface* GetAbilityInterface();
	TObjectPtr<class UAbilitySystemComponent> PawnASC;
	UAbilitySystemComponent* GetASC();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
};
