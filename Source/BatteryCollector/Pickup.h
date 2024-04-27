// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Pickup.generated.h"


UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Returns mesh for pickup */
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	/** Returns pickup is active */
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/** Set pickup active */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	/** When the pickup is collected event */
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

protected:
	/** Flag pickup active */
	bool bIsActive;

private:
	/** Static mesh for pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent* PickupMesh;
};
