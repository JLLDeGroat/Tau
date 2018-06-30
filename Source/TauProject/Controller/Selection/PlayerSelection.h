// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Units/UnitStructs.h"
#include "Buildings/BuildingStructs.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/EResource.h"
#include "PlayerSelection.generated.h"

UCLASS()
class TAUPROJECT_API UPlayerSelection : public UObject
{
	GENERATED_BODY()
		UPlayerSelection();
		UPlayerSelection(APlayerController * controller);
public:
	
	#pragma region Properties
	UPROPERTY()
		APlayerController* controllerClass;

	UPROPERTY()
		FString Name;
	UPROPERTY()
		float Health;
	UPROPERTY()
		float MaxHealth;
	UPROPERTY()
		float HealthAsPercent;
	UPROPERTY()
		FString Activity;
	UPROPERTY()
		FString Type;
	UPROPERTY()
		FString HealthOfMax;
	UPROPERTY()
		AActor* ActorClass;

	#pragma endregion

	#pragma region Getters
		
	UFUNCTION(BluePrintCallable)
		FString GetName();
	UFUNCTION(BluePrintCallable)
		float GetHealth();
	UFUNCTION(BluePrintCallable)
		float GetMaxHealth();
	UFUNCTION(BluePrintCallable)
		float GetHealthAsPercent();
	UFUNCTION(BluePrintCallable)
		FString GetActivity();
	UFUNCTION(BluePrintCallable)
		FString GetType();
	UFUNCTION(BluePrintCallable)
		FString GetHealthOfMax();
	UFUNCTION(BluePrintCallable)
		AActor* GetActorClass();

	#pragma endregion

	#pragma region Setters

	void SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EUnitInstructions::EUnitInstruction> activity,	FString type, AActor* actor);
	void SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EBuildStates::EBuildingStates> activity,			FString type, AActor* actor);
	void SetSelection(FString name, float health, float maxHealth, TEnumAsByte<EResources::All> activity,						FString type, AActor* actor);

	void SetName(FString name);
	void SetHealth(float health);
	void SetMaxHealth(float health);
	void SetHealthAsPercentage(float health);
	void SetActivity(FString activity);
	void SetType(FString type);
	void SetActorClass(AActor* actor);

	#pragma endregion

	#pragma region Util

	float CalculatePercantage(float num, float max);

	FString GetActivityFromState(TEnumAsByte<EUnitInstructions::EUnitInstruction> activity);
	FString GetActivityFromState(TEnumAsByte<EBuildStates::EBuildingStates> activity);
	FString GetActivityFromState(TEnumAsByte<EResources::All> activity);
	#pragma endregion

	

};
