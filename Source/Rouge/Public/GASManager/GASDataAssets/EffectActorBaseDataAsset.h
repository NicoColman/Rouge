// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CoreUtilites/RougeLibrary.h"
#include "EffectActorBaseDataAsset.generated.h"

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	EOT_None UMETA(DisplayName = "None"),
	EOT_StaticMesh UMETA(DisplayName = "StaticMesh"),
	EOT_SkeletalMesh UMETA(DisplayName = "SkeletalMesh"),
	EOT_Flipbook UMETA(DisplayName = "FlipbookMesh")
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
	float ActorScale = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|ObjectType")
	EObjectType ObjectType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|ObjectType")
	TObjectPtr<UObject> EffectActorObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|ObjectType")
	EFlipbookRotation FlipbookRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Overlap")
	bool bUseSphereOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Overlap")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	EGameplayEffectDurationType DurationType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	EEffectApplicationPolicy EffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	EEffectRemovalPolicy EffectRemovalPolicy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	TSubclassOf<class UGameplayEffect> EffectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	bool bApplyEffectToEnemies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	bool bDestroyOnEffectApplied;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Base|Effect Config")
	bool bDestroyOnEffectRemoval;

	UPROPERTY()
	TObjectPtr<class UPaperFlipbook> WeaponSprite;
};
