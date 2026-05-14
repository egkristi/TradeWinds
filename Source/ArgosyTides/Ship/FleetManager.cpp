// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "FleetManager.h"
#include "Ship.h"

UFleetManager::UFleetManager()
	: NextShipId(1)
{
}

void UFleetManager::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("FleetManager: Initializing..."));
	
	NextShipId = 1;
	FleetShips.Empty();
	
	UE_LOG(LogTemp, Log, TEXT("FleetManager: Initialized"));
}

void UFleetManager::Cleanup()
{
	UE_LOG(LogTemp, Log, TEXT("FleetManager: Cleaning up..."));
	
	// Clean up all ships
	for (UShip* Ship : FleetShips)
	{
		if (Ship)
		{
			Ship->Cleanup();
			Ship->MarkPendingKill();
		}
	}
	
	FleetShips.Empty();
}

void UFleetManager::CreateStarterFleet()
{
	UE_LOG(LogTemp, Log, TEXT("FleetManager: Creating starter fleet"));
	
	// Create one starter ship (Panamax container ship)
	UShip* StarterShip = NewObject<UShip>(this);
	StarterShip->Initialize();
	StarterShip->ShipName = TEXT("Argosy I");
	StarterShip->ShipClass = TEXT("Panamax");
	StarterShip->bIsPlayerOwned = true;
	
	AddShip(StarterShip);
	
	UE_LOG(LogTemp, Log, TEXT("FleetManager: Starter fleet created with 1 ship"));
}

void UFleetManager::AddShip(UShip* NewShip)
{
	if (NewShip)
	{
		if (NewShip->ShipId.IsEmpty())
		{
			NewShip->ShipId = GenerateShipId();
		}
		
		FleetShips.Add(NewShip);
		
		UE_LOG(LogTemp, Log, TEXT("FleetManager: Added ship '%s' (%s)"), 
			*NewShip->ShipName, *NewShip->ShipId);
	}
}

void UFleetManager::RemoveShip(UShip* Ship)
{
	if (Ship)
	{
		FleetShips.Remove(Ship);
		
		UE_LOG(LogTemp, Log, TEXT("FleetManager: Removed ship '%s'"), *Ship->ShipName);
		
		Ship->Cleanup();
		Ship->MarkPendingKill();
	}
}

TArray<UShip*> UFleetManager::GetAllShips() const
{
	return FleetShips;
}

UShip* UFleetManager::GetShipById(const FString& ShipId) const
{
	for (UShip* Ship : FleetShips)
	{
		if (Ship && Ship->ShipId == ShipId)
		{
			return Ship;
		}
	}
	
	return nullptr;
}

double UFleetManager::GetFleetValue() const
{
	double TotalValue = 0.0;
	
	for (const UShip* Ship : FleetShips)
	{
		if (Ship)
		{
			TotalValue += Ship->CurrentValue;
		}
	}
	
	return TotalValue;
}

int32 UFleetManager::GetShipCount() const
{
	return FleetShips.Num();
}

FString UFleetManager::GenerateShipId()
{
	return FString::Printf(TEXT("SHIP_%04d"), NextShipId++);
}
