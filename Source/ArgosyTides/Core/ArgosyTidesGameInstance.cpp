// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "ArgosyTidesGameInstance.h"
#include "DataManager.h"
#include "WeatherSystem.h"
#include "FleetManager.h"
#include "Engine/AssetManager.h"

UArgosyTidesGameInstance::UArgosyTidesGameInstance()
	: DataManager(nullptr)
	, WeatherSystem(nullptr)
	, PlayerFleet(nullptr)
	, CurrentEra(0) // EGameEra::Modern
	, VisualStyle(0) // EVisualStyle::TopDown
	, GameSpeed(1.0f)
	, GameDate(FDateTime::Now())
	, CompanyName(TEXT("New Shipping Company"))
	, NetWorth(100000.0) // Starting capital
{
}

void UArgosyTidesGameInstance::Init()
{
	Super::Init();
	
	UE_LOG(LogTemp, Log, TEXT("ArgosyTidesGameInstance: Initializing..."));
	
	InitializeGameSystems();
}

void UArgosyTidesGameInstance::Shutdown()
{
	CleanupGameSystems();
	
	Super::Shutdown();
	
	UE_LOG(LogTemp, Log, TEXT("ArgosyTidesGameInstance: Shutdown complete"));
}

void UArgosyTidesGameInstance::InitializeGameSystems()
{
	UE_LOG(LogTemp, Log, TEXT("Initializing game systems..."));
	
	// Create data manager
	DataManager = NewObject<UDataManager>(this);
	DataManager->Initialize();
	
	// Create weather system
	WeatherSystem = NewObject<UWeatherSystem>(this);
	WeatherSystem->Initialize();
	
	// Create fleet manager
	PlayerFleet = NewObject<UFleetManager>(this);
	PlayerFleet->Initialize();
	
	UE_LOG(LogTemp, Log, TEXT("Game systems initialized successfully"));
}

void UArgosyTidesGameInstance::CleanupGameSystems()
{
	UE_LOG(LogTemp, Log, TEXT("Cleaning up game systems..."));
	
	if (PlayerFleet)
	{
		PlayerFleet->Cleanup();
	}
	
	if (WeatherSystem)
	{
		WeatherSystem->Cleanup();
	}
	
	if (DataManager)
	{
		DataManager->Cleanup();
	}
}

void UArgosyTidesGameInstance::StartNewGame()
{
	UE_LOG(LogTemp, Log, TEXT("Starting new game: %s"), *CompanyName);
	
	// Reset game state
	NetWorth = 100000.0;
	GameDate = FDateTime::Now();
	
	// Initialize player with starter ship
	PlayerFleet->CreateStarterFleet();
}

void UArgosyTidesGameInstance::LoadGame()
{
	UE_LOG(LogTemp, Log, TEXT("Loading saved game..."));
	
	// TODO: Implement save game loading
	// For now, just initialize systems
	InitializeGameSystems();
}

void UArgosyTidesGameInstance::SaveGame()
{
	UE_LOG(LogTemp, Log, TEXT("Saving game: %s - Net Worth: $%.2f"), *CompanyName, NetWorth);
	
	// TODO: Implement save game saving
	// Save current state to SQLite database
}
