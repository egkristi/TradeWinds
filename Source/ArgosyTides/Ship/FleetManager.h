// Copyright 2026 Argosy Tides. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ship.h"
#include "FleetManager.generated.h"

/**
 * Fleet Manager - Manages player's ships and fleet operations
 */
UCLASS()
class ARGOSYTIDES_API UFleetManager : public UObject
{
	GENERATED_BODY()

public:
	UFleetManager();

	/** Initialize fleet manager */
	UFUNCTION(BlueprintCallable, Category = "Fleet")
	void Initialize();

	/** Cleanup fleet manager */
	UFUNCTION(BlueprintCallable, Category = "Fleet")
	void Cleanup();

	/** Create starter fleet for new game */
	UFUNCTION(BlueprintCallable, Category = "Fleet")
	void CreateStarterFleet();

	/** Add ship to fleet */
	UFUNCTION(BlueprintCallable, Category = "Fleet")
	void AddShip(UShip* NewShip);

	/** Remove ship from fleet */
	UFUNCTION(BlueprintCallable, Category = "Fleet")
	void RemoveShip(UShip* Ship);

	/** Get all ships in fleet */
	UFUNCTION(BlueprintPure, Category = "Fleet")
	TArray<UShip*> GetAllShips() const;

	/** Get ship by ID */
	UFUNCTION(BlueprintPure, Category = "Fleet")
	UShip* GetShipById(const FString& ShipId) const;

	/** Get total fleet value */
	UFUNCTION(BlueprintPure, Category = "Fleet")
	double GetFleetValue() const;

	/** Get number of ships */
	UFUNCTION(BlueprintPure, Category = "Fleet")
	int32 GetShipCount() const;

protected:
	/** Generate unique ship ID */
	FString GenerateShipId();

public:
	/** All ships in the fleet */
	UPROPERTY()
	TArray<UShip*> FleetShips;

	/** Next ship ID counter */
	UPROPERTY()
	int32 NextShipId;
};
