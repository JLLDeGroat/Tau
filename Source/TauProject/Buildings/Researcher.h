// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/ResourceCost.h"

#include "Researcher.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
namespace EResearchList
{
	enum  EResearhables
	{
		R_OreRefinery					UMETA(DisplayName = "Ore Refinery"),
		R_Harveting						UMETA(DisplayName = "Harvesting"),
		R_CopperForge					UMETA(DisplayName = "Copper Forge"),
		R_IronForge						UMETA(DisplayName = "Iron Forge"),
	};
}




UCLASS()
class TAUPROJECT_API UResearcher : public UObject
{
	GENERATED_BODY()
		UResearcher();

public:
	UResearcher(FString name, FString desc, TArray<UResourceCost*> costList, float researchTime);

	UResearcher* Setup(FString name, FString desc, float researchTime, float childVersions, TEnumAsByte<EResearchList::EResearhables> researchEnum, TArray<UResourceCost*> costList);


	UPROPERTY()
		FString Description;

	UPROPERTY()
		FString Name;

	UPROPERTY()
		FString DisplayName;

	UPROPERTY()
		TArray<UResourceCost*> ResearchCost;

	UPROPERTY()
		TArray<UResourceCost*> AdditiveResearchCost;

	UPROPERTY()
		TEnumAsByte<EResearchList::EResearhables> ResearchType;
	
	UPROPERTY()
		float CurrentResearchTime;

	UPROPERTY()
		float ResearchTime;

	UPROPERTY()
		float ChildrenVersions;

	UPROPERTY()
		float CurrentVersion;

	UPROPERTY()
		bool HasStarted;

	UPROPERTY()
		bool IsFinished;

	UPROPERTY()
		bool IsCompleted;

	void UpdateResearch(float DeltaTime);

	TArray<UResourceCost*> GetResourceCost();


	UFUNCTION(BlueprintCallable)
		FString GetResearchName();

	UFUNCTION(BlueprintCallable)
		FString GetResearchDescription();

	UFUNCTION(BlueprintCallable)
		FString GetResearchCostUIString();

	UFUNCTION(BlueprintCallable)
		bool GetIsCompletedResearch();

	UFUNCTION(BlueprintCallable)
		FString GetDisplayName();

	bool GetHasStarted();
	bool GetIsFinished();

	void SetHasStarted(bool val);
	void SetIsFinished(bool val);
	
};
