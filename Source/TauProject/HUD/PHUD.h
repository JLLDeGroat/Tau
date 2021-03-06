// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Units/Units.h"
#include "Buildings/Building.h"
#include "Controller/ControllerStructs.h"
#include "Resources/Resource.h"
#include "PHUD.generated.h"
/* 
 */
UCLASS()
class TAUPROJECT_API APHUD : public AHUD
{
	GENERATED_BODY()
		
public:

	void BeginPlay() override;
	virtual void DrawHUD() override; // Same As Tick Function

	const APlayerController* ControllerClass;

	FVector2D InitialPoint;
	FVector2D CurrentPoint;
	FVector2D GetMousePosition2D();
	
	bool bIsSelecting;

	//selection
	UPROPERTY()
    TArray <AUnits*> SelectedUnits;
	UPROPERTY()
	TArray <ABuilding*> SelectedBuildings;
	UPROPERTY()
		TArray<AResource*> SelectedResources;
	//TArray <AResources*> SelectedResources;
	//class ABuilding* SelectedBuilding;


	#pragma region HudWidgets
	
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (BlueprintProtected = "true"))
	//	TSubclassOf<class UUserWidget> SelectionHudClass;
	//UPROPERTY()
	//	class UUserWidget* SelectionWidget;


	//UPROPERTY()
	//	TSubclassOf<class UUserWidget> ResourceHudClass;
	//UPROPERTY()
	//	class UUserWidget* ResourceWidget;



	//UPROPERTY()
	//	TSubclassOf<class UUserWidget> BarracksHudClass; 
	//UPROPERTY()
	//	class UUserWidget* BarracksWidget;

	//UPROPERTY()
	//	TSubclassOf<class UUserWidget> DetailsHudClass;
	//UPROPERTY()
	//	class UUserWidget* DetailsWidget;


	UPROPERTY()
		TSubclassOf<class UUserWidget> MainBottomUIHudClass;

	UPROPERTY()
		class UUserWidget* MainBottomWidget;


	void InitializeWidgets();



	#pragma endregion

	void Debug(FString string);

	#pragma region Override Normal RectangleSelection to only get RootComponent UNITS ONLY 

	template <typename ClassFilter>
	bool GetActorsRootInSelectionRectangle(const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<ClassFilter*>& OutActors, bool bIncludeNonCollidingComponents = true, bool bActorMustBeFullyEnclosed = false)
	{
		//Is Actor subclass?
		if (!ClassFilter::StaticClass()->IsChildOf(AActor::StaticClass()))
		{
			return false;
		}

		//Run Inner Function, output to Base AActor Array
		TArray<AActor*> OutActorsBaseArray;
		GetActorsRootInSelectionRectangle(ClassFilter::StaticClass(), FirstPoint, SecondPoint, OutActorsBaseArray, bIncludeNonCollidingComponents, bActorMustBeFullyEnclosed);

		//Construct casted template type array
		for (AActor* EachActor : OutActorsBaseArray)
		{
			OutActors.Add(CastChecked<ClassFilter>(EachActor));
		}

		return true;
	};

	void GetActorsRootInSelectionRectangle(TSubclassOf<class AActor> ClassFilter, const FVector2D& FirstPoint, const FVector2D& SecondPoint,
		TArray<AActor*>& OutActors, bool bIncludeNonCollidingComponents, bool bActorMustBeFullyEnclosed);

	#pragma endregion
};
