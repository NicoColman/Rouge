// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "FireBallProjectile.generated.h"

UCLASS()
class ROUGE_API AFireBallProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFireBallProjectile();
	virtual void Destroyed() override;
	
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAudioComponent> SoundComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> NiagaraImpactFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USoundCue> ProjectileSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USoundCue> ImpactSound;
private:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> CollisionBox;

	bool bHit;
};
