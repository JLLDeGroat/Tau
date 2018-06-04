// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitStructs.h"
#include "Task.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UTask : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		FString Name;
	UPROPERTY()
		FVector StartLocation;
	UPROPERTY()
		FVector TargetLocation;	
	UPROPERTY()
		AActor* TargetActor;
	UPROPERTY()
		TEnumAsByte<EUnitInstructions::EUnitInstruction> Instruction;
	UPROPERTY()
		bool IsAutoTask;

	

	void SetName(FString name);
	void SetTargetLocation(FVector target);
	void SetStartLocation(FVector start);
	void SetTargetActor(AActor* actor);
	void SetInstruction(TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction);
	void SetIsAutoTask(bool isauto);

	FString GetName();
	FVector GetStartLocation();
	FVector GetTargetLocation();
	AActor* GetTargetActor();
	TEnumAsByte<EUnitInstructions::EUnitInstruction> GetInstruction();
	bool GetIsAutoTask();
};
