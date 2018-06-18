// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerResource/ResourceCost.h"
#include "PlayerResource/All.h"
#include "Converter.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UConverter : public UObject
{
	GENERATED_BODY()
		UConverter();
public:


	UPROPERTY()
		bool IsActive;

	UPROPERTY()
		float ConversionRate;

	UPROPERTY()
		float CurrentConversion;

	UPROPERTY()
		bool CurrentlyConverting;

	UPROPERTY()
		bool ConversionComplete;

	#pragma region Getters
	bool GetCurrentlyConverting();

	bool GetConversionComplete();

	bool GetIsActive();

	float GetConversionRate();

	TArray<UResourceCost*> UConverter::GetConverterToItem();
	TArray<UResourceCost*> UConverter::GetConverterFromItem();

	#pragma endregion

	#pragma region Setters;
	void SetCurrentlyConverting(bool value);

	void SetConversionComplete(bool complete);

	void SetIsActive(bool active);

	void SetConversionRate(float rate);

	void SetConverterFromItem(UResourceCost* item);
	void SetConverterToItem(UResourceCost* item);
	#pragma endregion

	UPROPERTY()
	TArray<UResourceCost*> ConvertsFrom;
	UPROPERTY()
	TArray<UResourceCost*> ConvertsTo;


	//bool HasResourceForConvert(TArray<UResourceCost*> costlist, UAll* resources);
		
	void UpdateConvert(float DeltaTime);

	void CompletedConversion();
	
};
