// Fill out your copyright notice in the Description page of Project Settings.


#include "Rouge/Public/Characters/CharacterEnemy.h"
#include "AbilitySystemComponent.h"
#include "GASManager/AbilitySystem/ASCBase.h"
#include "GASManager/AttributeSet/AttributeSetBase.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "AIManager/RougeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CharacterDataAssets/CharacterBaseDataAsset.h"

ACharacterEnemy::ACharacterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UASCBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	Level = 1;
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	AIController = Cast<ARougeAIController>(NewController);
	if (AIController && BehaviorTree)
	{
		AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AIController->RunBehaviorTree(BehaviorTree);
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterDataAsset->CharacterClass != ECharacterClass::Melee);
	}
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UASCBase>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FRougeGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACharacterEnemy::StunTagChanged);
	if (HasAuthority())
	{
		InitializeAttributes();
	}
	AddCharacterAbilities();
}

//OnASCRegistered.BroadCast(AbilitySystemComponent);