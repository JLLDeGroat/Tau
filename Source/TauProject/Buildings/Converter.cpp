// Fill out your copyright notice in the Description page of Project Settings.

#include "Converter.h"
#include "PlayerResource/All.h"
#include "PlayerResource/ResourceCost.h"


UConverter::UConverter() {
	SetIsActive(true);
	CurrentConversion = 0;
}



#pragma endregion Getters
bool UConverter::GetCurrentlyConverting() {
	return CurrentlyConverting;
}

bool UConverter::GetConversionComplete() {
	return ConversionComplete;
}

bool UConverter::GetIsActive() {
	return this->IsActive;
}

float UConverter::GetConversionRate() {
	return this->ConversionRate;
}

TArray<UResourceCost*> UConverter::GetConverterFromItem() {
	return ConvertsFrom;
}

TArray<UResourceCost*> UConverter::GetConverterToItem() {
	return ConvertsTo;
}

#pragma endregion

#pragma region Setters
void UConverter::SetCurrentlyConverting(bool value) {
	CurrentlyConverting = value;
}

void UConverter::SetConversionComplete(bool complete) {
	ConversionComplete = complete;
}

void UConverter::SetIsActive(bool active) {
	this->IsActive = active;
}

void UConverter::SetConversionRate(float rate) {
	this->ConversionRate = rate;
}

void UConverter::SetConverterFromItem(UResourceCost* item) {
	ConvertsFrom.Add(item);
}

void UConverter::SetConverterFromItem(TArray<UResourceCost*> items) {
	for (int32 i = 0; i < items.Num(); i++) {
		ConvertsFrom.Add(items[i]);
	}
}

void UConverter::SetConverterToItem(UResourceCost* item) {
	ConvertsTo.Add(item);
}

void UConverter::SetConverterToItem(TArray<UResourceCost*> items) {
	for (int32 i = 0; i < items.Num(); i++) {
		ConvertsTo.Add(items[i]);
	}
}
#pragma endregion


void UConverter::UpdateConvert(float DeltaTime) {
	CurrentConversion += DeltaTime;

	if (CurrentConversion >= ConversionRate) {
		CompletedConversion();
		//converting of res is complete :D
	}
}

void UConverter::CompletedConversion() {
	CurrentConversion = 0;
	SetConversionComplete(true);
}




