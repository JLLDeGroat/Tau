// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitTasks.h"
#include "Units/Task.h"
#include "UnitStructs.h"


UUnitTasks::UUnitTasks() {
	TaskList.Empty();
}


void UUnitTasks::CreateAndAddTask(FString name, FVector startLocation, FVector targetLocation, AActor * targetActor, TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction, bool ReplaceAll)
{
	UTask* newTask = NewObject<UTask>();
	newTask->SetName(name);
	newTask->SetStartLocation(startLocation);
	newTask->SetTargetLocation(targetLocation);
	newTask->SetTargetActor(targetActor);
	newTask->SetInstruction(instruction);
	newTask->SetIsAutoTask(false);

	if (ReplaceAll) TaskList.Empty();

	TaskList.Add(newTask);
}

void UUnitTasks::CreateAndAddTaskAUTO(FString name, FVector startLocation, FVector targetLocation, AActor * targetActor, TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction, bool ReplaceAll) {
	UTask* newTask = NewObject<UTask>();
	newTask->SetName(name);
	newTask->SetStartLocation(startLocation);
	newTask->SetTargetLocation(targetLocation);
	newTask->SetTargetActor(targetActor);
	newTask->SetInstruction(instruction);
	newTask->SetIsAutoTask(true);

	if (ReplaceAll) TaskList.Empty();

	TaskList.Add(newTask);
}

UTask* UUnitTasks::GetFirstTask() {
	if (TaskList.Num() > 0) 
		return TaskList[0];
	else return nullptr;
}

void UUnitTasks::RemoveFirstTask() {
	if (TaskList.Num() > 0) 
		TaskList.RemoveAt(0);
	else return;
}

bool UUnitTasks::HasTask() {
	return TaskList.Num() > 0;
}