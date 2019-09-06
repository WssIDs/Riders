#pragma once


#include "Riders.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Riders_CheckPoint.generated.h"


UENUM()
namespace ETypeCheckPoint
{
	enum Type
	{
		ETCP_FreeGame,
		ETCP_RaceGame,
	};
}

/**
 * 
 */
UCLASS()
class ARiders_CheckPoint : public AActor
{
	GENERATED_BODY()

	// Constructor declaration
	ARiders_CheckPoint(const FObjectInitializer& ObjectInitializer);

	/* Current CheckPoint Type*/
	UPROPERTY(EditAnywhere, Category = "Type")
	TEnumAsByte<ETypeCheckPoint::Type> TypeCheckPoint;

	float VehicleSpeed;

	/** sphere component */
	UPROPERTY(VisibleAnywhere, Category = "Switch Components")
	USphereComponent* SphereCollision;

	virtual void BeginPlay() override;

	/** called when something overlaps the sphere component */
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
