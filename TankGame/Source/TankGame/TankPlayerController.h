// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Tank.h>
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
		ATank* GetControlledTank() const;

		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Start moving tank barrel to crosshair
		void AimTowardsCrosshair();
};
