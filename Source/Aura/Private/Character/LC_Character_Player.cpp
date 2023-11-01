// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LC_Character_Player.h"
#include "AbilitySystem/LC_AbilitySystemComponent.h"
#include "Player/LC_PlayerState.h"
#include "Player/LC_PlayerController.h"
#include "HUD/LC_HUD.h"
#include "GameFramework/CharacterMovementComponent.h"

ALC_Character_Player::ALC_Character_Player()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 45.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane= true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ALC_Character_Player::InitAbiltyActorInfo()
{
	ALC_PlayerState* GASPlayerState = GetPlayerState<ALC_PlayerState>();
	check(GASPlayerState);
	GASPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(GASPlayerState, this);
	Cast<ULC_AbilitySystemComponent>(GASPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = GASPlayerState->GetAbilitySystemComponent();
	AttributeSet = GASPlayerState->GetAttributeSet();

	if (ALC_PlayerController* PlayerCont = Cast<ALC_PlayerController>(GetController()))
	{
		ALC_HUD* GameHUD = Cast<ALC_HUD>(PlayerCont->GetHUD());
		GameHUD->InitOverlay(PlayerCont, GASPlayerState, AbilitySystemComponent, AttributeSet);
	}

	InitVitalAttributes();
	InitSecondaryAttributes();
	InitAttributes();
	//InitVitalAttributes();
}

int32 ALC_Character_Player::GetPlayerLevel()
{
	const ALC_PlayerState* GASPlayerState = GetPlayerState<ALC_PlayerState>();
	check(GASPlayerState);
	return GASPlayerState->GetPlayerLevel();
}


void ALC_Character_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbiltyActorInfo();
	GiveGameplayAbilities();
	
}

void ALC_Character_Player::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
	InitAbiltyActorInfo();
}


