#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class WAR_OF_TANKS_1_0_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	void Start();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveRate = 0.01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Damage = 1;

	FTimerHandle MovementTimer;

	UFUNCTION()
		void Move();

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult);
};