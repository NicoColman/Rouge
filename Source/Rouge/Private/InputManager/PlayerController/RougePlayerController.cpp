// Rouge


#include "InputManager/PlayerController/RougePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ARougePlayerController::ARougePlayerController()
{

}

void ARougePlayerController::BeginPlay()
{
	Super::BeginPlay();

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Basic
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARougePlayerController::Move);

	/** Data Asset*/
	/**
	UEnhancedInputComponentBase* EnhancedInputComponentBase = CastChecked<UEnhancedInputComponentBase>(InputComponent);
	EnhancedInputComponentBase->BindAbilityActions(InputConfigDataAsset, this,
		&AGamePlayerController::AbilityInputTagPressed, &AGamePlayerController::AbilityInputTagReleased,
		&AGamePlayerController::AbilityInputTagHeld);
		*/
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
	Directionality = InputAxisVector;
}

void ARougePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ARougePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void ARougePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}
