// Fill out your copyright notice in the Description page of Project Settings.

#include "MarketConversionItem.h"


UMarketConversionItem::UMarketConversionItem() {

}

void UMarketConversionItem::AddToConversionHistory(float value) {
	ConversionHistory.Add(value);
}
