// Rouge


#include "WeaponManager/Projectiles/FireBallProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"


AFireBallProjectile::AFireBallProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 1500.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(SphereComponent);
	NiagaraComponent->SetAutoActivate(true);
}

void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();

	const ACharacter* CharacterInstigator = Cast<ACharacter>(GetInstigator());
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->IgnoreComponentWhenMoving(CharacterInstigator->GetCapsuleComponent(), true);
	if (HasAuthority())
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireBallProjectile::OnSphereOverlap);
	}
	SoundComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, NiagaraComponent);
}

void AFireBallProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator()) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), 1.f);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraImpactFX, GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector, true);
	SoundComponent->Stop();
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			if (DamageEffectSpecHandle.Data.IsValid())
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			}
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

void AFireBallProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), 1.f);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraImpactFX, GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector, true);
		SoundComponent->Stop();
	}
	Super::Destroyed();
}