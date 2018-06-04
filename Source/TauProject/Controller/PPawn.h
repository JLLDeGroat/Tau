// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPawn.generated.h"

UCLASS()
class TAUPROJECT_API APPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spring)
		class USpringArmComponent* SpringArm;



	void MoveCameraForwardInput(float Direction);
	void MoveCameraRightInput(float Direction);


	//Variables
	UPROPERTY(EditAnywhere, Category = Camera)
	float ScrollBoundary;
	//Camera Movement Variable
	FVector2D MovementInput;
	
};
