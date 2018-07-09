// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameMode.h"
#include "Controller/PController.h"
#include "Controller/PPawn.h"
#include "HUD/PHUD.h"
#include "Blueprint/UserWidget.h"

#include "Engine/Engine.h"

ABaseGameMode::ABaseGameMode() {
	DefaultPawnClass = APPawn::StaticClass();
	PlayerControllerClass = APController::StaticClass();
	HUDClass = APHUD::StaticClass();		
}


void ABaseGameMode::BeginPlay() {
	Super::BeginPlay();


	//FStringClassReference MyWidgetClassRef(TEXT("/Game/Blueprints/Widgets/Selection.Selection_C"));
	//if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
	//{
	//	//UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
	//	SelectionWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
	//	SelectionWidget->AddToViewport();
	//	// Do stuff with MyWidget
	//}
	//else {
	//	ShowError("Failed To Get Selection Widget");
	//}

}





void ABaseGameMode::ShowError(FString err) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, err);
}