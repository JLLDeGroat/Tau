// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "MarketPlace/MarketItem.h"
#include "PlayerResource/All.h"
#include "UObject/NoExportTypes.h"
#include "MarketHistory.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UMarketHistory : public UObject
{
	GENERATED_BODY()
		UMarketHistory();
	
	int32 MarketTestInt;

public:

	int32 GetTestInt();

	void IncrementTestInt();


	UMarketHistory* Setup(UAll* allRes);
	void UpdateMarket(UAll* allRes);

	UPROPERTY()
		TArray<UMarketItem*> MarketItems;
		
	void LogTrade(FString resFrom, FString resTo, float conversionRate, float amount);

};
