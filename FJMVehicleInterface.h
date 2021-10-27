// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "FJMVehicleInterface.generated.h"

class AFJMBaseVehicle;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFJMVehicleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WORLDWARTWO_API IFJMVehicleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//interface call for when an actor using this IF is in range of a vehicle.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void VehicleFound(uint8 SeatsRemaining, FRotator TurretRotation, FVector NearestSeatLocation, AFJMBaseVehicle* Vehicle);
};
