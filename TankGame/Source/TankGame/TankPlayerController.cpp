// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello Player TankController"))
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) return;

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {

		GetControlledTank()->AimAt(HitLocation);

	}

	// If it hits somthing, controlled tank should point towards it

}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const {

	// Does hitloaction hit terrain?
	OutHitLocation = FVector(1.0);

	// find crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;

	// Get Screen loation
	FVector2D ScreenLocation = FVector2D(
		(CrosshairXLocation * ViewportSizeX),
		(CrosshairYLocation * ViewportSizeY)
	);
	//	UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), * ScreenLocation.ToString());


	// get Look direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

		bool DidHitLocation = GetLookVectorHitLocation(LookDirection, OutHitLocation);


	}

	// Line trace along look direction

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const {

	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)) {
		
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector(1.f);
		return false;
	}
}
