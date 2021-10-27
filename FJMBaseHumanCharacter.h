// Copyright Fergus Marsden 2021

#pragma once

#include <CoreMinimal.h>
#include "WorldWarTwo/Characters/WW2BaseCharacter.h"
#include "WorldWarTwo/Interface/FJMCoverInterface.h"
#include "WorldWarTwo/Interface/FJMDamageInterface.h"
#include "WorldWarTwo/Interface/FJMTurretInterface.h"
#include "WorldWarTwo/Interface/FJMDoorBreachInterface.h"
#include "WorldWarTwo/Interface/FJMVehicleInterface.h"
#include <Components/SphereComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "WorldWarTwo/Library/FJMEnumerations.h"
#include "WorldWarTwo/Library/FJMStructs.h"
#include "FactionAgentInterface.h"
#include <Perception/AIPerceptionStimuliSourceComponent.h>
#include "WorldWarTwo/Components/Characters/WW2CharacterSupressionComponent.h"
#include "FJMBaseHumanCharacter.generated.h"

/*Forward declare dev made classes, avoids the possibility of circular dependancy*/
class UCoverPositionComponent;
class AFJMBaseWeapon;
class AFJMBaseThrownWeapon;
class AFJMBaseBuilding;
class UAudioComponent;
class UFJMHumanMontageComponent;
class UFJMCharacterAimingComponent;
class UFJMBuildingSearchComponent;
class AFJMBaseTurret;
class AFJMBaseVehicle;
class UFJMVehicleSeatComponent;
class AFJMBaseBullet;
class UFJMCharacterAppearenceData;
class AFJMEntranceActor;
class UFJMCharacterHealthComponent;

struct FFaction;

struct FTurretInfo
{
	AFJMBaseTurret* Turret;
	FVector UserLocation;
	FRotator UserRotation;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterDeath, AFJMBaseHumanCharacter*, DeadChar);

/** 
 */
UCLASS(BlueprintType)
class WORLDWARTWO_API AFJMBaseHumanCharacter : public AWW2BaseCharacter, public IFJMCoverInterface, public IFactionAgentInterface, public IFJMDamageInterface, public IFJMTurretInterface, public IFJMDoorBreachInterface, public IFJMVehicleInterface
{
	GENERATED_BODY()


	AFJMBaseHumanCharacter(const FObjectInitializer& ObjectInitializer);

/////////////////////////
//Components////////////
///////////////////////

	/*Class Default Components*/
	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Head = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Hair = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FacialHair = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Helmet = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Straps = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* FootstepAudio = nullptr;

