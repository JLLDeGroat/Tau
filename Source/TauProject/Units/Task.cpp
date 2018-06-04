// Fill out your copyright notice in the Description page of Project Settings.

#include "Task.h"


#pragma region Getters & Setters

FString UTask::GetName() {
	return Name;
}

FVector UTask::GetTargetLocation() {
	return TargetLocation;
}

FVector UTask::GetStartLocation() {
	return StartLocation;
}

AActor* UTask::GetTargetActor() {
	return TargetActor;
}

TEnumAsByte<EUnitInstructions::EUnitInstruction> UTask::GetInstruction() {
	return Instruction;
}

bool UTask::GetIsAutoTask() {
	return IsAutoTask;
}


void UTask::SetName(FString name) {
	Name = name;
}

void UTask::SetTargetLocation(FVector target) {
	TargetLocation = target;
}

void UTask::SetStartLocation(FVector start) {
	StartLocation = start;
}

void UTask::SetTargetActor(AActor* actor) {
	TargetActor = actor;
}

void UTask::SetInstruction(TEnumAsByte<EUnitInstructions::EUnitInstruction> instruction) {
	Instruction = instruction;
}

void UTask::SetIsAutoTask(bool isauto) {
	IsAutoTask = isauto;
}

#pragma endregion
