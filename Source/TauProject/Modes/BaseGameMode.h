// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TAUPROJECT_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()


		ABaseGameMode();
public:
	virtual void BeginPlay() override;
	void ShowError(FString err);

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> SelectionHudClass;


	UPROPERTY()
		class UUserWidget* SelectionWidget;*/

};
