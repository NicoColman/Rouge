// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "BasicSphereEffectActor.generated.h"

UCLASS()
class ROUGE_API ABasicSphereEffectActor : public AActor
{
	GENERATED_BODY()

public:
	ABasicSphereEffectActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSphereOverlap(
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

	FGameplayEffectSpecHandle EffectSpecToApply;
	TObjectPtr<class USphereComponent> SphereComponent;
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private:
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectsMap;
};
