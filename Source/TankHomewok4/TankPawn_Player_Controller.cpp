// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn_Player_Controller.h"
#include "TankPawn.h"

ATankPawn_Player_Controller::ATankPawn_Player_Controller()
{

}

void ATankPawn_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPawn_Player_Controller::MoveForward);
	InputComponent->BindAxis("RotateRight", this, &ATankPawn_Player_Controller::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn_Player_Controller::Fire);
	InputComponent->BindAction("Weapon Switch", IE_Pressed, this, &ATankPawn_Player_Controller::WeaponSwitch);
	bShowMouseCursor = true;
}

void ATankPawn_Player_Controller::Tick(float DeltaTime)
{
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	auto Z = FMath::Abs(TankPawn->GetActorLocation().Z - MouseLocation.Z);
	MouseLocation = MouseLocation - MouseDirection * Z / MouseDirection.Z;
}

void ATankPawn_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPawn_Player_Controller::MoveForward(float Scale)
{
	if (TankPawn)
		TankPawn->MoveForward(Scale);
}

void ATankPawn_Player_Controller::RotateRight(float Scale)
{
	if (TankPawn)
		TankPawn->RotateRight(Scale);
}

void ATankPawn_Player_Controller::Fire()
{
	if (TankPawn)
		TankPawn->Fire();
}

void ATankPawn_Player_Controller::WeaponSwitch()
{
	if (TankPawn)
		TankPawn->WeaponSwitch();
}
