// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Riders_GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARiders_GamePlayerController : public APlayerController
{
	GENERATED_BODY()

	// Constructor declaration
	ARiders_GamePlayerController(const FObjectInitializer& ObjectInitializer);


	TArray<class ARiders_Vehicle*> Vehicles;

public:

	/** Player Money */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		int32 PlayerMoney;

	/** Get All Vehicles*/
	void GetAllVehiclesAround();

	/** Get the vehicle with a minimum distance from the player*/
	ARiders_Vehicle* GetMinDistanceVehicleToPlayer();

	UFUNCTION(BlueprintCallable, Category = "Vehicle")
	virtual void SetSelectedCar();

	/** Ready to Switch Pawn(Vehicle) */
	UPROPERTY(BlueprintReadWrite, Category = "Vehicle")
	bool bReadyToSwitchCar;

	/** Max Iteration distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
		float VehicleIterationDistance;

	/** Selected Pawn(Vehicle) */
	UPROPERTY(BlueprintReadWrite, Category = "Vehicle")
	class ARiders_Vehicle* VehicleObject;

	//virtual void Possess(APawn* aPawn) override;


#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

private:
	virtual void BeginPlay() override;

	void Tick(float DeltaTime) override;


private:


};
