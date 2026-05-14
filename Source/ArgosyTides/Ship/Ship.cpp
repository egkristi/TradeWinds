// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "Ship.h"

UShip::UShip()
	: bIsPlayerOwned(true)
	, MaxCargoCapacity(50000) // 50,000 tons default
	, MaxSpeed(24.0f) // 24 knots
	, FuelConsumption(50.0f) // tons per day
	, CurrentFuel(100.0f)
	, CurrentValue(50000000.0) // $50 million
	, PurchasePrice(50000000.0)
	, CurrentLocation(TEXT(""))
	, CurrentCargoWeight(0)
{
}

void UShip::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("Ship: Initializing '%s'"), *ShipName);
	
	CurrentFuel = 100.0f;
	CurrentCargoWeight = 0;
	CargoManifest.Empty();
}

void UShip::Cleanup()
{
	UE_LOG(LogTemp, Log, TEXT("Ship: Cleaning up '%s'"), *ShipName);
	
	CargoManifest.Empty();
}

bool UShip::LoadCargo(const FString& CommodityId, int32 Amount)
{
	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship: Cannot load negative or zero cargo"));
		return false;
	}
	
	if (!HasCargoCapacity(Amount))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship: Not enough capacity for %d tons of %s"), 
			Amount, *CommodityId);
		return false;
	}
	
	// Add to manifest
	if (CargoManifest.Contains(CommodityId))
	{
		CargoManifest[CommodityId] += Amount;
	}
	else
	{
		CargoManifest.Add(CommodityId, Amount);
	}
	
	CurrentCargoWeight += Amount;
	
	UE_LOG(LogTemp, Log, TEXT("Ship: Loaded %d tons of %s. Total cargo: %d/%d"),
		Amount, *CommodityId, CurrentCargoWeight, MaxCargoCapacity);
	
	return true;
}

bool UShip::UnloadCargo(const FString& CommodityId, int32 Amount)
{
	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship: Cannot unload negative or zero cargo"));
		return false;
	}
	
	if (!CargoManifest.Contains(CommodityId))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship: No %s in cargo hold"), *CommodityId);
		return false;
	}
	
	int32 CurrentAmount = CargoManifest[CommodityId];
	if (Amount > CurrentAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship: Cannot unload %d tons, only %d tons available"),
			Amount, CurrentAmount);
		return false;
	}
	
	// Remove from manifest
	CargoManifest[CommodityId] -= Amount;
	if (CargoManifest[CommodityId] <= 0)
	{
		CargoManifest.Remove(CommodityId);
	}
	
	CurrentCargoWeight -= Amount;
	
	UE_LOG(LogTemp, Log, TEXT("Ship: Unloaded %d tons of %s. Remaining cargo: %d/%d"),
		Amount, *CommodityId, CurrentCargoWeight, MaxCargoCapacity);
	
	return true;
}

int32 UShip::GetCargoAmount(const FString& CommodityId) const
{
	if (CargoManifest.Contains(CommodityId))
	{
		return CargoManifest.FindRef(CommodityId);
	}
	
	return 0;
}

int32 UShip::GetTotalCargoWeight() const
{
	return CurrentCargoWeight;
}

bool UShip::HasCargoCapacity(int32 Weight) const
{
	return (CurrentCargoWeight + Weight) <= MaxCargoCapacity;
}

int32 UShip::GetAvailableCapacity() const
{
	return MaxCargoCapacity - CurrentCargoWeight;
}
