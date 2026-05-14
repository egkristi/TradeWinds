// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Port.generated.h"

/**
 * Port class - Represents a trading port with market, shipyard, and services
 */
UCLASS()
class ARGOSYTIDES_API UPort : public UObject
{
	GENERATED_BODY()

public:
	UPort();

	/** Initialize port */
	UFUNCTION(BlueprintCallable, Category = "Port")
	void Initialize();

	/** Cleanup port */
	UFUNCTION(BlueprintCallable, Category = "Port")
	void Cleanup();

	/** Get commodity price */
	UFUNCTION(BlueprintPure, Category = "Market")
	float GetCommodityPrice(const FString& CommodityId) const;

	/** Buy commodity from port */
	UFUNCTION(BlueprintCallable, Category = "Market")
	bool BuyCommodity(const FString& CommodityId, int32 Amount, float& TotalCost);

	/** Sell commodity to port */
	UFUNCTION(BlueprintCallable, Category = "Market")
	bool SellCommodity(const FString& CommodityId, int32 Amount, float& TotalRevenue);

	/** Get available ship classes */
	UFUNCTION(BlueprintPure, Category = "Shipyard")
	TArray<FString> GetAvailableShipClasses() const;

	/** Buy ship from shipyard */
	UFUNCTION(BlueprintCallable, Category = "Shipyard")
	class UShip* BuyShip(const FString& ShipClass);

	/** Sell ship to shipyard */
	UFUNCTION(BlueprintCallable, Category = "Shipyard")
	bool SellShip(class UShip* Ship, float& SalePrice);

	/** Refuel ship */
	UFUNCTION(BlueprintCallable, Category = "Services")
	bool RefuelShip(class UShip* Ship, float FuelAmount);

	/** Repair ship */
	UFUNCTION(BlueprintCallable, Category = "Services")
	bool RepairShip(class UShip* Ship);

public:
	/** Unique port identifier */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	FString PortId;

	/** Port name */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	FString PortName;

	/** Port location (latitude, longitude) */
	UPROPERTY(BlueprintReadWrite, Category = "Location")
	FVector2D Location;

	/** Port country */
	UPROPERTY(BlueprintReadWrite, Category = "Location")
	FString Country;

	/** Commodity prices (ID -> price per ton) */
	UPROPERTY(BlueprintReadOnly, Category = "Market")
	TMap<FString, float> CommodityPrices;

	/** Available ship classes at this port */
	UPROPERTY(BlueprintReadOnly, Category = "Shipyard")
	TArray<FString> AvailableShipClasses;

	/** Fuel price per ton */
	UPROPERTY(BlueprintReadWrite, Category = "Services")
	float FuelPrice;

	/** Repair cost per damage point */
	UPROPERTY(BlueprintReadWrite, Category = "Services")
	float RepairCost;
};