// Rouge


#include "GASManager/EffectActors/EffectActorBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerState.h"

AEffectActorBase::AEffectActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	ActorLevel = 1.f;
	bDestroyOnEffectRemoval = false;
	EffectActorDataAsset = nullptr;
	ObjectType = EObjectType::EOT_None;
	EffectDurationType = EGameplayEffectDurationType::Instant;
	EffectApplicationPolicy = EEffectApplicationPolicy::EEAP_None;
	EffectRemovalPolicy = EEffectRemovalPolicy::EERP_None;

	SetRootComponent(CreateDefaultSubobject<USphereComponent>(TEXT("SpehreComponent")));
}

void AEffectActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEffectActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetReplicateMovement(true);
}

void AEffectActorBase::BeginPlay()
{
	Super::BeginPlay();
	if (!EffectActorDataAsset) return;
	ObjectType = EffectActorDataAsset->ObjectType;
	EffectDurationType = EffectActorDataAsset->DurationType;
	EffectApplicationPolicy = EffectActorDataAsset->EffectApplicationPolicy;
	EffectRemovalPolicy = EffectActorDataAsset->EffectRemovalPolicy;
	ActorLevel = EffectActorDataAsset->ActorLevel;

	switch (ObjectType)
	{
	case EObjectType::EOT_None:
		checkf(ObjectType == EObjectType::EOT_None, TEXT("ObjectType is None in EffectActorBase"));
		break;
	case EObjectType::EOT_StaticMesh:
		{
			UStaticMesh* StaticMesh = Cast<UStaticMesh>(EffectActorDataAsset->EffectActorObject);
			StaticMeshActor = CreateSpecificActorComponent<UStaticMeshComponent>(StaticMesh);
		}
		break;
	case EObjectType::EOT_SkeletalMesh:
		{
			USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(EffectActorDataAsset->EffectActorObject);
			SkeletalMeshActor = CreateSpecificActorComponent<USkeletalMeshComponent>(SkeletalMesh);
		}
		break;
	default:
		break;
	}
	if ((SkeletalMeshActor || StaticMeshActor) && EffectActorDataAsset->bUseSphereOverlap)
	{
		SetSphereComponent();
	}
}

void AEffectActorBase::SetSphereComponent()
{
	USphereComponent* NewSphereComponent = NewObject<USphereComponent>(this);
	if (!NewSphereComponent) return;
	NewSphereComponent->RegisterComponent();
	NewSphereComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SphereComponent = NewSphereComponent;
	SphereComponent->SetSphereRadius(EffectActorDataAsset->SphereRadius);
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEffectActorBase::OnSphereOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEffectActorBase::OnSphereEndOverlap);
}


void AEffectActorBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnEffectOverlap(OtherActor);
}

void AEffectActorBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnEffectEndOverlap(OtherActor);
}

void AEffectActorBase::OnEffectOverlap(AActor* TargetActor)
{
	if (EffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, EffectActorDataAsset->EffectToApply);
	}
}

void AEffectActorBase::OnEffectEndOverlap(AActor* TargetActor)
{
	if (EffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, EffectActorDataAsset->EffectToApply);
	}
	if (EffectRemovalPolicy == EEffectRemovalPolicy::EERP_RemoveOnEndOverlap && EffectDurationType == EGameplayEffectDurationType::Infinite)
	{
		APawn* TargetPawn = Cast<APawn>(TargetActor);
		if (!TargetPawn || !TargetPawn->GetPlayerState()) return;
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetPawn->GetPlayerState());
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> ActiveEffectsToRemove;
		for (auto& ActiveEffect : ActiveEffectsMap)
		{
			if (ActiveEffect.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(ActiveEffect.Key, 1);
				ActiveEffectsToRemove.Add(ActiveEffect.Key);
			}
		}
		for (auto& ActiveEffect : ActiveEffectsToRemove)
		{
			ActiveEffectsMap.FindAndRemoveChecked(ActiveEffect);
		}
	}
}

void AEffectActorBase::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	const APawn* TargetPawn = Cast<APawn>(TargetActor);
	if (!TargetPawn || !TargetPawn->GetPlayerState()) return;
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetPawn->GetPlayerState());
	if (!TargetASC) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContext);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfiniteDuration = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfiniteDuration && EffectRemovalPolicy == EEffectRemovalPolicy::EERP_RemoveOnEndOverlap)
	{
		ActiveEffectsMap.Add(ActiveEffectHandle, TargetASC);
	}
}
