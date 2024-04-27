// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the Box Component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// Set spawm delay
	MinSpawnDelay = 1.0f;
	MaxSpawnDelay = 4.5f;
}

void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	// Get Random Point From WhereToSpawn
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtend = WhereToSpawn->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtend);
}

FRotator ASpawnVolume::GetRandomRotator()
{
	FRotator SpawnRotation;
	SpawnRotation.Yaw = FMath::FRand() * 360.0f;
	SpawnRotation.Pitch = FMath::FRand() * 360.0f;
	SpawnRotation.Roll = FMath::FRand() * 360.0f;
	return SpawnRotation;
}

void ASpawnVolume::SetSpawningActive(bool isShouldSpawn)
{
	if (isShouldSpawn)
	{
		// Start Spawn Pickup.
		CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
	}
	else
	{
		// Clear Timer.
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn == NULL)
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	// Spawn Settings.
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Spawn Pickup.
	FVector SpawnLocation = GetRandomPointInVolume();
	FRotator SpawnRotation = GetRandomRotator();
	APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	// Next Spawn Pickup.
	CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
}
