// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn_Player_Controller.generated.h"

/**
 * 
 */
class ATankPawn;
UCLASS()
class TANKHOMEWOK4_API ATankPawn_Player_Controller : public APlayerController
{
	GENERATED_BODY()
public:
	ATankPawn_Player_Controller();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	FVector GetMouseLocation()
	{
		return MouseLocation;
	};
protected:
	virtual void BeginPlay() override;
	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void Fire();
	void WeaponSwitch();

	UPROPERTY()
		FVector MouseLocation;
private:
	UPROPERTY()
		class ATankPawn* TankPawn;
};
