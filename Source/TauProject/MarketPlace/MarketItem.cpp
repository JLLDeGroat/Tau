// Fill out your copyright notice in the Description page of Project Settings.

#include "MarketItem.h"

UMarketItem::UMarketItem() {

}

UMarketItem* UMarketItem::Setup(FString resFrom, FString resTo, TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier) {
	resourceFrom = resFrom;
	resourceTo = resTo;

	SetCurrentConversion(fromTier, toTier, true);

	return this;
}

void UMarketItem::SetCurrentConversion(TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier, bool bIsInitial) {
	if (!bIsInitial) 
	{
		Conversions.Add(CurrentConversion);
		ConversionEvents.Add(CurrentEvent);
	}

	CurrentConversion = (GetRateFromTier(fromTier) + GetRateFromTier(toTier)) / 2;

	int32 eventRate = FMath::RandRange(0, 100);
	if (eventRate < 10) {
		int32 eventType = FMath::RandRange(0, 100);
		if (eventType > 49) {
			//event is positive
			CurrentConversion += .15f;
			CurrentEvent = "Demand is up";
		}
		else {
			//event is negative
			CurrentConversion -= .15f;
			CurrentEvent = "Demand is down";
		}
	}
	else {
		CurrentEvent = "Normal trading";
	}
}

float UMarketItem::GetRateFromTier(TEnumAsByte<EResourceTier::Tier> tier) {
	switch (tier) {
	case EResourceTier::T_1:
		return .35f;
	case EResourceTier::T_2:
		return .5f;
	case EResourceTier::T_3:
		return .75f;
	case EResourceTier::T_4:
		return 1;
	case EResourceTier::T_5:
		return 2;

	default: 
		return 0.35;
	}
}

void UMarketItem::IncrementTimesTraded() {
	TimesTraded++;
	CurrentConversion -= .4f;
}




void UMarketItem::SetResFrom(FString res) {
	resourceFrom = res;
}
void UMarketItem::SetResTo(FString res) {
	resourceTo = res;
}

FString UMarketItem::GetResFrom() {
	return resourceFrom;
}
FString UMarketItem::GetResTo() {
	return resourceTo;
}

FString UMarketItem::GetCurrentEvent() {
	return CurrentEvent;
}

float UMarketItem::GetCurrentConversion() {
	return CurrentConversion;
}

float UMarketItem::GetTimesTraded() {
	return TimesTraded;
}

TArray<float> UMarketItem::GetHistoricConversions() {
	return Conversions;
}

TArray<FString> UMarketItem::GetHistoricEvents() {
	return ConversionEvents;
}
