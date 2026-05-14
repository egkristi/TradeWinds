// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "Port.h"
#include "Ship/Ship.h"

UPort::UPort()
	: PortId(TEXT(""))
	, PortName(TEXT(""))
	, Location(FVector2D::ZeroVector)
	, Country(TEXT(""))
	, FuelPrice(800.0f) // $800 per ton
	, RepairCost(1000.0f) // $1000 per damage point
{
}

void UPort::Initialize()
{
	UE_LOG(LogTemp, Log, TEXT("Port: Initializing '%s'"), *PortName);

	// Initialize default commodity prices
	CommodityPrices.Add(TEXT("grain"), 250.0f); // $250 per ton

	// Initialize available ship classes
	AvailableShipClasses.Add(TEXT("Panamax"));
}

void UPort::Cleanup()
{
	UE_LOG(LogTemp, Log, TEXT("Port: Cleaning up '%s'"), *PortName);

	CommodityPrices.Empty();
	AvailableShipClasses.Empty();
}

float UPort::GetCommodityPrice(const FString& CommodityId) const
{
	if (CommodityPrices.Contains(CommodityId))
	{
		return CommodityPrices.FindRef(CommodityId);
	}

	UE_LOG(LogTemp, Warning, TEXT("Port: Unknown commodity '%s'"), *CommodityId);
	return 0.0f;
}

bool UPort::BuyCommodity(const FString& CommodityId, int32 Amount, float& TotalCost)
{
	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot buy negative or zero amount"));
		return false;
	}

	float PricePerTon = GetCommodityPrice(CommodityId);
	if (PricePerTon <= 0.0f)
	{
		return false;
	}

	TotalCost = PricePerTon * Amount;

	UE_LOG(LogTemp, Log, TEXT("Port: Bought %d tons of %s for $%.2f"),
		Amount, *CommodityId, TotalCost);

	return true;
}

bool UPort::SellCommodity(const FString& CommodityId, int32 Amount, float& TotalRevenue)
{
	if (Amount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot sell negative or zero amount"));
		return false;
	}

	float PricePerTon = GetCommodityPrice(CommodityId);
	if (PricePerTon <= 0.0f)
	{
		return false;
	}

	TotalRevenue = PricePerTon * Amount;

	UE_LOG(LogTemp, Log, TEXT("Port: Sold %d tons of %s for $%.2f"),
		Amount, *CommodityId, TotalRevenue);

	return true;
}

TArray<FString> UPort::GetAvailableShipClasses() const
{
	return AvailableShipClasses;
}

UShip* UPort::BuyShip(const FString& ShipClass)
{
	if (!AvailableShipClasses.Contains(ShipClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Ship class '%s' not available"), *ShipClass);
		return nullptr;
	}

	UShip* NewShip = NewObject<UShip>(this);
	if (!NewShip)
	{
		UE_LOG(LogTemp, Error, TEXT("Port: Failed to create ship object"));
		return nullptr;
	}

	// Configure ship based on class
	if (ShipClass == TEXT("Panamax"))
	{
		NewShip->ShipClass = TEXT("Panamax");
		NewShip->MaxCargoCapacity = 80000; // 80,000 tons
		NewShip->MaxSpeed = 24.0f; // 24 knots
		NewShip->FuelConsumption = 60.0f; // tons per day
		NewShip->PurchasePrice = 80000000.0; // $80 million
		NewShip->CurrentValue = 80000000.0;
		NewShip->ShipName = FString::Printf(TEXT("Panamax %s"), *FString::FromInt(FMath::RandRange(100, 999)));
	}

	NewShip->ShipId = FGuid::NewGuid().ToString();
	NewShip->CurrentLocation = PortId;
	NewShip->Initialize();

	UE_LOG(LogTemp, Log, TEXT("Port: Sold new %s ship '%s' for $%.0f"),
		*ShipClass, *NewShip->ShipName, NewShip->PurchasePrice);

	return NewShip;
}

bool UPort::SellShip(UShip* Ship, float& SalePrice)
{
	if (!Ship)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot sell null ship"));
		return false;
	}

	// Calculate sale price (typically 70-80% of current value)
	SalePrice = Ship->CurrentValue * 0.75f;

	UE_LOG(LogTemp, Log, TEXT("Port: Bought ship '%s' for $%.0f"),
		*Ship->ShipName, SalePrice);

	return true;
}

bool UPort::RefuelShip(UShip* Ship, float FuelAmount)
{
	if (!Ship)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot refuel null ship"));
		return false;
	}

	if (FuelAmount <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot refuel with negative or zero amount"));
		return false;
	}

	float MaxFuel = 100.0f;
	float CurrentFuel = Ship->CurrentFuel;
	float NeededFuel = MaxFuel - CurrentFuel;

	if (FuelAmount > NeededFuel)
	{
		FuelAmount = NeededFuel;
	}

	float Cost = FuelAmount * FuelPrice;
	Ship->CurrentFuel += FuelAmount;

	UE_LOG(LogTemp, Log, TEXT("Port: Refueled ship '%s' with %.1f tons for $%.2f"),
		*Ship->ShipName, FuelAmount, Cost);

	return true;
}

bool UPort::RepairShip(UShip* Ship)
{
	if (!Ship)
	{
		UE_LOG(LogTemp, Warning, TEXT("Port: Cannot repair null ship"));
		return false;
	}

	// For now, assume ships don't have damage system
	// This is a placeholder for future implementation
	UE_LOG(LogTemp, Log, TEXT("Port: Repaired ship '%s'"), *Ship->ShipName);

	return true;
}