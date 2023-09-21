#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class WAR_OF_TANKS_1_0_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void FireSpecial();
	bool IsReadyToFire();
	void Reload();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float Damage = 1;

	bool bReadyToFire = true;
	FTimerHandle ReloadTimer;

	int currentAmmo = 10;

};