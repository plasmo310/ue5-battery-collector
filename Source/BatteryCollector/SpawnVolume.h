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

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Returns WhereToSpawn */
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	/** Returns Random Point From WhereToSpawn */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	/** Returns Random Point From WhereToSpawn */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FRotator GetRandomRotator();

	/** Set Active */
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawningActive(bool isShouldSpawn);

protected:
	/** Spawn Pickup Actor */
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf <class APickup> WhatToSpawn;

	/** Spawn TimerHandle */
	FTimerHandle SpawnTimer;

	/** Min spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MinSpawnDelay;

	/** Max spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MaxSpawnDelay;

private:
	/** Spawn Pickup Area */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	/** Spawn New Pickup */
	void SpawnPickup();

	/** Current spawn delay */
	float CurrentSpawnDelay;
};
