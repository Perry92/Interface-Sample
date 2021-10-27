// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "FJMDoorBreachInterface.generated.h"

class AFJMEntranceActor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFJMDoorBreachInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WORLDWARTWO_API IFJMDoorBreachInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//interface call for when an actor using this IF is in range of a Door.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void DoorFound(bool CanKick, AFJMEntranceActor* DoorwayActor);

};
