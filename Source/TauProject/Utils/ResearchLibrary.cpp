// Fill out your copyright notice in the Description page of Project Settings.

#include "ResearchLibrary.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

UResearchLibrary::UResearchLibrary() {

}


UResearcher* UResearchLibrary::GetResearch(TEnumAsByte<EResearchList::EResearhables> researchType) {
	TArray<UResearcher*> researchList = ResearchList();
	for (int32 i = 0; i < researchList.Num(); i++) {
		if (researchList[i]->ResearchType == researchType) return researchList[i];
	}
	return nullptr;
}

UResearcher* UResearchLibrary::GetResearch(TEnumAsByte<EResearchList::EResearhables> researchType, TArray<UResearcher*> researchList) {
	for (int32 i = 0; i < researchList.Num(); i++) {
		if (researchList[i]->ResearchType == researchType) return researchList[i];
	}
	return nullptr;
}


UResearcher* UResearchLibrary::GetResearchItemForHover(TEnumAsByte<EResearchList::EResearhables> researchType, TArray<UResearcher*> buildingResearch, TArray<UResearcher*> completedResearch) {
	
	UResearcher* research = nullptr;
	Debug(FString::SanitizeFloat(buildingResearch.Num()));
	for (int32 i = 0; i < buildingResearch.Num(); i++) {		
		if (buildingResearch[i]->ResearchType == researchType) 
			research = buildingResearch[i];
	}
	
	if (research == nullptr) {
		Debug("Found no research of this type in this building");
		return nullptr; // wasnt found
	}

	
	TArray<UResearcher*> completedResearchOfThisType;
	for (int32 i = 0; i < completedResearch.Num(); i++) {
		if (completedResearch[i]->ResearchType == researchType) {
			completedResearchOfThisType.Add(completedResearch[i]);
		}
	}

	if (completedResearch.Num() < research->ChildrenVersions) {
		//valid one
		FString researchVersion = "";
		if(completedResearch.Num() != 0) researchVersion = FString::SanitizeFloat(completedResearch.Num(), 0);
		research->DisplayName = research->Name + " " + researchVersion;
		research->AdditiveResearchCost = GetCostOfResearch(research, completedResearchOfThisType);
	}
	else {
		research->DisplayName = "COMPLETED";
	}

	return research;
}

UResearcher* UResearchLibrary::GetResearchItemForResearching(TEnumAsByte<EResearchList::EResearhables> researchType, TArray<UResearcher*> completedResearch) {
	UResearcher* toResearch = GetResearch(researchType);

	TArray<UResearcher*> completedResearchOfType;
	for (int32 i = 0; i < completedResearch.Num(); i++) {
		if (completedResearch[i]->ResearchType == researchType) completedResearchOfType.Add(completedResearch[i]);
	}

	if (GetCurrentResearchVersion(completedResearchOfType, toResearch) == -1) {
		return nullptr;
	}

	toResearch->DisplayName = toResearch->Name + " " + FString::SanitizeFloat(GetCurrentResearchVersion(completedResearchOfType, toResearch), 0);	
	toResearch->AdditiveResearchCost = GetCostOfResearch(toResearch, completedResearchOfType);
	toResearch->CurrentVersion = GetCurrentResearchVersion(completedResearchOfType, toResearch);
	return toResearch;
}

TArray<UResourceCost*> UResearchLibrary::GetCostOfResearch(UResearcher* research, TArray<UResearcher*> completedResearchOfType) {
	
	float multipler = GetCurrentResearchVersion(completedResearchOfType, research) + 1;

	research->AdditiveResearchCost.Empty();

	TArray<UResourceCost*> baseCost = research->GetResourceCost();
	TArray<UResourceCost*> multiplierCost;

	for (int32 i = 0; i < baseCost.Num(); i++) {
		baseCost[i]->Amount *= multipler;
		multiplierCost.Add(baseCost[i]);
	}
	return multiplierCost;
}

float UResearchLibrary::GetCurrentResearchVersion(TArray<UResearcher*> researchOfType, UResearcher* research) {
	if (researchOfType.Num() < research->ChildrenVersions) {
		return researchOfType.Num();
	}
	return -1;
}

TArray<UResearcher*> UResearchLibrary::ResearchList() {
	TArray<UResearcher*> resList;
	
	//Ore Refinery
	UResearcher* oreRefinery = NewObject<UResearcher>();
	oreRefinery->Name = "Ore Refinery";
	oreRefinery->Description = "Learn the way of duplication, your smithee will alt f4 at the right moment which doubles the amount of smithed ingots";
	oreRefinery->ResearchTime = 5;
	oreRefinery->ResearchType = EResearchList::R_OreRefinery;
	oreRefinery->ChildrenVersions = 1;
	oreRefinery->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_IronOre, 10));
	oreRefinery->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 10));


	//IRON FORGE
	UResearcher* ironForge = NewObject<UResearcher>();
	ironForge->Name = "Iron Forge";
	ironForge->Description = "Learn the ways of heating, by debating the best ways of cooking a fish.";
	ironForge->ResearchTime = 5;
	ironForge->ResearchType = EResearchList::R_IronForge;
	ironForge->ChildrenVersions = 1;
	ironForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	ironForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Copper, 5));
	

	//COPPER FORGE
	UResearcher* copperForge = NewObject<UResearcher>();
	copperForge->Name = "Copper Forge";
	copperForge->Description = "Learn the ways of heating, by debating the best ways of cooking a egg.";
	copperForge->ResearchTime = 5;
	copperForge->ResearchType = EResearchList::R_CopperForge;
	copperForge->ChildrenVersions = 1;
	copperForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	copperForge->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_CopperOre, 5));
	

	//HARVESTING I
	UResearcher* harvestingI = NewObject<UResearcher>();
	harvestingI->Name = "Harvesting";
	harvestingI->Description = "discussing the hoe, the sickle and the scythe creates new ways of ripping plants from their home";
	harvestingI->ResearchTime = 5;
	harvestingI->ResearchType = EResearchList::R_Harveting;
	harvestingI->ChildrenVersions = 3;
	harvestingI->ResearchCost.Add(NewObject<UResourceCost>()->Setup(EResources::R_Bread, 5));
	
	
	resList.Add(oreRefinery);
	resList.Add(ironForge);
	resList.Add(copperForge);
	resList.Add(harvestingI);

	return resList;
}

void UResearchLibrary::Debug(FString message) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "UResearchLibrary.h: " + message);
}