// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/HoverInterface.h"
#include "EnhancedInputComponent.h"

ALC_PlayerController::ALC_PlayerController()
{
	bReplicates = true;
}

void ALC_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ALC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerInputContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	
}

void ALC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALC_PlayerController::Move);
}

void ALC_PlayerController::Move(const FInputActionValue& InputActionValue)
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
}

void ALC_PlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IHoverInterface>(CursorHit.GetActor());


	if (LastActor==nullptr && CurrentActor==nullptr)
	{

	}
	if (LastActor == nullptr && CurrentActor)
	{
		CurrentActor->HighlightActor();
	}
	if (LastActor && CurrentActor==nullptr)
	{
		LastActor->UnHighlightActor();
	}
	if (LastActor && CurrentActor && CurrentActor==LastActor)
	{
		
	}
	if (LastActor && CurrentActor && CurrentActor != LastActor)
	{
		LastActor->UnHighlightActor();
		CurrentActor->HighlightActor();
	}



}
