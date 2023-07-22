#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

UCLASS()
class WAR_OF_TANKS_1_0_API AAmmoBox : public AActor
{
	GENERATED_BODY()

public:	
	AAmmoBox();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* AmmoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<class ACannon> CannonClass;

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);


};