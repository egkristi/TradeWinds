// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArgosyTidesGameInstance.generated.h"

// Forward declarations
class UDataManager;
class UWeatherSystem;
class UFleetManager;

/**
 * Main Game Instance for Argosy Tides
 * Manages game state, data systems, and persistent information across levels
 */
UCLASS()
class ARGOSYTIDES_API UArgosyTidesGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UArgosyTidesGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	/** Called when game starts */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartNewGame();

	/** Called when loading a saved game */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void LoadGame();

	/** Save current game state */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void SaveGame();

protected:
	/** Initialize all game systems */
	void InitializeGameSystems();

	/** Cleanup game systems */
	void CleanupGameSystems();

public:
	/** Data manager for market, weather, and port data */
	UPROPERTY(BlueprintReadOnly, Category = "Systems")
	UDataManager* DataManager;

	/** Weather system for real-time marine forecasts */
	UPROPERTY(BlueprintReadOnly, Category = "Systems")
	UWeatherSystem* WeatherSystem;

	/** Player's fleet manager */
	UPROPERTY(BlueprintReadOnly, Category = "Systems")
	UFleetManager* PlayerFleet;

	/** Current game era (Modern, Age of Sail, etc.) */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	TEnumAsByte<EGameEra> CurrentEra;

	/** Current visual style */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	TEnumAsByte<EVisualStyle> VisualStyle;

	/** Game speed multiplier (1.0 = real-time, 0.0 = turn-based) */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float GameSpeed;

	/** Current in-game date */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	FDateTime GameDate;

	/** Player's company name */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	FString CompanyName;

	/** Player's net worth */
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	double NetWorth;
};
