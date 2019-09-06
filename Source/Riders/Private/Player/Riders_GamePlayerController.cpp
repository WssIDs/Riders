// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Riders/Classes/Player/Riders_GamePlayerController.h"
#include "Riders.h"
#include "EngineUtils.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"
#include "Player/AI/Riders_AIController.h"
#include "Riders/Classes/Player/Riders_PlayerCameraManager.h"



ARiders_GamePlayerController::ARiders_GamePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ARiders_PlayerCameraManager::StaticClass();

	PlayerMoney = 0;

	VehicleIterationDistance = 500.0f;
}



void ARiders_GamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetIgnoreMoveInput(true);

}


void ARiders_GamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetAllVehiclesAround(); /// function in wip (most CPU used)
}


void ARiders_GamePlayerController::GetAllVehiclesAround()
{
	for (TActorIterator<ARiders_Vehicle> VehicleItr(GetWorld()); VehicleItr; ++VehicleItr)
	{
		if (VehicleItr)
			{
				ARiders_Vehicle* Vehicle = Cast<ARiders_Vehicle>(*VehicleItr);

				if (Vehicle)
				{



					ARiders_AIController* AIController = Cast<ARiders_AIController>(Vehicle->GetController());

					if (!AIController)
					{

						if (Vehicle->IsControlled() == false)
						{
							//UE_LOG(RidersLog, Log, TEXT("Vehicle: %s"), *Vehicle->GetName());
							//UE_LOG(RidersLog, Log, TEXT("Location = %s"), *Vehicle->GetActorLocation().ToString());


							//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Vehicle:")+Vehicle->GetName()+" "+TEXT("Location = ")+Vehicle->GetActorLocation().ToString());

							Vehicles.Add(Vehicle);


						}

					}

				}
			}
	}

	if (Vehicles.Num() > 0)
	{
		VehicleObject = GetMinDistanceVehicleToPlayer();

		ARiders_Vehicle* VH = Cast<ARiders_Vehicle>(GetPawn());

		if (VH)
		{
			if ((VH->GetActorLocation() - VehicleObject->GetActorLocation()).Size() <= VehicleIterationDistance)
			{
				bReadyToSwitchCar = true;

				//UE_LOG(RidersLog, Log, TEXT("Vehicle can switch : %s"), *VehicleObject->GetName());
			}

			else
			{
				bReadyToSwitchCar = false;

				//UE_LOG(RidersLog, Log, TEXT("Vehicle can't switch: %s"), *VehicleObject->GetName());
			}
		}
	}

	Vehicles.Empty();
}

ARiders_Vehicle* ARiders_GamePlayerController::GetMinDistanceVehicleToPlayer()
{

	if (Vehicles.Num() > 0)
	{
		ARiders_Vehicle* MinDistanceVehicle = Vehicles[0];

		ARiders_Vehicle* VH = Cast<ARiders_Vehicle>(GetPawn());

		if (VH)
		{
			float MinDistance = (VH->GetActorLocation() - MinDistanceVehicle->GetActorLocation()).Size();

			for (int32 i = 0; i < Vehicles.Num(); i++)
			{

				float Distance = (VH->GetActorLocation() - Vehicles[i]->GetActorLocation()).Size();

				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					MinDistanceVehicle = Vehicles[i];
				}
			}

			return MinDistanceVehicle;

		}
	}

	return NULL;
}

void ARiders_GamePlayerController::SetSelectedCar()
{
	if (bReadyToSwitchCar)
	{

		ARiders_Vehicle* VH = Cast<ARiders_Vehicle>(GetPawn());

		VH->StopEngineSound();

		VH->FrontLightTurnOff();

		UnPossess();

		SetPawn(VehicleObject);

		Possess(VehicleObject);

		bReadyToSwitchCar = false;

		SetIgnoreMoveInput(true);

	}
}

//void ARiders_GamePlayerController::Possess(APawn* aPawn)
//{
//	Super::Possess(aPawn);
//}


#if WITH_EDITOR

void ARiders_GamePlayerController::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif
