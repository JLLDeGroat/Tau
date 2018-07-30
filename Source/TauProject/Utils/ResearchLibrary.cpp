// Fill out your copyright notice in the Description page of Project Settings.

#include "ResearchLibrary.h"


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
	ironForge->ResearchType = EResearchList::R_CopperForge;
	ironForge->ChildrenVersions = 1;
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