// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GASManager/GASDataAssets/EffectActorBaseDataAsset.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "EffectActorBase.generated.h"

UCLASS()
class ROUGE_API AEffectActorBase : public AActor
{
	GENERATED_BODY()

public:
	AEffectActorBase();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

	/**
	 * EffectActorBase Functions
	 */
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<class UGameplayEffect> GameplayEffectClass);

	void OnEffectOverlap(AActor* TargetActor);
	void OnEffectEndOverlap(AActor* TargetActor);
	
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	
	/**
	 * EffectActorBase Variables
	 */
	bool bDestroyOnEffectRemoval;
	float ActorLevel;
	
	UPROPERTY()
	EObjectType ObjectType;

	UPROPERTY()
	EGameplayEffectDurationType EffectDurationType;

	UPROPERTY()
	EEffectApplicationPolicy EffectApplicationPolicy;

	UPROPERTY()
	EEffectRemovalPolicy EffectRemovalPolicy;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshActor;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshActor;

	UPROPERTY()
	TObjectPtr<UPaperFlipbookComponent> FlipbookActor;

	UPROPERTY()
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEffectActorBaseDataAsset> EffectActorDataAsset;

	TMap<struct FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectsMap;
private:
	template<typename ComponentType>
	ComponentType* CreateSpecificActorComponent(UObject* Mesh);
	void SetSphereComponent();

public:
	FORCEINLINE UEffectActorBaseDataAsset* GetEffectActorDataAsset() const { return EffectActorDataAsset; }

};

template<typename ComponentType>
ComponentType* AEffectActorBase::CreateSpecificActorComponent(UObject* Mesh)
{
	ComponentType* NewComponent = NewObject<ComponentType>(this);
	if (NewComponent)
	{
		if (ComponentType::StaticClass() == UStaticMeshComponent::StaticClass())
		{
			UStaticMesh* StaticMesh = Cast<UStaticMesh>(Mesh);
			Cast<UStaticMeshComponent>(NewComponent)->SetStaticMesh(StaticMesh);
		}
		else if (ComponentType::StaticClass() == USkeletalMeshComponent::StaticClass())
		{
			USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Mesh);
			Cast<USkeletalMeshComponent>(NewComponent)->SetSkeletalMesh(SkeletalMesh);
		}
		else if (ComponentType::StaticClass() == UPaperFlipbookComponent::StaticClass())
		{
			UPaperFlipbook* Flipbook = Cast<UPaperFlipbook>(Mesh);
			Cast<UPaperFlipbookComponent>(NewComponent)->SetFlipbook(Flipbook);
		}
		NewComponent->RegisterComponent();
		NewComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	return NewComponent;
}