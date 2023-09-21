#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ACannon;

UCLASS()
class WAR_OF_TANKS_1_0_API ATankPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY()
		ACannon* Cannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon")
		TSubclassOf<ACannon> CannonClassSecond = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Cannon")
		class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Rotation")
		float TurretRotationInterpolationKey = 0.1f;


	UPROPERTY()
		class ATankPlayerController* TankController;

	float _targetForwardAxisValue;
	float _targetRightAxisValue;
	float _targetRotateRightAxisValue;

public:
	ATankPawn();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void RotateRight(float Value);
	void Fire();
	void SwapCannon();
	void FireSpecial();
	void SetupCannon(TSubclassOf<ACannon> newCannonClass);


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void UpdatePosition(float DeltaTime);


};