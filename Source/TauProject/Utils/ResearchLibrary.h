// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Buildings/Researcher.h"
#include "PlayerResource/ResourceCost.h"
#include "ResearchLibrary.generated.h"
/**
 * 
 */
UCLASS()
class TAUPROJECT_API UResearchLibrary : public UObject
{
	GENERATED_BODY()
		UResearchLibrary();
	
public:
	

	static TArray<UResearcher*> ResearchList();

	
	static UResearcher* GetResearch(TEnumAsByte<EResearchList::EResearhables> researchType);
	static UResearcher* GetResearch(TEnumAsByte<EResearchList::EResearhables> researchType, TArray<UResearcher*> researchList);

};
