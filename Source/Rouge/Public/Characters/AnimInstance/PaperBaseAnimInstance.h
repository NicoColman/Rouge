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
	virtual void OnInit_Implementation() override;

	UFUNCTION()
	FVector2D GetDirection() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	TObjectPtr<APaperZDCharacter> CachedCharacter;
};
