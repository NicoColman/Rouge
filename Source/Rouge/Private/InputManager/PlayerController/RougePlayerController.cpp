// Rouge


#include "InputManager/PlayerController/RougePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputManager/EnhancedInputComponents/RougeEnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GlobalManagers/RougeGameplayTags.h"
#include "Interfaces/GASInterfaces/RougeAbilitySystemInterface.h"
#include "Net/UnrealNetwork.h"

ARougePlayerController::ARougePlayerController()
{
	AbilityInterface = nullptr;
}

void ARougePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARougePlayerController, Directionality);
}

void ARougePlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	if (!ensure(PlayerBaseContext))
	{
		UE_LOG(LogTemp, Error, TEXT(" PlayerBaseContext is null."));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem)
	{
		return;
	}
	Subsystem->AddMappingContext(PlayerBaseContext, 0);
	FInputModeGameAndUI InputModeData;
}

void ARougePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	URougeEnhancedInputComponent* EnhancedInputComponentBase = CastChecked<URougeEnhancedInputComponent>(InputComponent);

	// Basic
	EnhancedInputComponentBase->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARougePlayerController::Move);

	/** Data Asset*/
	EnhancedInputComponentBase->BindAbilityActions(InputConfigDataAsset, this,
		&ARougePlayerController::AbilityInputTagPressed, &ARougePlayerController::AbilityInputTagReleased,
		&ARougePlayerController::AbilityInputTagHeld);
}

void ARougePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputPressed)) || !GetAbilityInterface()) return;
	
	GetAbilityInterface()->AbilityInputTagPressed(InputTag);
}

void ARougePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputReleased)) || !GetAbilityInterface()) return;
	
	GetAbilityInterface()->AbilityInputTagReleased(InputTag);
}

void ARougePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if ((GetASC() && GetASC()->HasMatchingGameplayTag(
		FRougeGameplayTags::Get().Player_Block_InputHeld)) || !GetAbilityInterface()) return;

	GetAbilityInterface()->AbilityInputTagHeld(InputTag);
}

void ARougePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	ServerMove(InputAxisVector);
}

void ARougePlayerController::ServerMove_Implementation(const FVector2D& Direction)
{
	Directionality = FVector2D(Direction.Y, Direction.X);
}

UAbilitySystemComponent* ARougePlayerController::GetASC()
{
	if (PawnASC) return PawnASC;
	return PawnASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>());
}

IRougeAbilitySystemInterface* ARougePlayerController::GetAbilityInterface()
{
	if (AbilityInterface) return AbilityInterface;
	return AbilityInterface = Cast<IRougeAbilitySystemInterface>(GetASC());
}