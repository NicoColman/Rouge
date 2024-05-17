// Rouge

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RougeAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class ROUGE_API ARougeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARougeAIController();
	
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTree> BehaviorTree;
};
