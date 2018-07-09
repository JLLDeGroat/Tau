// Fill out your copyright notice in the Description page of Project Settings.

#include "MarketHistory.h"


UMarketHistory::UMarketHistory() {

}

UMarketHistory* UMarketHistory::Setup(UAll* allRes) {
	for (int32 i = 0; i < allRes->GetAllResourceNamesAsString().Num(); i++) { // get all string resources
		FString fromRes = allRes->GetAllResourceNamesAsString()[i]; // set as from res

		for (int32 x = 0; x < allRes->GetAllResourceNamesAsString().Num(); x++) { // loop to get To Resources
			FString toRes = allRes->GetAllResourceNamesAsString()[x];

			if (fromRes != toRes) { // can not get same Resources Trading

				// Get Resource tiers
				EResourceTier::Tier fromTier = allRes->GetResourceTier(EResources::R_None, fromRes);
				EResourceTier::Tier toTier = allRes->GetResourceTier(EResources::R_None, toRes);

				MarketItems.Add(NewObject<UMarketItem>()->Setup(fromRes, toRes, fromTier, toTier));
			}
		}
	}
	return this;
}

void UMarketHistory::UpdateMarket(UAll* allRes) {
	for (int32 i = 0; i < this->MarketItems.Num(); i++) {
		UMarketItem* item = this->MarketItems[i];

		// Get Resource tiers
		EResourceTier::Tier fromTier = allRes->GetResourceTier(EResources::R_None, item->GetResFrom());
		EResourceTier::Tier toTier = allRes->GetResourceTier(EResources::R_None, item->GetResTo());

		//update Market Conversions
		item->SetCurrentConversion(fromTier, toTier);
	}
}

int32 UMarketHistory::GetTestInt() {
	return MarketTestInt;
}

void UMarketHistory::IncrementTestInt() {
	MarketTestInt++;
}

void UMarketHistory::LogTrade(FString resFrom, FString resTo, float conversionRate, float amount) {
	for (int32 i = 0; i < MarketItems.Num(); i++) {
		UMarketItem* item = MarketItems[0];

		if (item->GetResFrom() == resFrom && item->GetResTo() == resTo) {


			item->IncrementTimesTraded();

		}
	}
}