// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Projectile.h"




// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	//ObjectPooler = CreateDefaultSubobject<UProjectilePool>(TEXT("ObjectPooler"));

}


void ACannon::Fire()
{
	if (CurrentAmmo > 0)
	{
		/*if (!bReadyToFire)
			return;*/
		if (Type == ECannonType::FireProjectile)
		{
		
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Use FireProjectile")));
		}

		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString(TEXT("Use FirTrace")));
			FHitResult Result;
			FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
			TraceParams.bTraceComplex = true;
			TraceParams.bReturnPhysicalMaterial = false;
			FVector start = ProjectileSpawnPoint->GetComponentLocation();
			FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
			if (GetWorld()->LineTraceSingleByChannel(Result, start, end, ECC_Visibility, TraceParams))
			{
				DrawDebugLine(GetWorld(), start, Result.Location, FColor::Red, false, 0.5f, 0, 5);
			}

			if (Result.Actor.Get())
			{
				Result.Actor.Get()->Destroy();
			}

			else
			{
				DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
			}



		}

		
		
	}

	
}



void ACannon::Reload()
{
	CurrentAmmo = Ammo;
}

void ACannon::AddAmmo(float& Ammunition)
{

	CurrentAmmo = +Ammunition;
}





// Called when the game starts or when spawned
void ACannon::BeginPlay()
{

	Super::BeginPlay();
	
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	


}

