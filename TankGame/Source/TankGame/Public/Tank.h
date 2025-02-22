// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward declaration

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UTankAimingComponent * TankAimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = Setup)

	void SetBarrelReference(UTankBarrel * BarrelToSet);

	void AimAt(FVector WorldSpaceAim);


protected:


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f; // TODO: find sensible default
	
};
