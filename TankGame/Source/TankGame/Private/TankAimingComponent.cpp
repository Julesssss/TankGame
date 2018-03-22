// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet) {

	Barrel = BarrelToSet;

}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed) {
	// auto TankName = GetOwner()->GetName();
	// auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s, from %s"), *TankName, *WorldSpaceAim.ToString(), * BarrelLocation);


	// UE_LOG(LogTemp, Warning, TEXT("LaunchSpeed: %f"), LaunchSpeed)

	if (!Barrel) return;

	FVector OutLaunchVelocity = FVector(0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::TraceFullPath);
	

	if (HaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *AimDirection.ToString());

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time

}