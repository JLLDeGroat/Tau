// Fill out your copyright notice in the Description page of Project Settings.

#include "PHUD.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Controller/PController.h"
#include "Units/Units.h"
#include "Blueprint/UserWidget.h"
#include "Controller/ControllerStructs.h"

void APHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bIsSelecting) {
		SelectedUnits.Empty();
		SelectedBuildings.Empty();
		SelectedResources.Empty();

		CurrentPoint = GetMousePosition2D();
		DrawRect(FLinearColor(0, 0, 1, .15), InitialPoint.X, InitialPoint.Y,
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsRootInSelectionRectangle<AUnits>(InitialPoint, CurrentPoint, SelectedUnits, false, false);
		GetActorsInSelectionRectangle<ABuilding>(InitialPoint, CurrentPoint, SelectedBuildings, false, false);
		GetActorsInSelectionRectangle<AResource>(InitialPoint, CurrentPoint, SelectedResources, false, false);		
	}
}

FVector2D APHUD::GetMousePosition2D() {
	float posY; float posX;
	ControllerClass->GetMousePosition(posX, posY);
	return FVector2D(posX, posY);
}



void APHUD::BeginPlay() {
	Super::BeginPlay();
	// HUD STARTED
	// create links to player controller
	ControllerClass = GetOwningPlayerController();
	
	InitializeWidgets();
}

#pragma region Widgets

void APHUD::InitializeWidgets() {

	FStringClassReference BottomUIWidgetClassRef(TEXT("/Game/Blueprints/Widgets/BottomUI.BottomUI_C"));
	if (UClass* BottomUIWidgetClass = BottomUIWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		//UUserWidget* MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
		MainBottomWidget = CreateWidget<UUserWidget>(GetWorld(), BottomUIWidgetClass);
		MainBottomWidget->AddToViewport();
		ShowWidget(MainBottomWidget);
		// Do stuff with MyWidget
	}
	else {
		Debug("Failed To Get Main Bottom Widget");
	}
}

void APHUD::ShowWidget(TEnumAsByte<EWidgets::EWidgetToShow> widget) {
	UUserWidget* widgetToShow = GetWidget(widget);
	ShowWidget(widgetToShow);
}

void APHUD::ShowWidget(UUserWidget* widget) {
	widget->SetVisibility(ESlateVisibility::Visible);
}

void APHUD::HideWidget(UUserWidget* widget) {
	widget->SetVisibility(ESlateVisibility::Hidden);
}

void APHUD::HideWidget(TEnumAsByte<EWidgets::EWidgetToShow> widget) {
	UUserWidget* widgetToHide = GetWidget(widget);
	HideWidget(widgetToHide);
}

void APHUD::HideAllWidgets() {
	//UUserWidget* swidget = GetWidget(EWidgets::EWidgetToShow::W_Selection);
	//UUserWidget* bwidget = GetWidget(EWidgets::EWidgetToShow::W_Barracks);
	//HideWidget(swidget);
	//HideWidget(bwidget);
}

UUserWidget* APHUD::GetWidget(TEnumAsByte<EWidgets::EWidgetToShow> widget) {
	switch (widget) {
		/*case EWidgets::EWidgetToShow::W_Selection:
			return SelectionWidget;
		case EWidgets::EWidgetToShow::W_Barracks:
			return BarracksWidget;
		case EWidgets::EWidgetToShow::W_Details:
			return DetailsWidget;
*/
		case EWidgets::EWidgetToShow::W_None:
			return nullptr;
	}
	return nullptr;
}

#pragma endregion



#pragma region Override Way Rect Gathers Actors

void APHUD::GetActorsRootInSelectionRectangle(TSubclassOf<class AActor> ClassFilter, const FVector2D& FirstPoint, const FVector2D& SecondPoint,
	TArray<AActor*>& OutActors, bool bIncludeNonCollidingComponents, bool bActorMustBeFullyEnclosed)
{
	// Because this is a HUD function it is likely to get called each tick,
	// so make sure any previous contents of the out actor array have been cleared!
	OutActors.Reset();

	//Create Selection Rectangle from Points
	FBox2D SelectionRectangle(ForceInit);

	//This method ensures that an appropriate rectangle is generated, 
	//		no matter what the coordinates of first and second point actually are.
	SelectionRectangle += FirstPoint;
	SelectionRectangle += SecondPoint;


	//The Actor Bounds Point Mapping
	const FVector BoundsPointMapping[8] =
	{
		FVector(1.f, 1.f, 1.f),
		FVector(1.f, 1.f, -1.f),
		FVector(1.f, -1.f, 1.f),
		FVector(1.f, -1.f, -1.f),
		FVector(-1.f, 1.f, 1.f),
		FVector(-1.f, 1.f, -1.f),
		FVector(-1.f, -1.f, 1.f),
		FVector(-1.f, -1.f, -1.f) };

	//~~~

	//For Each Actor of the Class Filter Type
	for (TActorIterator<AActor> Itr(GetWorld(), ClassFilter); Itr; ++Itr)
	{
		AActor* EachActor = *Itr;

		//Get Actor Bounds				//casting to base class, checked by template in the .h
		const FBox EachActorBounds = EachActor->GetRootComponent()->Bounds.GetBox(); /* All Components? */

																					 //Center
		const FVector BoxCenter = EachActorBounds.GetCenter();

		//Extents
		const FVector BoxExtents = EachActorBounds.GetExtent();

		// Build 2D bounding box of actor in screen space
		FBox2D ActorBox2D(ForceInit);
		for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
		{
			// Project vert into screen space.
			const FVector ProjectedWorldLocation = Project(BoxCenter + (BoundsPointMapping[BoundsPointItr] * BoxExtents));
			// Add to 2D bounding box
			ActorBox2D += FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);
		}

		//Selection Box must fully enclose the Projected Actor Bounds
		if (bActorMustBeFullyEnclosed)
		{
			if (SelectionRectangle.IsInside(ActorBox2D))
			{
				OutActors.Add(EachActor);
			}
		}
		//Partial Intersection with Projected Actor Bounds
		else
		{
			if (SelectionRectangle.Intersect(ActorBox2D))
			{
				OutActors.Add(EachActor);
			}
		}
	}
}

#pragma endregion

void APHUD::Debug(FString string) {
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, string);
}