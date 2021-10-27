// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "FJMTurretInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFJMTurretInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WORLDWARTWO_API IFJMTurretInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//interface call for when an actor using this IF is in range of a turret.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TurretFound(bool IsAvailable, FRotator TurretRotation, FVector TurretLocation, class AFJMBaseTurret* Turret);

};