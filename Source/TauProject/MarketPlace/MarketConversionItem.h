// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MarketConversionItem.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UMarketConversionItem : public UObject
{
	GENERATED_BODY()
		UMarketConversionItem();

	UPROPERTY()
		TArray<float> ConversionHistory;

public:
	void AddToConversionHistory(float value);
		
};
