// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectilePool.generated.h"

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKHOMEWOK4_API UProjectilePool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectilePool();

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		int PoolSize = 5;


	UPROPERTY()
	TArray<AProjectile*> Pool;

	void ReturnObjectToPool(AProjectile* Projectile);
	void DestroyActor();
	AProjectile* SpawnProjectile(TSubclassOf<class AProjectile> PooledObjectSubclass,FTransform& Transform);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	

	int PoolIndex = 0;

};
