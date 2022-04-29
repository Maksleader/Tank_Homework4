// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBox.h"
#include "TankPawn.h"
#include "Cannon.h"
#include "Projectile.h"
#include "ProjectilePool.h"
// Sets default values
AWeaponBox::AWeaponBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject < USceneComponent>("Root");
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBox::OnMeshOverlapBegin);
	Mesh->SetCollisionProfileName(FName("Overlap All"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AWeaponBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (OtherActor == playerPawn)
	{
		

		if (playerPawn->CannonClass == playerPawn->CannonClass1)
		{
			playerPawn->CannonClass1 = CannonClass;
			playerPawn->ATankPawn::SetupCannon(playerPawn->CannonClass1);
			//ObjectPooler->DestroyActor();

		}

		else if (playerPawn->CannonClass == playerPawn->CannonClass2)
		{
			playerPawn->CannonClass2 = CannonClass;
			playerPawn->ATankPawn::SetupCannon(playerPawn->CannonClass2);
			//ObjectPooler->DestroyActor();
	

		}

		Destroy();
	}
}



