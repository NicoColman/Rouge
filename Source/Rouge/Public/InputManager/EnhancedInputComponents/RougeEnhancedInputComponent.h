// Rouge

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "RougeEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ROUGE_API URougeEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URougeEnhancedInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
