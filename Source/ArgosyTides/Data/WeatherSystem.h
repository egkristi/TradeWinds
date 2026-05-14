// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeatherSystem.generated.h"

/**
 * Weather System - Manages real-time weather simulation
 * Integrates with Open-Meteo for real marine forecasts
 */
UCLASS()
class ARGOSYTIDES_API UWeatherSystem : public UObject
{
	GENERATED_BODY()

public:
	UWeatherSystem();

	/** Initialize weather system */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void Initialize();

	/** Cleanup weather system */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void Cleanup();

	/** Get current weather at location */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	FWeatherForecast GetCurrentWeather(float Latitude, float Longitude);

	/** Update weather for all active ships */
	UFUNCTION(BlueprintCallable, Category = "Weather")
	void UpdateWeather();

	/** Check if location has storm conditions */
	UFUNCTION(BlueprintPure, Category = "Weather")
	bool IsStormy(float Latitude, float Longitude) const;

protected:
	/** Fetch weather data from API */
	void FetchWeatherData();

	/** Interpolate weather between data points */
	FWeatherForecast InterpolateWeather(const FWeatherForecast& From, const FWeatherForecast& To, float Alpha);

public:
	/** Update interval in seconds */
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	float UpdateInterval;

	/** Last update time */
	UPROPERTY()
	FDateTime LastUpdateTime;

	/** Active weather regions */
	UPROPERTY()
	TMap<FString, FWeatherForecast> WeatherRegions;
};
