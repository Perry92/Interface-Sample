// Copyright Fergus Marsden 2021

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "FJMCoverInterface.generated.h"

class UFJMInteriorCoverComponent;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UFJMCoverInterface : public UInterface
{
	GENERATED_BODY()

};

/** This interface is used to communicate between a coveer object and a human character that can use cover.
 * It will tell the character when they are able to take cover and when in cover, it will tell them if they are at the end.
 */
class WORLDWARTWO_API IFJMCoverInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*Called when cover has been found or lost, used to tell a character that cover is available.
	*IsAvailable: Whether cover is availble or not
	*CoverRotation: The direction of the cover found*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void CoverFound(bool IsAvailable, FRotator CoverRotation, UFJMInteriorCoverComponent* CoverComp);

	/*called when the character occupies an end cover position.
	*IsLeft: is at the left hand end
	*IsRight: is at the right hand end*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AtCoverEnd(bool right, bool left);

	//Getter to check if IF user is at right end of cover.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	bool GetAtCoverRightEnd();

	//Getter to check if IF user is at left end of cover.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	bool GetAtCoverLeftEnd();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetAtCoverRightEnd(bool NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetAtCoverLeftEnd(bool NewValue);

};
