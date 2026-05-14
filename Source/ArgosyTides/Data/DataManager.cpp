// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "DataManager.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"

UDataManager::UDataManager()
	: bUseLiveData(false)
	, LastUpdateTime(FDateTime::MinValue())
{
}

void UDataManager::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("DataManager: Initializing..."));
	
	// Set up cache directory
	CacheDirectory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DataCache"));
	IFileManager::Get().MakeDirectory(*CacheDirectory, true);
	
	// Load cached data
	LoadCachedData();
	
	UE_LOG(LogTemp, Log, TEXT("DataManager: Initialized. Cache dir: %s"), *CacheDirectory);
}

void UDataManager::Cleanup()
{
	UE_LOG(LogTemp, Log, TEXT("DataManager: Cleaning up..."));
	
	// Save cached data before shutdown
	SaveCachedData();
	
	CommodityCache.Empty();
	PortCache.Empty();
}

FCommodityPrice UDataManager::GetCommodityPrice(const FString& CommodityId, const FString& PortId)
{
	// TODO: Implement proper price calculation with local simulation
	// For now, return cached or default price
	
	if (CommodityCache.Contains(CommodityId))
	{
		return CommodityPrice[CommodityId];
	}
	
	// Return default price if not cached
	FCommodityPrice DefaultPrice;
	DefaultPrice.CommodityId = CommodityId;
	DefaultPrice.PortId = PortId;
	DefaultPrice.Price = 100.0; // Default base price
	DefaultPrice.Currency = TEXT("USD");
	DefaultPrice.Unit = TEXT("ton");
	DefaultPrice.LastUpdated = FDateTime::Now();
	
	return DefaultPrice;
}

TArray<FCommodityPrice> UDataManager::GetPriceHistory(const FString& CommodityId, int32 Days)
{
	// TODO: Implement historical price data
	TArray<FCommodityPrice> History;
	
	// Placeholder - return empty array
	return History;
}

FWeatherForecast UDataManager::GetForecast(float Latitude, float Longitude, int32 HoursAhead)
{
	// TODO: Implement weather forecast from Open-Meteo
	FWeatherForecast Forecast;
	Forecast.Latitude = Latitude;
	Forecast.Longitude = Longitude;
	Forecast.ForecastTime = FDateTime::Now() + FTimespan::FromHours(HoursAhead);
	
	// Default calm weather
	Forecast.WindSpeed = 5.0; // m/s
	Forecast.WaveHeight = 1.0; // meters
	Forecast.Visibility = 10000.0; // meters
	Forecast.bIsStorm = false;
	
	return Forecast;
}

FPortInfo UDataManager::GetPortInfo(const FString& PortId)
{
	if (PortCache.Contains(PortId))
	{
		return PortCache[PortId];
	}
	
	// Return default port info
	FPortInfo Info;
	Info.PortId = PortId;
	Info.Name = TEXT("Unknown Port");
	Info.Country = TEXT("Unknown");
	Info.Latitude = 0.0;
	Info.Longitude = 0.0;
	
	return Info;
}

bool UDataManager::IsOnlineDataAvailable() const
{
	// TODO: Implement actual connectivity check
	return bUseLiveData;
}

void UDataManager::SetUseLiveData(bool bUseLive)
{
	bUseLiveData = bUseLive;
	
	if (bUseLiveData)
	{
		UE_LOG(LogTemp, Log, TEXT("DataManager: Switched to LIVE data mode"));
		FetchCommodityPrices();
		FetchWeatherData();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("DataManager: Switched to CACHED data mode"));
	}
}

void UDataManager::FetchCommodityPrices()
{
	// TODO: Implement Rust data pipeline integration
	// For now, just log that we would fetch data
	UE_LOG(LogTemp, Log, TEXT("DataManager: Would fetch commodity prices from World Bank API"));
}

void UDataManager::FetchWeatherData()
{
	// TODO: Implement Open-Meteo integration
	UE_LOG(LogTemp, Log, TEXT("DataManager: Would fetch weather data from Open-Meteo"));
}

void UDataManager::LoadCachedData()
{
	// TODO: Implement SQLite loading
	UE_LOG(LogTemp, Log, TEXT("DataManager: Loading cached data from disk"));
}

void UDataManager::SaveCachedData()
{
	// TODO: Implement SQLite saving
	UE_LOG(LogTemp, Log, TEXT("DataManager: Saving cached data to disk"));
}
