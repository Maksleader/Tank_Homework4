// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponBox.generated.h"

class ATankPawn;
class ACannon;
class UProjectilePool;
UCLASS()
class TANKHOMEWOK4_API AWeaponBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBox();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon>CannonClass;


	UPROPERTY()
		UProjectilePool* ObjectPooler;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const
			FHitResult& SweepResult);
private:
	UPROPERTY()
    ATankPawn* playerPawn;

	UPROPERTY()
		ACannon* Cannon;
};
