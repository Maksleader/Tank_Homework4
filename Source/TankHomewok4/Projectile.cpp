// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "ProjectilePool.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* scenecoponent = CreateDefaultSubobject<USceneComponent>("scenecoponent");
	RootComponent = scenecoponent;
	//Collision = CreateDefaultSubobject<USphereComponent>("Collison");
	//RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AProjectile::StartMove()
{
	SetActive(true);
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, Rate, true);
}

void AProjectile::StopMove()
{
	SetActive(false);
	GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());
	OtherActor->Destroy();
	StopMove();

}

void AProjectile::Move()
{
	FVector start = GetActorLocation();
	FVector end = GetActorForwardVector() * Speed * Rate;
	FVector move = start + end;
	SetActorLocation(move);
	if (FVector::Distance(start, end) > FlyRange)
	{
		ObjectPooler->ReturnObjectToPool(this);
		
	}

}

void AProjectile::SetActive(bool InpActive)
{
	Active = InpActive;
	Mesh->SetHiddenInGame(!InpActive);
	if(InpActive==false)
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	else
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}







bool AProjectile::IsActive()
{
	return Active;
}




// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

