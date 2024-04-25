// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

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

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// get player character.
	auto playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	ABatteryCollectorCharacter* playerCharacter = Cast<ABatteryCollectorCharacter>(playerPawn);

	// update player power.
	if (playerCharacter && playerCharacter->GetCurrentPower() > 0)
	{
		auto powerChange = -DeltaTime * DecayRate * (playerCharacter->GetInitialPower());
		playerCharacter->UpdatePower(powerChange);
	}
}
