// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/HoverInterface.h"
#include "Input/LC_EnhancedInputComponent.h"
#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "LC_GameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

ALC_PlayerController::ALC_PlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ALC_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void ALC_PlayerController::AutoRun()
{
	if (bAutoRunning)
	{
		if (APawn* ControlledPawn = GetPawn())
		{
			FVector SplineLocation = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
			FVector SplineDirection = Spline->FindDirectionClosestToWorldLocation(SplineLocation, ESplineCoordinateSpace::World);
			ControlledPawn->AddMovementInput(SplineDirection);

			const float DistanceToDistanation = (SplineLocation - CachedDestination).Length();
			if (DistanceToDistanation < AutoRunAcceptanceRadius)
			{
				bAutoRunning = false;
			}
		}
	}
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

	ULC_EnhancedInputComponent* EnhancedInputComponent = CastChecked<ULC_EnhancedInputComponent>(InputComponent);

	//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALC_PlayerController::Move);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Triggered, this, &ALC_PlayerController::ShiftPresssed);
	EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ALC_PlayerController::ShiftReleased);
	EnhancedInputComponent->BindAbilityActions(InputDataAsset, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

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
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IHoverInterface>(CursorHit.GetActor());

	if (LastActor != CurrentActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (CurrentActor) CurrentActor->HighlightActor();
	}
	
}

void ALC_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FLC_GameplayTags::Get().InputTag_LMB))
	{
		bTargeting = CurrentActor ? true : false;
		bAutoRunning = false;
	}
}

void ALC_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FLC_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC() == nullptr) return;
		GetASC()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		if (bTargeting)
		{
			if (GetASC() == nullptr) return;
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		else
		{
			APawn* ControlledPawn = GetPawn();
			if (RunningTime <= ShortClickThreshold && ControlledPawn)
			{
					if (UNavigationPath* NaviPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
					{
						Spline->ClearSplinePoints();
						for (const FVector& VectorPoint : NaviPath->PathPoints)
						{
							Spline->AddSplinePoint(VectorPoint,ESplineCoordinateSpace::World);
						}
						CachedDestination = NaviPath->PathPoints[NaviPath->PathPoints.Num() - 1];
						bAutoRunning = true;
					}
			}
			bTargeting = false;
			RunningTime = 0.f;
		}
	}
}

void ALC_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FLC_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC() == nullptr) return;
		GetASC()->AbilityInputTagHeld(InputTag);
	}
	else 
	{
		if (!bTargeting && !bShiftPressed)
		{

			RunningTime = GetWorld()->GetDeltaSeconds();
			if (CursorHit.bBlockingHit)
			{
				CachedDestination = CursorHit.ImpactPoint;
				if (APawn* ControlledPawn = GetPawn())
				{
					const FVector MovementVector = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
					ControlledPawn->AddMovementInput(MovementVector);
				}
			}
		}
		else
		{
			if (GetASC() == nullptr) return;
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
}

ULC_AbilitySystemComponent* ALC_PlayerController::GetASC()
{
	if (LC_AbilitySystemComponent == nullptr)
	{
		LC_AbilitySystemComponent = Cast<ULC_AbilitySystemComponent>
			(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return LC_AbilitySystemComponent;
}


