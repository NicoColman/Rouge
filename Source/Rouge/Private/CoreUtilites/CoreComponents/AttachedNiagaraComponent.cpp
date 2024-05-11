// Rouge


#include "CoreUtilites/CoreComponents/AttachedNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/CharacterInterfaces/CharacterBaseInterface.h"
#include "Components/AudioComponent.h"

UAttachedNiagaraComponent::UAttachedNiagaraComponent()
{
	bAutoActivate = false;
	AudioComponent = nullptr;
}

void UAttachedNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	ICharacterBaseInterface* CharacterBaseInterface = Cast<ICharacterBaseInterface>(GetOwner());
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
	{
		ASC->RegisterGameplayTagEvent(ComponentTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAttachedNiagaraComponent::TagChanged);
	}
	else if (CharacterBaseInterface)
	{
		CharacterBaseInterface->GetOnASCRegisteredDelegate().AddWeakLambda(this, [this](UAbilitySystemComponent* InASC)
		{
			InASC->RegisterGameplayTagEvent(ComponentTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAttachedNiagaraComponent::TagChanged);
		});
	}
	if (CharacterBaseInterface)
	{
		CharacterBaseInterface->GetOnDeathDelegate().AddDynamic(this, &UAttachedNiagaraComponent::OnOwnerDeath);
	}
}

void UAttachedNiagaraComponent::SetNiagaraAssets(const FAbilityCuesBase& AbilityCues)
{
	if (AbilityCues.AbilityParticles) SetAsset(AbilityCues.AbilityParticles);
	
	if (AbilityCues.AbilitySound)
	{
		AudioComponent = NewObject<UAudioComponent>(this);
		AudioComponent->SetupAttachment(this);
		AudioComponent->RegisterComponent();
		AudioComponent->SetSound(AbilityCues.AbilitySound);
		AudioComponent->SetVolumeMultiplier(0.5f);
	}
}

void UAttachedNiagaraComponent::ActivateComponents(const bool bActivate)
{
	if (bActivate)
	{
		Activate();
		if (AudioComponent) AudioComponent->Play();
	}
	else
	{
		Deactivate();
		if (AudioComponent) AudioComponent->Stop();
	}
}

void UAttachedNiagaraComponent::TagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		if (AudioComponent) AudioComponent->Play();
		Activate();
	}
	else
	{
		Deactivate();
		if (AudioComponent) AudioComponent->Stop();
	}
}

void UAttachedNiagaraComponent::OnOwnerDeath(AActor* DeadActor)
{
	Deactivate();
}