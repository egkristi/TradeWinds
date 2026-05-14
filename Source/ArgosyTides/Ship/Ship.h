// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ship.generated.h"

/**
 * Ship class - Represents a single vessel in the player's fleet
 */
UCLASS()
class ARGOSYTIDES_API UShip : public UObject
{
	GENERATED_BODY()

public:
	UShip();

	/** Initialize ship */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void Initialize();

	/** Cleanup ship */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void Cleanup();

	/** Load cargo onto ship */
	UFUNCTION(BlueprintCallable, Category = "Cargo")
	bool LoadCargo(const FString& CommodityId, int32 Amount);

	/** Unload cargo from ship */
	UFUNCTION(BlueprintCallable, Category = "Cargo")
	bool UnloadCargo(const FString& CommodityId, int32 Amount);

	/** Get current cargo amount */
	UFUNCTION(BlueprintPure, Category = "Cargo")
	int32 GetCargoAmount(const FString& CommodityId) const;

	/** Get total cargo weight */
	UFUNCTION(BlueprintPure, Category = "Cargo")
	int32 GetTotalCargoWeight() const;

	/** Check if ship can hold more cargo */
	UFUNCTION(BlueprintPure, Category = "Cargo")
	bool HasCargoCapacity(int32 Weight) const;

	/** Get available cargo capacity */
	UFUNCTION(BlueprintPure, Category = "Cargo")
	int32 GetAvailableCapacity() const;

public:
	/** Unique ship identifier */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	FString ShipId;

	/** Ship name (player-chosen) */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	FString ShipName;

	/** Ship class/type (e.g., "Panamax", "Capesize") */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	FString ShipClass;

	/** Whether this ship is owned by the player */
	UPROPERTY(BlueprintReadWrite, Category = "Identity")
	bool bIsPlayerOwned;

	/** Maximum cargo capacity in tons */
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	int32 MaxCargoCapacity;

	/** Current speed in knots */
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float MaxSpeed;

	/** Fuel consumption rate */
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float FuelConsumption;

	/** Current fuel level (0-100) */
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float CurrentFuel;

	/** Ship's current value */
	UPROPERTY(BlueprintReadWrite, Category = "Economy")
	double CurrentValue;

	/** Purchase price */
	UPROPERTY(BlueprintReadWrite, Category = "Economy")
	double PurchasePrice;

	/** Current location (port ID or coordinates) */
	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	FString CurrentLocation;

	/** Current cargo manifest */
	UPROPERTY()
	TMap<FString, int32> CargoManifest;

	/** Current cargo weight */
	UPROPERTY()
	int32 CurrentCargoWeight;
};
