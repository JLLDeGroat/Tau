// Fill out your copyright notice in the Description page of Project Settings.

#include "MarketItem.h"
#include "Algo/Reverse.h"

UMarketItem::UMarketItem() {

}

UMarketItem* UMarketItem::Setup(FString resFrom, FString resTo, TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier) {
	resourceFrom = resFrom;
	resourceTo = resTo;

	SetBaseConversionRate(fromTier, toTier);
	SetCurrentConversion(fromTier, toTier, true);
	return this;
}

void UMarketItem::SetBaseConversionRate(TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier) {
	BaseConversionRate = (GetRateFromTier(fromTier) + GetRateFromTier(toTier)) / 2;
	CurrentConversionRate = BaseConversionRate;
}

void UMarketItem::SetCurrentConversion(TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier, bool bIsInitial) {
	if (!bIsInitial) 
	{
		Conversions.Add(CurrentConversion);
		ConversionEvents.Add(CurrentEvent);

		if (Conversions.Num() > 10) Conversions.RemoveAt(10);
		if (ConversionEvents.Num() > 10) ConversionEvents.RemoveAt(10);
	}
	
	CurrentConversion += .03f;
	if (CurrentConversion > BaseConversionRate) CurrentConversion = BaseConversionRate; //  can not go above base until a demand event occurs below

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

	if (CurrentConversion < 0) CurrentConversion = 0;
}

float UMarketItem::GetRateFromTier(TEnumAsByte<EResourceTier::Tier> tier) {
	switch (tier) {
	case EResourceTier::T_1:
		return .6f;
	case EResourceTier::T_2:
		return .8f;
	case EResourceTier::T_3:
		return .99f;
	case EResourceTier::T_4:
		return 1;
	case EResourceTier::T_5:
		return 1;

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
	TArray<float> reversed = Conversions;
	Algo::Reverse(reversed);
	return reversed;
}

TArray<FString> UMarketItem::GetHistoricEvents() {
	TArray<FString> reversed = ConversionEvents;
	Algo::Reverse(reversed);
	return reversed;
}
