// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/ResourceCost.h"

#include "Researcher.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UResearcher : public UObject
{
	GENERATED_BODY()
		UResearcher();

public:
	UResearcher(FString name, FString desc, TArray<UResourceCost*> costList, float researchTime);


	UPROPERTY()
		FString Description;

	UPROPERTY()
		FString Name;

	UPROPERTY()
		TArray<UResourceCost*> ResearchCost;
	
	UPROPERTY()
		float CurrentResearchTime;

	UPROPERTY()
		float ResearchTime;


	UPROPERTY()
		bool HasStarted;

	UPROPERTY()
		bool IsFinished;

	void UpdateResearch(float DeltaTime);

	TArray<UResourceCost*> GetResourceCost();


	UFUNCTION(BlueprintCallable)
		FString GetResearchName();

	UFUNCTION(BlueprintCallable)
		FString GetResearchDescription();

	UFUNCTION(BlueprintCallable)
		FString GetResearchCostUIString();


	bool GetHasStarted();
	bool GetIsFinished();

	void SetHasStarted(bool val);
	void SetIsFinished(bool val);
	
};
