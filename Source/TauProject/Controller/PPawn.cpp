// Fill out your copyright notice in the Description page of Project Settings.

#include "PPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h "
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Viewport.h"

// Sets default values
APPawn::APPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	#pragma region Setup Root, Camera and Spring Arm

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 3000.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bDoCollisionTest = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	#pragma endregion

	#pragma region Initialize Variables

	ScrollBoundary = 2.0f;

	#pragma endregion

}

// Called when the game starts or when spawned
void APPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);

	UGameViewportClient* GameViewPort = GEngine->GameViewport;

	#pragma region Mouse Edge of Screen Movement

	FVector2D MousePosition;
	FVector2D ViewPortSize;

	GameViewPort->GetViewportSize(ViewPortSize);

	if (GameViewPort->IsFocused(GameViewPort->Viewport) && GameViewPort->GetMousePosition(MousePosition))
	{
		if (MousePosition.X < ScrollBoundary)
		{
			MovementInput.Y = -1;
		}
		else if (ViewPortSize.X - MousePosition.X < ScrollBoundary)
		{
			MovementInput.Y = 1;
		}

		if (MousePosition.Y < ScrollBoundary)
		{
			MovementInput.X = 1;
		}
		else if (ViewPortSize.Y - MousePosition.Y < ScrollBoundary)
		{
			MovementInput.X = -1;
		}
	}

	#pragma endregion

	#pragma region Set And Do Camera Movement
	
	MovementInput = MovementInput.GetSafeNormal() * 100.0f;
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime * 5;
	NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime * 5;
	SetActorLocation(NewLocation);
	
	#pragma endregion
}

// Called to bind functionality to input
void APPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APPawn::MoveCameraForwardInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &APPawn::MoveCameraRightInput);
}

void APPawn::MoveCameraForwardInput(float Direction) {
	MovementInput.X = Direction;
}

void APPawn::MoveCameraRightInput(float Direction) {
	MovementInput.Y = Direction;
}
