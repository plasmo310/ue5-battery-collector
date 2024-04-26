// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// enable tick function.
	PrimaryActorTick.bCanEverTick = true;
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	// set playing state.
	SetCurrentState(EBatteryPlayState::EPlaying);

	// create widget.
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCurrentState() != EBatteryPlayState::EPlaying)
	{
		return;
	}

	// get player character.
	auto playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	ABatteryCollectorCharacter* playerCharacter = Cast<ABatteryCollectorCharacter>(playerPawn);

	if (!playerCharacter)
	{
		return;
	}

	// check player power
	if (playerCharacter->GetCurrentPower() > PowerToWin)
	{
		SetCurrentState(EBatteryPlayState::EWin);
	}
	else if (playerCharacter->GetCurrentPower() > 0)
	{
		auto powerChange = -DeltaTime * DecayRate * (playerCharacter->GetInitialPower());
		playerCharacter->UpdatePower(powerChange);
	}
	else
	{
		SetCurrentState(EBatteryPlayState::EGameOver);
	}
}

float ABatteryCollectorGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState state)
{
	CurrentState = state;
}
