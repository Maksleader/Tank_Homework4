// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "TankPawn_Player_Controller.h"
#include "ProjectilePool.h"
#include "Cannon.h"
#include "Projectile.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	TankBody = CreateDefaultSubobject<UStaticMeshComponent>("TankBody");
	TankBody->SetupAttachment(RootComponent);

	TankTurret = CreateDefaultSubobject<UStaticMeshComponent>("TankTurret");
	TankTurret->SetupAttachment(TankBody);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	CannonSetup = CreateDefaultSubobject<UArrowComponent>("CannonSetup");
	CannonSetup->SetupAttachment(TankTurret);

	ObjectPooler = CreateDefaultSubobject<UProjectilePool>(TEXT("ObjectPooler"));
}


void ATankPawn::MoveForward(float Scale)
{
	MoveForwardScale = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RotateScale = Scale;
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		if (Cannon->CurrentAmmo > 0)
		{
			if (!bReadyToFire)
				return;


			Cannon->Fire();
			FTransform SpawnTransform(Cannon->ProjectileSpawnPoint->GetComponentRotation(), Cannon->ProjectileSpawnPoint->GetComponentLocation(), FVector::OneVector);
			AProjectile* PoolableActor = Cast<AProjectile>(ObjectPooler->SpawnProjectile(Cannon->ProjectileClass, SpawnTransform));

			if (PoolableActor == nullptr)
			{
				return;
			}

			else
			{

				PoolableActor->StartMove();
			}
			Cannon->CurrentAmmo--;
		}
		bReadyToFire = false;
		
		GEngine->AddOnScreenDebugMessage(1237, 10, FColor::Green, FString::Printf(TEXT("%f/%f"), Cannon->CurrentAmmo, Cannon->Ammo));
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateUObject(this, &ATankPawn::bIsReadyToFire), 1 / Cannon->FireRate, false);
	}

	
}

void ATankPawn::WeaponSwitch()
{
	
	if (Cannon)
	{
		

		if (CannonClass == CannonClass1)
		{
			
			SetupCannon(CannonClass2);
			

		
			
		}

		else if (CannonClass == CannonClass2)
		{
		
			SetupCannon(CannonClass1);
			//ObjectPooler->DestroyActor();
		}
			
		
	}
	
}
void ATankPawn::SetupCannon(TSubclassOf<ACannon>& CannonType)
{
	
	CannonClass = CannonType;

	if (Cannon)
	{
		Cannon->Destroy();
	}
	auto Transform = CannonSetup->GetComponentTransform();
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, Transform);
	Cannon->AttachToComponent(CannonSetup, FAttachmentTransformRules::SnapToTargetIncludingScale);
	ObjectPooler->DestroyActor();

}
void ATankPawn::bIsReadyToFire()
{
	bReadyToFire = true;
}
// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPawn_Player_Controller>(GetController());
	SetupCannon(CannonClass1);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTank(DeltaTime);
	RotateTank(DeltaTime);
	CanononRotation(DeltaTime);
	GEngine->AddOnScreenDebugMessage(1236, 10, FColor::Green, FString::Printf(TEXT("Time= %f "), GetWorld()->GetTimerManager().GetTimerElapsed(ReloadTimerHandle)));
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveTank(float DeltaTime)
{
	CurrentForwardScale = FMath::Lerp(CurrentForwardScale, MoveForwardScale, ForwardInterpolationKey);
	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector newposition = CurrentLocation + ForwardVector * MoveSpeed * CurrentForwardScale * DeltaTime;

	SetActorLocation(newposition, false);
}

void ATankPawn::RotateTank(float DeltaTime)
{
	CurrentRotateScale = FMath::Lerp(CurrentRotateScale, RotateScale, RotateInterpolationKey);
	float YawRotation = RotateSpeed * CurrentRotateScale * DeltaTime;
	FRotator CurrentRotattion = GetActorRotation();
	YawRotation = CurrentRotattion.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0, YawRotation, 0);
	SetActorRotation(NewRotation);
}

void ATankPawn::CanononRotation(float DeltaTime)
{
	if (!TankController)
		return;

	FRotator OldRotation = TankTurret->GetComponentRotation();

	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TankTurret->GetComponentLocation(), TankController->GetMouseLocation());

	OldRotation.Yaw = TurretRotation.Yaw;
	TurretRotation.Pitch = OldRotation.Pitch;
	TurretRotation.Roll = OldRotation.Roll;

	TankTurret->SetWorldRotation(FMath::Lerp(OldRotation, TurretRotation, TurretRotationInterpolationKey));
}


