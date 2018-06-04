// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Units/Task.h"
#include "UObject/NoExportTypes.h"
#include "UnitTasks.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UUnitTasks : public UTask
{
	GENERATED_BODY()
		UUnitTasks();
	
public:

	UPROPERTY()
		TArray<UTask*> TaskList;
	

	void CreateAndAddTask(FString name, FVector startLocation, FVector targetLocation, AActor* targetActor, TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction, bool ReplaceAll = true);
	void CreateAndAddTaskAUTO(FString name, FVector startLocation, FVector targetLocation, AActor* targetActor, TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction, bool ReplaceAll = true);

	bool HasTask();

	UTask* GetFirstTask();
	void RemoveFirstTask();

};
