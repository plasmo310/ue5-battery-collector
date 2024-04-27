// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWin,
	EUnknown,
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Returns need power win the game */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	/** Returns current state */
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	/** Set playing state */
	void SetCurrentState(EBatteryPlayState state);

protected:
	/** Lose player power rate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate = 0.05f;

	/** Need power win the game */
	UPROPERTY(EditDefaultsOnly, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin = 3000.0f;

	/** The Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the Widget */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	/** Keeps track of the current playing state */
	EBatteryPlayState CurrentState;

	/** Spawn Volumes */
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/** handle change state */
	void HandleNewState(EBatteryPlayState state);

};
