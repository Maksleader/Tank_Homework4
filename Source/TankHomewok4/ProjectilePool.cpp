// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"
#include "Projectile.h"
#include "TankPawn.h"
#include "Cannon.h"

// Sets default values for this component's properties
UProjectilePool::UProjectilePool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UProjectilePool::ReturnObjectToPool(AProjectile* Projectile)
{
	Projectile->StopMove();
}

void UProjectilePool::DestroyActor()
{

	//AProjectile *PoolableActor = nullptr;
	TArray<AProjectile*>PoolRef = Pool;
	if (Pool.Num()>0)
	{
		for (AProjectile* PoolableActor : PoolRef)
		{
			Pool.Pop();
			PoolableActor->Destroy();
		}
	}
}

AProjectile* UProjectilePool::SpawnProjectile(TSubclassOf<class AProjectile> PooledObjectSubclass, FTransform& Transform)
{
	AProjectile* PoolableActor = nullptr;
	TArray<AProjectile*>PoolRef =Pool;
	if (PooledObjectSubclass != NULL)
	{
		
		/* Check for a valid World */
		UWorld* const World = GetWorld();

		if (World)
		{

			/* Spawn objects, make them 'inactive' and add them to pool */

			if (PoolRef.Num() == PoolSize)
			{
				if (PoolIndex == PoolSize)
				{
					PoolIndex = 0;
					PoolableActor = PoolRef[PoolIndex];
					PoolIndex++;
					PoolableActor->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
					PoolableActor->SetActive(true);
				}

				else
				{
					PoolableActor = PoolRef[PoolIndex];
					PoolIndex++;
					PoolableActor->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
					PoolableActor->SetActive(true);
				}
					              
			}
			
			
			else
			{

				PoolableActor = Cast<AProjectile>(GetWorld()->SpawnActor(PooledObjectSubclass, &Transform));
				PoolableActor->SetActive(false);
				Pool.Add(PoolableActor);

			}
			

		}


	}
	return PoolableActor;
}


// Called when the game starts
void UProjectilePool::BeginPlay()
{




	//if (PooledObjectSubclass != NULL)
	//{
	//	AProjectile* PoolableActor = nullptr;
	//	/* Check for a valid World */
	//	UWorld* const World = GetWorld();


	//
	//	
	//	
	//		if (World)
	//		{

	//			/* Spawn objects, make them 'inactive' and add them to pool */
	//			

	//				for (int i = 0; i < PoolSize; i++)
	//				{

	//					PoolableActor = World->SpawnActor<AProjectile>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
	//					PoolableActor->SetActive(false);
	//					Pool.Add(PoolableActor);
	//					
	//				}
	//			
	//		}
	//	
	//	
	//}
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProjectilePool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