	UPROPERTY(Category = Soldier, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFJMHumanMontageComponent* CharMontageManager = nullptr;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UFJMCharacterAppearenceComponent* CharAppearenceComp = nullptr;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFJMCharacterHealthComponent* CharacterHealthComp = nullptr;

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetHeadComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetHelmetComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		USkeletalMeshComponent* GetFacialHairComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetHairComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* GetStrapsComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UFJMHumanMontageComponent* GetMontageManager() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UFJMCharacterHealthComponent* GetCharHealthComp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UFJMCharacterAppearenceComponent * GetCharAppearenceComp() const;

/////////////////////////
/*Character and States*/
///////////////////////

public:

	UAudioComponent* GetFootstepAudio() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsPlayer() const;
	void SetIsPlayer(bool IsPlayer);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsAlert() const;
	void SetIsAlert(bool IsAlert);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsCrouching() const;
	void SetIsCrouching(bool IsCrouching);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsJumping() const;
	void SetIsJumping(bool IsJumping);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsFallingHigh() const;
	void SetIsFallingHigh(bool IsFallingHigh);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsProne() const;
	void SetIsProne(bool IsProne);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsWalking() const;
	void SetIsWalking(bool IsWalking);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsSprinting() const;
	void SetIsSprinting(bool IsSprinting);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsTurning() const;
	void SetIsTurning(bool IsTurning);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsDead() const;
	void SetIsDead(bool IsDead);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsIdling() const;
	void SetIsIdling(bool IsIdling);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMoveForwardAxis() const;
	void SetMoveForwardAxis(float NewAxis);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMoveRightAxis() const;
	void SetMoveRightAxis(float NewAxis);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetCharacterInBuilding(AFJMBaseBuilding*& OutBuilding);

	FName GetRightHandSocketName() const;
	FName GetGrenadeSocketName() const;
	FName GetUnequippedWeaponSocketName() const;
	FName GetLauncherSocketName() const;

	void BeginAlertPhase();
	void EndAlertPhase();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ESoldierClassType GetSoldierClass() const;

	UFUNCTION(BlueprintCallable)
	void SetSoldierClass(ESoldierClassType NewClass);

	/*Event Dispatcher Delegate to display crosshair*/
	UPROPERTY(BlueprintAssignable)
	FOnCharacterDeath OnCharacterDeath;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	ESoldierClassType SoldierClass = ESoldierClassType::NonCombat;

	/*Socket Names*/
	static FName RightHandSocket;
	static FName LauncherHandSocket;
	static FName WeaponMountSocket;
	static FName GrenadeSocket;
	static FName RightFootSocket;
	static FName UnequippedWeaponSocket;

	float MoveForwardAxis;
	float MoveRightAxis;

	/*is the character Dead*/
	bool bIsDead = false;

	/* Animation states used to control the flows within the anim graph.
	*/
	bool bIsCrouching = false;
	bool bIsJumping = false;
	bool bIsFallingHigh = false;
	bool bIsProne = false;
	bool bIsTurning = false;
	bool bIsWalking = false;
	bool bIsSprinting = false;
	bool bIsIdling = false;
	bool bIsAlert = false;

	FTimerHandle AlertTimer;
	float AlertTime = 10.f;
private:
	/*Used to determine if the character is controlled by a player, set in child Player Character*/
	bool bIsPlayer = false;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

////////////////////
/*Cover interface*/
//////////////////

public:
	/*The implementation for when we recive a call from the cover interface on cover found
	* sets the bISCoverAvailable and CoverRotation, for use when the character is trying to take cover.
	* all functionality is done in the _Implementation function, this is standard syntax for implemeting interface handlers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void CoverFound(bool IsAvailable, FRotator CoverRotation, UFJMInteriorCoverComponent* CoverComp);
	virtual void CoverFound_Implementation(bool IsAvailable, FRotator CoverRotation, UFJMInteriorCoverComponent* CoverComp) override;

	//Used when we need to know if the character is at the right side of cover.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	bool GetAtCoverRightEnd();
	virtual bool GetAtCoverRightEnd_Implementation() override;

	//Used when we need to know if the character is at the left side of cover.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	bool GetAtCoverLeftEnd();
	virtual bool GetAtCoverLeftEnd_Implementation() override;

	/*The implementation for when we recive a call from the cover interface when the characters reaches the right side of cover
	* ensures that the character is facing right and so can aim around the corner if needed.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetAtCoverRightEnd(bool NewValue);
	virtual void SetAtCoverRightEnd_Implementation(bool NewValue) override;

	/*The implementation for when we recive a call from the cover interface when the characters reaches the left side of cover
	* ensures that the character is facing left and so can aim around the corner if needed.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void SetAtCoverLeftEnd(bool NewValue);
	virtual void SetAtCoverLeftEnd_Implementation(bool NewValue) override;

	/*The implementation for when we recive a call from the cover interface when the characters reaches an end of cover
	* parameters will then set the character to be at the right end or left end.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AtCoverEnd(bool right, bool left);
	virtual void AtCoverEnd_Implementation(bool right, bool left) override;

/////////////////////
/*Turret interface*/
///////////////////

public:
	/*The implementation for when we recive a call from the turret interface on turret found
	* tells the character that a turret is available and if player then to show the apropriate UI.
	* all functionality is done in the _Implementation function, this is standard syntax for implemeting interface handlers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TurretFound(bool IsAvailable, FRotator TurretRotation, FVector TurretLocation, AFJMBaseTurret* Turret);
	virtual void TurretFound_Implementation(bool IsAvailable, FRotator TurretRotation, FVector TurretLocation, AFJMBaseTurret* Turret) override;

	virtual bool UseTurret();

	virtual bool LeaveTurret();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AFJMBaseTurret * GetUsedTurret();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsUsingTurret() const;
	void SetIsUsingTurret(bool IsUsingTurret);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsTurretAvailable() const;
	void SetIsTurretAvailable(bool IsAvailable);

	virtual bool CalculateGrenadeVelocity(float LaunchSpeed, FVector& OUTVelocity);
protected:
	bool bIsTurretAvailable = false;
	FTurretInfo OverlappedTurretInfo = FTurretInfo();

private:
	/*Is the character Using a Turret*/
	bool bIsUsingTurret = false;

	AFJMBaseTurret* UsedTurret = nullptr;

////////////////////
/*House interface*/
//////////////////

public:
	/*The implementation for when we recive a call from the Building interface on door found
	* tells the character that a door is in their way - it will allow them to break down or open the door depending on its current state.
	* all functionality is done in the _Implementation function, this is standard syntax for implemeting interface handlers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void DoorFound(bool CanKick, AFJMEntranceActor* DoorwayActor);
	virtual void DoorFound_Implementation(bool CanKick, AFJMEntranceActor* DoorwayActor) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsBreachingDoor() const;
	void SetIsBreachingDoor(bool NewValue);

	AFJMBaseBuilding* GetOccupiedBuilding() const;
	void SetOccupiedBuilding(AFJMBaseBuilding* Building);

	AFJMEntranceActor* GetBreachDoorway() const;
	void SetBreachDoorway(AFJMEntranceActor* Door);

	bool GetCanBreachDoorway() const;
	void SetCanBreachDoorway(bool NewValue);

	bool GetIsInHouse() const;
	void SetIsInHouse(bool IsInHouse);

private:
	/*Is the character currently inside of a building.*/
	bool bIsInHouse = false;

	/*The House this character currently occupies. Only Applicable when character is in a house.*/
	AFJMBaseBuilding* OccupiedBuilding = nullptr;

	bool bCanBreachDoorway = false;
	bool bIsBreachingDoor = false;

	AFJMEntranceActor* BreachDoorway = nullptr;

//////////////////////
/*Vehicle interface*/
////////////////////
	
public:
	/*The implementation for when we recive a call from the Vehicle interface on Vehicle found
	* tells the character that a vehicle is nearby, for friendly vehicles this will allow characters to enter the vehicle.
	* for enemy vehicles it will give the character the ability to plant demolition.
	* all functionality is done in the _Implementation function, this is standard syntax for implemeting interface handlers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void VehicleFound(uint8 SeatsRemaining, FRotator TurretRotation, FVector NearestSeatLocation, AFJMBaseVehicle* Turret);
	virtual void VehicleFound_Implementation(uint8 SeatsRemaining, FRotator TurretRotation, FVector NearestSeatLocation, AFJMBaseVehicle* Vehicle) override;

/////////////////////
/*Damage interface*/
///////////////////

public:
	/*The implementation for when we recive a call from the damage interface that the character has been hit and should recive damage
	* this will determine the amount of damage recived based on min and max damage and the critical chance.
	* all functionality is done in the _Implementation function, this is standard syntax for implemeting interface handlers.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void ReceiveDamage(float MinDamage, float MaxDamage, float CritChance, const FHitResult & Hit, AActor* DamageInstigator, AFJMBaseBullet* Projectile = nullptr);
	virtual void ReceiveDamage_Implementation(float MinDamage, float MaxDamage, float CritChance, const FHitResult & Hit, AActor* DamageInstigator, AFJMBaseBullet* Projectile = nullptr) override;

	/*The implementation for when we recive a call from the damage interface that an explosion has occured within range of this character
	* this will determine the amount of damage recived based on the explosion force, its positions and its critical chance.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TakeExplosionDamage(float ExplosionForce, FVector ExplosionPos, float CritChance, AActor* DamageInstigator);
	void TakeExplosionDamage_Implementation(float ExplosionForce, FVector ExplosionPos, float CritChance, AActor* DamageInstigator) override;

	/*The implementation for when we recive a call from the damage interface that a projectile has narrowly missed this character
	* this will add to the characters fear levels, fixing the character in place when fear is full.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void TakeSupressingFire(AActor* FiringActor);
	virtual void TakeSupressingFire_Implementation(AActor* FiringActor) override;

	/*The implementation for when we recive a call from the damage interface that a gun has been fired nearby
	* this will make the character and his team alert to the nearby fire.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void AlertToNearbyFire(AActor* FiringActor);
	virtual void AlertToNearbyFire_Implementation(AActor* FiringActor) override;

	/*The implementation for when we recive a call from the damage interface that an enemy soldier has been killed
	* Tells the character to find a new target.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnSoldierKilled();
	virtual void OnSoldierKilled_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsHitByBullet() const;
	void SetIsHitByBullet(bool IsHit);

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	virtual void KillCharacter(AActor * DamageInstigator);

	bool bIsHitByBullet = false;

//////////////////////
/*Faction interface*/
////////////////////

public:
	/** Returns the current faction (Call Execute_GetFaction instead for BP and C++ support)
	* @return the current faction
	*/
	virtual FFaction GetFaction() const override;

	/*The faction that this chracter belongs too.*/
	UPROPERTY(Category = Faction, EditAnywhere)
	FFaction CharacterFaction;

	void SetFaction(const FFaction& NewFaction) override;

};
