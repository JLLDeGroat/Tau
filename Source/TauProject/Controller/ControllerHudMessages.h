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
	
	
};
