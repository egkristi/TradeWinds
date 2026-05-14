// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "WeatherSystem.h"

UWeatherSystem::UWeatherSystem()
	: UpdateInterval(3600.0f) // Update every hour
	, LastUpdateTime(FDateTime::MinValue())
{
}

void UWeatherSystem::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("WeatherSystem: Initializing..."));
	
	// Initialize with default weather
	LastUpdateTime = FDateTime::Now();
	
	UE_LOG(LogTemp, Log, TEXT("WeatherSystem: Initialized"));
}

void UWeatherSystem::Cleanup()
{
	UE_LOG(LogTemp, Log, TEXT("WeatherSystem: Cleaning up..."));
	
	WeatherRegions.Empty();
}

FWeatherForecast UWeatherSystem::GetCurrentWeather(float Latitude, float Longitude)
{
	// TODO: Implement proper weather lookup
	FWeatherForecast Weather;
	Weather.Latitude = Latitude;
	Weather.Longitude = Longitude;
	Weather.ForecastTime = FDateTime::Now();
	
	// Default conditions
	Weather.WindSpeed = 5.0;
	Weather.WaveHeight = 1.0;
	Weather.Visibility = 10000.0;
	Weather.bIsStorm = false;
	
	return Weather;
}

void UWeatherSystem::UpdateWeather()
{
	FDateTime Now = FDateTime::Now();
	
	if ((Now - LastUpdateTime).GetTotalSeconds() >= UpdateInterval)
	{
		UE_LOG(LogTemp, Log, TEXT("WeatherSystem: Updating weather data"));
		FetchWeatherData();
		LastUpdateTime = Now;
	}
}

bool UWeatherSystem::IsStormy(float Latitude, float Longitude) const
{
	// TODO: Check actual weather data
	return false;
}

void UWeatherSystem::FetchWeatherData()
{
	// TODO: Integrate with Open-Meteo API
	UE_LOG(LogTemp, Log, TEXT("WeatherSystem: Would fetch weather from Open-Meteo"));
}

FWeatherForecast UWeatherSystem::InterpolateWeather(const FWeatherForecast& From, const FWeatherForecast& To, float Alpha)
{
	FWeatherForecast Result;
	
	Result.Latitude = FMath::Lerp(From.Latitude, To.Latitude, Alpha);
	Result.Longitude = FMath::Lerp(From.Longitude, To.Longitude, Alpha);
	Result.WindSpeed = FMath::Lerp(From.WindSpeed, To.WindSpeed, Alpha);
	Result.WaveHeight = FMath::Lerp(From.WaveHeight, To.WaveHeight, Alpha);
	Result.Visibility = FMath::Lerp(From.Visibility, To.Visibility, Alpha);
	Result.bIsStorm = From.bIsStorm || To.bIsStorm; // If either is stormy, result is stormy
	
	return Result;
}
