// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllerHudMessages.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API UControllerHudMessages : public UObject
{
	GENERATED_BODY()

		UControllerHudMessages();

public:

	UPROPERTY()
		bool bShowMessage;

	UPROPERTY()
		bool bCurrentlyShowingMessage;

	UPROPERTY()
		FString Message;

	UPROPERTY()
		TArray<FString> MessageQueue;

	void MessageShown();
	void ShowMessage(FString Message);
	

	#pragma region Completion Messages
	
	UPROPERTY()
		bool bShowCompletionMessage;

	UPROPERTY()
		bool bCurrentlyShowingCompletionMessage;

	UPROPERTY()
		FString CompletionMessage;

	UPROPERTY()
		TArray<FString> CompletionMessageQueue;


	UFUNCTION(BlueprintCallable)
		bool GetCurrentlyShowingCompletionMessage();

	UFUNCTION(BlueprintCallable)
		bool GetShouldShowCompletionMessage();

	UFUNCTION(BlueprintCallable)
		void SetCurrentlyShowingCompletionMessage(bool val);

	

	UFUNCTION(BlueprintCallable)
		FString GetFirstCompletionMessage();

	int32 GetCompletionMessageQueueCount();
	TArray<FString> GetCompletionMessageQueue();

	void ShowCompletionMessage(FString Message);

	UFUNCTION(BlueprintCallable)
		void FinishedShowingCompletionMessage();
	#pragma endregion
	
};
