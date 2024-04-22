// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnVolume();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Return WhereToSpawn
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// Return Random Point From WhereToSpawn
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	// Return Random Point From WhereToSpawn
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FRotator GetRandomRotator();

protected:
	// Spawn Pickup Actor
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf <class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	// Min spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MinSpawnDelay;

	// Max spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MaxSpawnDelay;

private:
	// Spawn Pickup Area
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	// Spawn New Pickup
	void SpawnPickup();

	// Current spawn delay
	float CurrentSpawnDelay;
};
