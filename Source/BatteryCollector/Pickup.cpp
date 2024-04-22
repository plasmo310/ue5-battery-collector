// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

APickup::APickup()
{
 	// Disable Tick function.
	PrimaryActorTick.bCanEverTick = false;

	// pickup start active
	bIsActive = true;

	// Create the static mesh.
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::WasCollected_Implementation()
{
	// print debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}