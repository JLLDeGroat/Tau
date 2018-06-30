// Fill out your copyright notice in the Description page of Project Settings.

#include "Researcher.h"

UResearcher::UResearcher() {

}

UResearcher::UResearcher(FString name, FString desc, TArray<UResourceCost*> costList, float researchTime) {
	this->Name = name;
	this->Description = desc;
	this->ResearchCost = costList;
	this->ResearchTime = researchTime;
}


void UResearcher::UpdateResearch(float DeltaTime) {
	if (HasStarted) {
		//only do this if its started
		CurrentResearchTime += DeltaTime;

		if (CurrentResearchTime >= ResearchTime) {
			this->IsFinished = true;
		}
	}
}

FString UResearcher::GetResearchName() {
	return Name;
}

FString UResearcher::GetResearchDescription() {
	return this->Description;
}

FString UResearcher::GetResearchCostUIString() {
	FString CostListString = "";

	for (int32 i = 0; i < this->ResearchCost.Num(); i++) {
		CostListString += FString::SanitizeFloat(this->ResearchCost[i]->Amount) + "x " + this->ResearchCost[i]->GetResourceType() + "   ";
	}
	return CostListString;
}

TArray<UResourceCost*> UResearcher::GetResourceCost() {
	return ResearchCost;
}

bool UResearcher::GetHasStarted() {
	return this->HasStarted;
}

bool UResearcher::GetIsFinished() {
	return this->IsFinished;
}


void UResearcher::SetHasStarted(bool val) {
	this->HasStarted = val;
}

void UResearcher::SetIsFinished(bool val) {
	this->IsFinished = val;
}