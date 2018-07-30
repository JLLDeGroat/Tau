// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "PlayerResource/All.h"
#include "MarketConversionItem.h"
#include "UObject/NoExportTypes.h"
#include "MarketItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TAUPROJECT_API UMarketItem : public UObject
{
	GENERATED_BODY()
		UMarketItem();

	
	
	UPROPERTY()
		TArray<float> Conversions;
	UPROPERTY()
		float CurrentConversion;

	UPROPERTY()
		TArray<FString> ConversionEvents;

	UPROPERTY()
		FString CurrentEvent;

	UPROPERTY()
		FString resourceFrom;
	UPROPERTY()
		FString resourceTo;

	UPROPERTY()
		float BaseConversionRate;
	UPROPERTY()
		float CurrentConversionRate;

	UPROPERTY()
		float TimesTraded;

public:

	UMarketItem* Setup(FString resFrom, FString resTo, TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier);
	

	void SetCurrentConversion(TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier, bool bIsInitial = false);
	void SetBaseConversionRate(TEnumAsByte<EResourceTier::Tier> fromTier, TEnumAsByte<EResourceTier::Tier> toTier);
	float GetRateFromTier(TEnumAsByte<EResourceTier::Tier> tier);

	void SetResFrom(FString res);

	void SetResTo(FString res);
	
	UFUNCTION(BlueprintCallable)
		float GetCurrentConversion();
	UFUNCTION(BlueprintCallable)
		FString GetResFrom();
	UFUNCTION(BlueprintCallable)
		FString GetResTo();
	UFUNCTION(BlueprintCallable)
		FString GetCurrentEvent();
	UFUNCTION(BlueprintCallable)
		float GetTimesTraded();
	UFUNCTION(Blueprintcallable)
		TArray<float> GetHistoricConversions();
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetHistoricEvents();

	
	void IncrementTimesTraded();

	
};
