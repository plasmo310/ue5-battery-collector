// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	// create the BoxComponent.
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	// set spawn = 1.0f;
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

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// get random point from WhereToSpawn.
	const FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	const FVector SpawnExtend = WhereToSpawn->Bounds.BoxExtent;
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

void ASpawnVolume::SetSpawningActive(const bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		// start spawn pickup.
		CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
	}
	else
	{
		// clear timer.
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn == nullptr)
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	// spawn settings.
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// spawn pickup.
	const FVector SpawnLocation = GetRandomPointInVolume();
	const FRotator SpawnRotation = GetRandomRotator();
	World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	// next loop spawn pickup.
	CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
}
