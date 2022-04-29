// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "TankPawn.generated.h"


class ACannon;
class UProjectilePool;
class ATankPawn_Player_Controller;
UCLASS()
class TANKHOMEWOK4_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TankBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TankTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetup;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret/Cannon")
		TSubclassOf<ACannon>CannonClass1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret/Cannon")
		TSubclassOf<ACannon>CannonClass2;


	UPROPERTY()
		class ACannon* Cannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float ForwardInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotateInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float MoveSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotateSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float RotationInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement/Speed")
		float TurretRotationInterpolationKey = 0.5f;

	UPROPERTY()
		TSubclassOf<ACannon>CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
		UProjectilePool* ObjectPooler;


	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void Fire();
	void WeaponSwitch();
	void SetupCannon(TSubclassOf<ACannon>& CannonType);
	void bIsReadyToFire();

	FTimerHandle ReloadTimerHandle;
	bool bReadyToFire = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	void MoveTank(float DeltaTime);
	void RotateTank(float DeltaTime);
	void CanononRotation(float DeltaTime);



	float MoveForwardScale = 0;
	float CurrentForwardScale = 0;
	float RotateScale = 0;
	float CurrentRotateScale = 0;



	UPROPERTY()
		class ATankPawn_Player_Controller* TankController;

};
