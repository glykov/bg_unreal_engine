#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include <Kismet/KismetMathLibrary.h>
#include "Cannon.h"
#include "Components/ArrowComponent.h"


ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	SetupCannon(CannonClass);
}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveRight(float AxisValue)
{
	_targetRightAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float Value)
{
	_targetRotateRightAxisValue = Value;
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePosition(DeltaTime);

	float yawRotation = RotationSpeed * _targetRotateRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation += currentRotation.Yaw;
	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	if (TankController)
	{
		FVector mousePos = TankController->GetMousePosition();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = TurretRotation.Pitch;
		targetRotation.Roll = TurretRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TurretRotationInterpolationKey));

	}
}

void ATankPawn::UpdatePosition(float _DeltaTime)
{
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * _targetForwardAxisValue * _DeltaTime + rightVector * MoveSpeed * _targetRightAxisValue * _DeltaTime;
	SetActorLocation(movePosition, true);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::SwapCannon() 
{
	TSubclassOf<ACannon> TemporaryCannon = CannonClassSecond;
	CannonClassSecond = CannonClass;
	CannonClass = TemporaryCannon;
	SetupCannon(CannonClass);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		Cannon->Destroy();

		return;
	}
	if (Cannon)
	{
		if (CannonClassSecond == nullptr) // Åñëè âòîðîé ñëîò ó ïóøêè ñâîáîäåí, òî ïðè ïîäáîðå ïóøêè îíà âñòàåò íà ïåðâûé ñëîò, à íà÷àëüíàÿ ñäâèãàåòñÿ íà âòîðîé
		{
			CannonClassSecond = CannonClass;
		}
		CannonClass = newCannonClass;
		Cannon->Destroy();
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;
	
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}