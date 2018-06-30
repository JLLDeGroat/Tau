// Fill out your copyright notice in the Description page of Project Settings.

#include "DetailsStringLibrary.h"


UDetailsStringLibrary::UDetailsStringLibrary() {
	SetupFightingList();
	SetupConstructionList();
	SetupDroppingOffList();
	SetupGatheringList();
	SetupMovingList();
	SetupNoneList();		
}

FString UDetailsStringLibrary::FightingActivity() {
	return "";
}

FString UDetailsStringLibrary::ConstructingActivity() {
	return "";
}

FString UDetailsStringLibrary::DroppingOffActivity() {
	return "";
}

FString UDetailsStringLibrary::GatheringActivity() {
	return "";
}

FString UDetailsStringLibrary::MovingActivity() {
	return "";
}

FString UDetailsStringLibrary::NoneActivity() {
	return "";
}


void UDetailsStringLibrary::SetupFightingList() {
	FightingActivityList.Add("Fighting");
}
void UDetailsStringLibrary::SetupConstructionList() {
	ConstructingActivityList.Add("Constructing");
}
void UDetailsStringLibrary::SetupDroppingOffList() {
	DroppingActivityList.Add("Dropping Off");
}
void UDetailsStringLibrary::SetupGatheringList() {
	GatheringActivityList.Add("Gathering");
}
void UDetailsStringLibrary::SetupMovingList() {
	MovingActivityList.Add("Moving");
}
void UDetailsStringLibrary::SetupNoneList() {
	NoneActivityList.Add("Absolutely Nothing");
}