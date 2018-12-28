// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameMode.h"
#include "Controller/PController.h"
#include "Controller/PPawn.h"
#include "HUD/PHUD.h"
#include "Blueprint/UserWidget.h"

#include "Engine/Engine.h"

ABaseGameMode::ABaseGameMode() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);

	DefaultPawnClass = APPawn::StaticClass();
	PlayerControllerClass = APController::StaticClass();
	HUDClass = APHUD::StaticClass();		
}


void ABaseGameMode::BeginPlay() {
	Super::BeginPlay();

	EnemyClass = NewObject<UEnemyObject>();
	EnemyClass->Setup(GetWorld());	
}


void ABaseGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);


	EnemyClass->GetCountDownObject()->UpdateCountDown(DeltaTime);
	EnemyClass->TryDoEscalation();
	EnemyClass->GetEnemySpawnObject()->TrySpawnEnemyUnit(EnemyClass);

}


UEnemyObject* ABaseGameMode::GetEnemyClass() {
	return EnemyClass;
}


void ABaseGameMode::ShowError(FString err) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, err);
}

