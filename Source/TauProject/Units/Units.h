// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitStructs.h"
#include "UnitTasks.h"
#include "Components/SphereComponent.h"
#include "Units/UnitTasks.h"
#include "Units/UnitInventory.h"
#include "PlayerResource/ResourceCost.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Weapons/Weapon.h"
#include "Units.generated.h"




UCLASS()
class TAUPROJECT_API AUnits : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnits();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	#pragma region visuals
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* CurrentMesh;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UDecalComponent* selectedDecal;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UMaterial* selectedDecalMaterial;


	#pragma endregion

	#pragma region Basic Properties

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		FString DisplayName;


	void SetDisplayName(FString name);
	FString GetDisplayName();
	FString GetType();
	float GetHealth();
	float GetMaxHealth();
	#pragma endregion


	#pragma region widget Properties

	UPROPERTY(EditAnywhere, category = global)
		FString Description;

	UFUNCTION(BlueprintCallable)
		FString GetHumanName();

	UFUNCTION(BlueprintCallable)
		FString GetDescription();

	UFUNCTION(BlueprintCallable)
		FString GetBuildCostAsUIString();

	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EUnitList::All> GetUnitType();

	void SetDescription(FString desc);

	UPROPERTY()
		bool bIsHighlighted;
	#pragma endregion

	#pragma region Movement And Instructions
	void ResetUnitInstructionsOnMove();
	
	void MoveUnit(AActor* ActorAtLocation, FVector Location, int32 UnitNumber, int32 UnitCount);

	void MoveUnitAndConstruct(AActor* Building, FVector Location);
	void MoveUnitAndAttack(AActor* actor);
	void MoveUnitAndHarvest(AActor* actor, FVector location);
	void MoveUnitAndHarvestBuilding(AActor* building);

	void IsMovementInstructionComplete();
	void IsAttackInstructionComplete();

	void AttemptToGetAutoTask();
	

	UPROPERTY()
		UUnitTasks* UnitTask;

	void HideDecals();
	void ShowDecals();

		
	#pragma endregion

	#pragma region Build Costs

	UPROPERTY()
		TArray<UResourceCost*> BuildCost;

	UPROPERTY()
		float SpawnTime;

	UFUNCTION(BlueprintCallable)
		TArray<UResourceCost*> GetBuildCost();

	void SetBuildCosts(TArray<UResourceCost*> buildCost);

	float GetSpawnTime();
	#pragma endregion

	#pragma region Base
	UPROPERTY()
		UUnitInventory* Inventory;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		bool CanHarvest;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float HarvestRate;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		bool CanBuild;

	UPROPERTY(EditAnywhere, Category = BuilderUnit)
		float BuildRate;

	UPROPERTY()
		bool IsBuilding;

	UPROPERTY()
		bool IsHarvesting;

	UPROPERTY()
		AActor* HarvestingActor;

	bool HitInstructedBuilding(AActor* OtherActor);

	void StartBuilding();
	void BuildBuilding();
	void BuildingFinished();


	bool IsTaskedToHarvest();
	bool IsTaskedToHarvestFoundActor(AActor* actor);
	bool HasNoTaskAndFoundResourceToHarvest(AActor* actor);

	void HarvestTick();
	AActor* FindNearestStorageBuilding();
	bool HasHitDropOffBuilding(AActor* actor);
	void DropResourcesOff();

	void AttemptToFindAnotherResourceOfType(AActor* res);

	UFUNCTION(BlueprintCallable)
		bool GetIsHarvesting();
	#pragma endregion

	#pragma region Combat 



	UPROPERTY()
		AWeapon* rArmWeapon;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float LineOfSight;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float AttackRange;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float Health;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float MaxHealth;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float Name;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float Attack;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float Defence;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float CriticalChance;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		float CriticalMultiplier;

	//range units
	bool bIsRanged;
	
	bool bIsAiming;
	bool bIsReloading;	
	bool bCanFire;
	bool bHasFired;

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		bool GetIsAiming();

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		void SetIsAiming(bool aiming);

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		bool GetIsReloading();

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		void SetIsReloading(bool reloading);

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		bool GetCanFire();

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		void SetCanFire(bool fire);

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		bool GetHasFired();

	UFUNCTION(BlueprintCallable, Category = RangedUnit)
		void SetHasFired(bool val);


	UPROPERTY()
		TArray<AActor*> UnitsInSight;
	UPROPERTY()
		TArray<AActor*> UnitsWithinRange;

	bool IsDead;

	UPROPERTY()
		bool bIsAttacking;

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking();

	UPROPERTY()
		AActor* AttackingUnit;


	bool GetIsDead();
	void SetIsDead();

	bool HasFoundAnEnemy(AActor* actor, UPrimitiveComponent* OtherComp);
	void NewEnemyHasEnteredAttackRange(AActor* actor);

	bool IsEnemyAttackable(AActor* actor);

	bool IsTaskedToKillFoundEnemy(AActor* actor);
	bool HasNoTaskAndFoundEnemy(AActor* actor);

	void EnemyIsOutOfAttackRange(AActor* actor);

	void StartAttacking(AActor* actor);
	void StopAttacking();
	void AttackTick();

	void AttemptToFindNewAttackTarget();

	void CleanUpUnitsWithinRange();
	#pragma endregion

	#pragma region Combar Armaments

	UPROPERTY()
		bool bIsArmed;

	UPROPERTY()
		TEnumAsByte<EUnitCombatType::ArmamentType> CombatType;

	#pragma endregion
	
	#pragma region Util
	void LookAt(AActor* actor);

	UPROPERTY()
		TEnumAsByte<EUnitList::All> ThisUnitType;

	UPROPERTY()
		AController* playerController;

	void SetController(AController* con);

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		TEnumAsByte<EUnitOwnerships::EUnitOwnerShip> UnitOwner;

	TEnumAsByte<EUnitOwnerships::EUnitOwnerShip> GetUnitOwner();
	void AUnits::SetUnitOwner(TEnumAsByte<EUnitOwnerships::EUnitOwnerShip> newowner);

	AUnits* GetUnitClassOfType(TEnumAsByte<EUnitList::All> unit);
	AUnits* SpawnUnitOfType(TEnumAsByte<EUnitList::All> unit, FVector spawnLocation, FRotator rotation, UWorld* ThisWorld);

	UPROPERTY()
		TArray<AActor*> BuildableBuildings;

	UFUNCTION(BlueprintCallable)
		TArray<AActor*> GetBuildableBuildings();
	#pragma endregion

	#pragma region overlaps

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		USphereComponent* SightSphere;

	UPROPERTY(EditAnywhere, Category = GlobalUnit)
		USphereComponent* RangeSphere;

	UFUNCTION()
		void WithinSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OutOfSight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void WithinRangeOfAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OutOfRangeOfAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	#pragma endregion

	#pragma region Unit Death
	void KillUnit();
	#pragma endregion

	void Debug(FString message);
};
