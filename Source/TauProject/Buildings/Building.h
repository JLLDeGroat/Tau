#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buildings/BuildingStructs.h"
#include "PlayerResource/ResourceCost.h"
#include "Units/Units.h"
#include "Units/UnitStructs.h" 
#include "Buildings/Researcher.h"
#include "Building.generated.h"
UCLASS()
class TAUPROJECT_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PostConstructionMethod();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		UStaticMeshComponent* Box;
	UPROPERTY()
		UStaticMesh* BuildingMesh;
	UPROPERTY()
		UStaticMesh* FailedBuildingMesh;
	UPROPERTY()
		UStaticMesh* Stage1Construction;
	UPROPERTY()
		UStaticMesh* Stage2Construction;
	UPROPERTY()
		UStaticMesh* Stage3Construction;
	UPROPERTY()
		UStaticMesh* Stage1Damage;
	UPROPERTY()
		UStaticMesh* Stage2Damage;
	UPROPERTY()
		UStaticMesh* Stage3Damage;
	UPROPERTY()
		UStaticMesh* DepletedMesh;

	UPROPERTY()
		AController* control;
	
	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		TEnumAsByte<EAvailableBuildings::EAvailableBuildings> BuildingType;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		FString BuildingName;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		float Health;

	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		float MaxHealth;
		
	UPROPERTY(EditAnywhere, category = BuildingGlobal)
		bool CanStore;

	#pragma region Basic Properties

	FString GetName();
	FString GetType();
	float GetHealth();
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EAvailableBuildings::EAvailableBuildings> GetBuildingType();

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


	void SetDescription(FString desc);

	#pragma endregion

	#pragma region Costing
	UPROPERTY()
		TArray<UResourceCost*> BuildCost;

	UFUNCTION(BlueprintCallable)
		TArray<UResourceCost*> GetBuildCost();

	void SetBuildCosts(TArray<UResourceCost*> costList);


	UPROPERTY()
		TArray<UResearcher*> ResearchCost;

	void SetResearchCosts(TArray<UResearcher*> costList);

	UPROPERTY()
		TArray<FString> NeededBuildingList;

	void SetNeededBuildingList(TArray<FString> name);

	TArray<FString> GetNeededBuildingList();
	#pragma endregion

	#pragma region Spawning
	UPROPERTY()
		bool IsPlaced;

	UPROPERTY()
		bool IsConstructed;

	UPROPERTY()
		bool CanPlace;

	UPROPERTY()
		bool RadiusPlaceRules;

	UPROPERTY()
		TEnumAsByte<EAvailableBuildings::EAvailableBuildings> RadiusPlaceActor;

	UPROPERTY()
		float RadiusPlaceAmount;

	UPROPERTY()
		TArray<UPrimitiveComponent*> OverlappingComponents;

	UFUNCTION()
		void StartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		bool GetIsConstructed();


	void SetBuildingAsPlaced();
	void CheckIsValidPlacement();
	bool GetIsValidPlacement();
	void SetIsValidPlacement(bool valid);

	bool SpecialSpawnConditionsMet();

	void SetRadiusPlaceRules(bool value);
	bool GetIsRadiusPlaceRule();
	void SetRadiusPlaceActor(TEnumAsByte<EAvailableBuildings::EAvailableBuildings> value);
	TEnumAsByte<EAvailableBuildings::EAvailableBuildings> GetRadiusPlaceActor();
	void SetRadiusPlaceAmount(float value);
	float GetRadiusPlaceAmount();

	

	void SetMeshOnValidPlacement();

	void PlaceBuilding();

	void SetPlayerController(AController* controller);
	AController* GetPlayerController();


	void SetIsConstructed(bool val);
	#pragma endregion

	#pragma region Health Changes

	void AddToHealth(float amount);
	void SubtractFromHealth(float amount);
	void SetHealthToMax();

	void ChangeStateOnHealthChange();

	#pragma endregion

	#pragma region Onwership
	UPROPERTY()
		TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> BuildingOwner;

	void SetBuildingOwner(TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> owner);
	TEnumAsByte<EBuildingOwnerships::EBuildingOwnership> GetBuildingOwnership();

	#pragma endregion

	#pragma region States

	UPROPERTY()
		TEnumAsByte<EBuildStates::EBuildingStates> CurrentBuildingState;

	void SetBuildingState(TEnumAsByte<EBuildStates::EBuildingStates> state);
	TEnumAsByte<EBuildStates::EBuildingStates> GetCurrentState();

	#pragma endregion
	
	#pragma region Creating And Spawning Units & Buildings

	UPROPERTY()
		TArray<AUnits*> SpawnableUnits;

	UPROPERTY()
		TArray<ABuilding*> SpawnableBuildings;

	UPROPERTY()
		TArray<UObject*> SpawnList;

	UFUNCTION(BlueprintCallable)
	void AddUnitToSpawnList(TEnumAsByte<EUnitList::All> unitType);	

	void SpawnUnitTick(float DeltaTime);


	#pragma endregion


	#pragma region Converting Resources
	UPROPERTY()
	UObject* ResourceConverter;

	void SetResourceConversions(TArray<UResourceCost*> Cost, TArray<UResourceCost*> Reward, float Rate);

	UPROPERTY()
		bool IsConverter;

	void SetIsConverter(bool converter);
	bool GetIsConverter();

	void UpdateResourceConvert(float DeltaTime);

	#pragma endregion

	#pragma region Depletable

	UPROPERTY()
		bool IsDepletableResourceBuilding;

	UPROPERTY()
		bool IsDepletableResourceDepleted;

	UPROPERTY()
		UObject* DepletableResource;

	float GetCurrentDepletableResource();
	
	void AffectCurrentDepletableResource(float amount, bool IsAdd = false);

	void SetupDepletableResource(UObject* resource);

	void SetIsDepletableResourceBuilding(bool val);
	bool GetIsDepletableResourceBuilding();

	bool GetIsDepletableResourceDepleted();

	void SetIsDepletableResourceDepleted(bool val = true);

	float RemoveAmountFromDepletableResource(float amount);

	#pragma endregion

	#pragma region Utils

	void SetMeshOnState();
	#pragma endregion

	#pragma region Researchable

	UFUNCTION(BlueprintCallable)
		TArray<UResearcher*> GetResearchList();

	UFUNCTION(BlueprintCallable)
		UResearcher* GetResearchItemByName(FString name);

	UFUNCTION(BlueprintCallable)
		UResearcher* GetUIResearchByType(TEnumAsByte<EResearchList::EResearhables> researchType);

	UFUNCTION(BlueprintCallable)
		FString GetResearchCostAsUIString(FString name);

	UFUNCTION(BlueprintCallable)
		FString GetResearchDescription(FString name);

	void SetResearchObjects(TArray<UResearcher*> researchList);

	UPROPERTY()
		bool CanResearch;

	UPROPERTY()
		TArray<UResearcher*> ResearchObject;

	UFUNCTION(BlueprintCallable)
		bool GetIsResearchBuilding();

	UPROPERTY()
		bool CurrentlyResearching;

	UFUNCTION()
		bool GetIsCurrentlyResearching();

	UResearcher* CurrentlyResearchingObject;

	void SetIsResearchBuilding(bool val);

	UFUNCTION(BlueprintCallable)
		void BeginResearching(TEnumAsByte<EResearchList::EResearhables> researchType);

	void ResearchTick(float DeltaTime);

	#pragma endregion

	void Debug(FString error);
};
