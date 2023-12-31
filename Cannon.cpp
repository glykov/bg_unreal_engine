#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"



ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	bReadyToFire = true;
	
}

void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}
	
	if (currentAmmo > 0)
	{
		if (CannonType == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Purple, "Fire projectile");
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
			if (Projectile)
			{
				Projectile->Start();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "Fire trace");
			
			FHitResult hitResult;
			FCollisionQueryParams traceParams = FCollisionQueryParams();
			traceParams.AddIgnoredActor(this);
			traceParams.bReturnPhysicalMaterial = false;

			FVector Start = ProjectileSpawnPoint->GetComponentLocation();
			FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

			if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
			{
				DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Red, false, 1, 0, 5);
				if (hitResult.GetActor())
				{
					AActor* OverlappedActor = hitResult.GetActor();
					UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *OverlappedActor->GetName());
					OverlappedActor->Destroy();
				}
			}
			else
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 1, 0, 5);

			}

		}
		currentAmmo--;
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Ammo: %d"), currentAmmo));
	} 
	else 
	{
		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
	}
}

void ACannon::FireSpecial()
{
	CannonType = ECannonType::FireTrace;
	Fire();
	CannonType = ECannonType::FireProjectile;
}


bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::Reload()
{
	currentAmmo = 10;
	bReadyToFire = true;

}