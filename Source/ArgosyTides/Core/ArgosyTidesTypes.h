// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArgosyTidesTypes.generated.h"

/** Game Era - Historical periods available in the game */
UENUM(BlueprintType)
enum class EGameEra : uint8
{
	Modern          UMETA(DisplayName = "Modern Era (2024+)"),
	AgeOfSail       UMETA(DisplayName = "Age of Sail (1650-1850)"),
	SteamEra        UMETA(DisplayName = "Steam Era (1850-1950)"),
	GlobalHistorical UMETA(DisplayName = "Global Historical Expeditions (B.C.-1600)"),
	Custom          UMETA(DisplayName = "Custom Scenario")
};

/** Visual Style - Different rendering modes */
UENUM(BlueprintType)
enum class EVisualStyle : uint8
{
	TopDown         UMETA(DisplayName = "Top-Down (Classic Strategy)"),
	Isometric       UMETA(DisplayName = "Isometric (3D Fixed Camera)"),
	Full3D          UMETA(DisplayName = "Full 3D (Cinematic)"),
	PaperMap        UMETA(DisplayName = "Paper Map (Nautical Chart)"),
	DataDashboard   UMETA(DisplayName = "Data Dashboard"),
	Cinematic       UMETA(DisplayName = "Cinematic (Immersive)")
};

/** Commodity Price Data */
USTRUCT(BlueprintType)
struct FCommodityPrice
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	FString CommodityId;

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	FString PortId;

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	double Price;

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	FString Currency;

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	FString Unit;

	UPROPERTY(BlueprintReadWrite, Category = "Market")
	FDateTime LastUpdated;
};

/** Weather Forecast Data */
USTRUCT(BlueprintType)
struct FWeatherForecast
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	float Latitude;

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	float Longitude;

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	FDateTime ForecastTime;

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	float WindSpeed; // m/s

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	float WaveHeight; // meters

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	float Visibility; // meters

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	bool bIsStorm;

	UPROPERTY(BlueprintReadWrite, Category = "Weather")
	FString Conditions; // "Clear", "Rain", "Storm", etc.
};

/** Port Information */
USTRUCT(BlueprintType)
struct FPortInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	FString PortId;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	FString Name;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	FString Country;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	float Latitude;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	float Longitude;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	int32 MaxShipSize; // Maximum ship capacity in tons

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	TArray<FString> AvailableCommodities;

	UPROPERTY(BlueprintReadWrite, Category = "Port")
	TArray<FString> Services; // "Refuel", "Repair", "Shipyard", etc.
};

/** Captain Data */
USTRUCT(BlueprintType)
struct FCaptainData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	FString CaptainId;

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	FString Name;

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	FString Portrait;

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	FString Personality; // "Cautious", "Aggressive", "Charismatic", "Greedy"

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 NavigationSkill; // 0-5

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 CombatSkill; // 0-5

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 TradeSkill; // 0-5

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 LeadershipSkill; // 0-5

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 Loyalty; // 0-100

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	int32 Courage; // 0-100

	UPROPERTY(BlueprintReadWrite, Category = "Captain")
	FString Backstory;
};
