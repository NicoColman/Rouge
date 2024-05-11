// Rouge

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "PaperBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROUGE_API UPaperBaseAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	class ACharacterBase* CachedCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	class ARougePlayerController* CachedController;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	bool bIsFalling;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	bool bHasVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	FVector Velocity;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	FVector2D Directionality;
	UPROPERTY(BlueprintReadOnly, Category = "Variables")
	FVector2D NewDirectionality;
};
