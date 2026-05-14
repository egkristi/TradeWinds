// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArgosyTidesTypes.h"
#include "DataManager.generated.h"

/**
 * Data Manager - Abstracts data access for the game
 * Handles real-world data fetching, caching, and offline fallback
 */
UCLASS()
class ARGOSYTIDES_API UDataManager : public UObject
{
	GENERATED_BODY()

public:
	UDataManager();

	/** Initialize data manager */
	UFUNCTION(BlueprintCallable, Category = "Data")
	void Initialize();

	/** Cleanup data manager */
	UFUNCTION(BlueprintCallable, Category = "Data")
	void Cleanup();

	/** Get commodity price for a specific port */
	UFUNCTION(BlueprintCallable, Category = "Market Data")
	FCommodityPrice GetCommodityPrice(const FString& CommodityId, const FString& PortId);

	/** Get historical price data */
	UFUNCTION(BlueprintCallable, Category = "Market Data")
	TArray<FCommodityPrice> GetPriceHistory(const FString& CommodityId, int32 Days);

	/** Get weather forecast */
	UFUNCTION(BlueprintCallable, Category = "Weather Data")
	FWeatherForecast GetForecast(float Latitude, float Longitude, int32 HoursAhead);

	/** Get port information */
	UFUNCTION(BlueprintCallable, Category = "Port Data")
	FPortInfo GetPortInfo(const FString& PortId);

	/** Check if online data is available */
	UFUNCTION(BlueprintPure, Category = "Data")
	bool IsOnlineDataAvailable() const;

	/** Toggle between live and cached data */
	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetUseLiveData(bool bUseLive);

protected:
	/** Fetch real-world commodity prices */
	void FetchCommodityPrices();

	/** Fetch weather data */
	void FetchWeatherData();

	/** Load cached data from disk */
	void LoadCachedData();

	/** Save data to cache */
	void SaveCachedData();

public:
	/** Whether to use live data or cached data */
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bUseLiveData;

	/** Cache directory path */
	UPROPERTY()
	FString CacheDirectory;

	/** Last data update time */
	UPROPERTY()
	FDateTime LastUpdateTime;

	/** Cached commodity data */
	UPROPERTY()
	TMap<FString, FCommodityPrice> CommodityCache;

	/** Cached port data */
	UPROPERTY()
	TMap<FString, FPortInfo> PortCache;
};
