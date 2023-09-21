#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

UCLASS()
class WAR_OF_TANKS_1_0_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		ATankPawn* TankPawn;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePos; };

protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void RotateRight(float Value);
	void SwapCannon();

	void Fire();
	void FireSpecial();

	FVector MousePos;
	
};