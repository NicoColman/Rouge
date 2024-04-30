// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EffectActorBaseDataAsset.generated.h"

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	EOT_None UMETA(DisplayName = "None"),
	EOT_StaticMesh UMETA(DisplayName = "StaticMesh"),
	EOT_SkeletalMesh UMETA(DisplayName = "SkeletalMesh"),
};

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	EEAP_None UMETA(DisplayName = "None"),
	EEAP_ApplyOnOverlap UMETA(DisplayName = "Apply On Overlap"),
	EEAP_ApplyOnEndOverlap UMETA(DisplayName = "Apply On End Overlap "),
	EEAP_DoNotApply UMETA(DisplayName = "Do Not Apply"),
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	EERP_None UMETA(DisplayName = "None"),
	EERP_RemoveOnEndOverlap UMETA(DisplayName = "Remove On End Overlap "),
	EERP_DoNotRemove UMETA(DisplayName = "Do Not Remove"),
};


/**
 * 
 */
UCLASS()
class ROUGE_API UEffectActorBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	FGameplayTag EffectActorTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	float ActorLevel = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	EObjectType ObjectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	TObjectPtr<UObject> EffectActorObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	bool bUseSphereOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	EGameplayEffectDurationType DurationType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	EEffectApplicationPolicy EffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	EEffectRemovalPolicy EffectRemovalPolicy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	TSubclassOf<class UGameplayEffect> EffectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base")
	bool bDestroyOnEffectRemoval;
};
