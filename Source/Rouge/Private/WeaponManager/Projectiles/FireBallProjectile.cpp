// Rouge


#include "WeaponManager/Projectiles/FireBallProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AFireBallProjectile::AFireBallProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBox->SetNotifyRigidBodyCollision(true);
	
	CollisionBox->SetBoxExtent(FVector(5, 2.5, 2.5));
	CollisionBox->SetLineThickness(2.0);
	CollisionBox->SetVisibility(false);
	CollisionBox->SetHiddenInGame(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 1500.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(CollisionBox);
	NiagaraComponent->SetAutoActivate(true);
}

void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		CollisionBox->OnComponentHit.AddDynamic(this, &AFireBallProjectile::OnHit);
	}
	SoundComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, NiagaraComponent);
}

void AFireBallProjectile::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.ImpactPoint, 1.f);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraImpactFX, Hit.ImpactPoint, FRotator::ZeroRotator, FVector::OneVector, true);
	SoundComponent->Stop();
	
	if (HasAuthority())
	{
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