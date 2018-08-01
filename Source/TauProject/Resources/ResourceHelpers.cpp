// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceHelpers.h"




UResourceHelpers::UResourceHelpers() {

}



void UResourceHelpers::SetInitialResourceAmount(AResource* resource) {
	float count = FMath::RandRange(resource->MinResourceCount, resource->MaxResourceCount);
	resource->ResourceCountOriginal = count;
	resource->ResourceCount = count;
}

void UResourceHelpers::SetResourceMinMaxAmount(AResource* resource) {
	switch (resource->ResourceType) {
		case EResources::R_CopperOre:
		case EResources::R_IronOre:
		case EResources::R_Coal:
		case EResources::R_Lumber:
			resource->MinResourceCount = 120;
			resource->MaxResourceCount = 849;

		default:
			resource->MinResourceCount = 50;
			resource->MaxResourceCount = 250;
	}
}


void UResourceHelpers::CheckIfDepleted(AResource* resource) {
	if (resource->ResourceCount <= 0) {
		resource->SetIsDepleted();
		resource->Destroy();
	}
}