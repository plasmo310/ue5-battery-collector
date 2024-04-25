// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

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

protected:
	/** lose player power rate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate = 0.05f;

	/** need power win the game */
	UPROPERTY(EditDefaultsOnly, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin = 3000.0f;

	/** The Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the Widget */
	UPROPERTY()
	class UUserWidget* CurrentWidget;

};
