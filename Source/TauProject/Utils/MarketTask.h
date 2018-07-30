// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreGlobals.h"
#include "Runtime/Core/Public/Async/AsyncWork.h"
#include "Controller/MarketHistory.h"
#include "PlayerResource/All.h"
#include "Controller/PController.h"
#include "CoreMinimal.h"
/**
 * 
 */


namespace MarketPlaceTask
{
	static void CalculateMarketOptions(APController* control, UMarketHistory* marketHistory, UAll* allRes, bool IsStartup) {
		if (IsStartup) { // starting up the marketplace
			marketHistory->Setup(allRes);


			for (int32 i = 0; i < marketHistory->MarketItems.Num(); i++) {
				UMarketItem* item = marketHistory->MarketItems[i];

				
				FString log  = item->GetResFrom() + " " + item->GetResTo() + " at a rate of " + 
					FString::SanitizeFloat(item->GetCurrentConversion()) + " trading is: " + item->GetCurrentEvent();

				const TCHAR* logItem = *log;

				UE_LOG(LogTemp, Warning, TEXT("___ %s ____"), logItem);
			}
				

		}
		else { // updating the market place			
			marketHistory->UpdateMarket(allRes);
		}
	}
}








class MarketTask : public FNonAbandonableTask
{
	UMarketHistory* marketHistory;
	UAll* allRes;
	APController* controller;
	bool bIsStartup;
		
public:
	
	
	/*Default constructor*/
	MarketTask();
	~MarketTask();

	
	MarketTask(APController* control, UMarketHistory* MH, UAll* allres, bool startup = false) {
		marketHistory = MH;
		allRes = allres;
		bIsStartup = startup;
		controller = control;
	}

	/*This function is needed from the API of the engine.
	My guess is that it provides necessary information
	about the thread that we occupy and the progress of our task*/
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MarketTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	/*This function is executed when we tell our task to execute*/
	void DoWork()
	{
		MarketPlaceTask::CalculateMarketOptions(controller, marketHistory, allRes, bIsStartup);

		UE_LOG(LogTemp, Warning, TEXT("--------------------------------------------------------------------"));
		UE_LOG(LogTemp, Warning, TEXT("End or Market Thread"));
		UE_LOG(LogTemp, Warning, TEXT("--------------------------------------------------------------------"));
	}
};

