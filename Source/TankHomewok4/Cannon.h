// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "DrawDebugHelpers.h"
#include "Cannon.generated.h"


UENUM(BlueprintType)
enum class ECannonType :uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use Projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use Trace")
};

class AProjectile;
class UProjectilePool;

UCLASS()
class TANKHOMEWOK4_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		float FireDamage = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		float Ammo = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		TSubclassOf<AProjectile>ProjectileClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Params")
		float CurrentAmmo = 5.0;

	

	void Fire();
	void Reload();
	void AddAmmo(float& Ammuniton);


	
	//void AddAmmo(float &Ammunition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		class ATankPawn* TankPawn;


};
