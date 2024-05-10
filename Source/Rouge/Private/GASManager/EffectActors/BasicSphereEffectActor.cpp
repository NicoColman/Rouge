// Rouge


#include "GASManager/EffectActors/BasicSphereEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABasicSphereEffectActor::ABasicSphereEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
}

void ABasicSphereEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasicSphereEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicSphereEffectActor::OnSphereOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABasicSphereEffectActor::OnSphereEndOverlap);
}

void ABasicSphereEffectActor::Destroyed()
{
	if (ActiveEffectHandle.IsValid())
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
		if (TargetASC)
		{
			TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle, -1);
		}
	}
	Super::Destroyed();
}

void ABasicSphereEffectActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("ABasicSphereEffectActor::OnSphereOverlap)"));

	if (TargetASC && EffectSpecToApply.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("ABasicSphereEffectActor::OnSphereOverlap - ActiveEffectHandle.IsValid()"));
		ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecToApply.Data.Get());
	}
}

void ABasicSphereEffectActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC && ActiveEffectHandle.IsValid())
	{
		TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle, -1);
	}
}
