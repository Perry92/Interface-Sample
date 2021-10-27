// Fergus Marsden 2020

#pragma once

#include <CoreMinimal.h>
#include <UObject/Interface.h>
#include "FJMDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UFJMDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/** This interface is used to communicate between a projectile object that can inflict damage and any character that can take damage.
 * 
 */
class WORLDWARTWO_API IFJMDamageInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//called when a projectile has hit an actor that can be damaged
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void ReceiveDamage(float MinDamage, float MaxDamage, float CritChance, const FHitResult & Hit, AActor* DamageInstigator, AFJMBaseBullet* Projectile = nullptr);

	//called when an explosive projectile has hit an actor that can be damaged
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TakeExplosionDamage(float ExplosionForce, FVector ExplosionPos, float CritChance, AActor* DamageInstigator);

	//called when a projectile has narrowly missed a character that can be damaged.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TakeSupressingFire(AActor* FiringActor);

	//called when a projectile has Hit Nearby to a character.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AlertToNearbyFire(AActor* FiringActor);

	//called when a hit character has been killed
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnSoldierKilled();

};
