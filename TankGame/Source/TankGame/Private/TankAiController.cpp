// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"

ATank * ATankAiController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAiController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Hello AI TankController"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AI is blind"))
	}
}

ATank * ATankAiController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
