// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/EnemyObject.h"
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
	virtual void Tick(float DeltaTime) override;
	void ShowError(FString err);

	
	UPROPERTY()
		UEnemyObject* EnemyClass;

	UFUNCTION(BlueprintCallable, category = "Base Game Mode")
		UEnemyObject* GetEnemyClass();

};
