// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "GameFramework/PawnMovementComponent.h"

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

	// find all SpawnVolume actors.
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

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
		playerCharacter->ChangePower(powerChange);
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
	HandleNewState(state);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState state)
{
	switch (state)
	{
	case EBatteryPlayState::EPlaying:
	{
		// spawn volumes active
		for (ASpawnVolume* volume : SpawnVolumeActors)
		{
			volume->SetSpawningActive(true);
		}
		break;
	}
	case EBatteryPlayState::EWin:
	{
		// spawn volumes inactive
		for (ASpawnVolume* volume : SpawnVolumeActors)
		{
			volume->SetSpawningActive(false);
		}
		break;
	}
	case EBatteryPlayState::EGameOver:
	{
		// spawn volumes inactive
		for (ASpawnVolume* volume : SpawnVolumeActors)
		{
			volume->SetSpawningActive(false);
		}
		// disable input player
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		if (playerController)
		{
			playerController->SetCinematicMode(true, false, false, true, true);
		}
		// break ragdoll player
		ACharacter* character = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (character)
		{
			character->GetMesh()->SetSimulatePhysics(true);
			character->GetMovementComponent()->MovementState.bCanJump = false;
		}
		break;
	}
	case EBatteryPlayState::EUnknown:
		break;
	}
}
