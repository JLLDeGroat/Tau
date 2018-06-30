// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DetailsStringLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UDetailsStringLibrary : public UObject
{
	GENERATED_BODY()
		UDetailsStringLibrary();

public:	

	UPROPERTY()
		TArray<FString> FightingActivityList;

	UPROPERTY()
		TArray<FString> ConstructingActivityList;

	UPROPERTY()
		TArray<FString> DroppingActivityList;

	UPROPERTY()
		TArray<FString> GatheringActivityList;

	UPROPERTY()
		TArray<FString> MovingActivityList;

	UPROPERTY()
		TArray<FString> NoneActivityList;

	void SetupFightingList();
	void SetupConstructionList();
	void SetupDroppingOffList();
	void SetupGatheringList();
	void SetupMovingList();
	void SetupNoneList();


	FString FightingActivity();
	FString ConstructingActivity();
	FString DroppingOffActivity();
	FString GatheringActivity();
	FString MovingActivity();
	FString NoneActivity();
};
