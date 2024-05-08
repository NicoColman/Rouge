// Rouge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "CoreUtilites/RougeAbilityTypes.h"
#include "FireBallProjectile.generated.h"

UCLASS()
class ROUGE_API AFireBallProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFireBallProjectile();
	virtual void Destroyed() override;
	
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	FDamageEffectParams DamageEffectParams;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnHit();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphereComponent;
protected:
	virtual void BeginPlay() override;
	
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
