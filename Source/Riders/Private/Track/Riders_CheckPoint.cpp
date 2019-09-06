
#include "Track/Riders_CheckPoint.h"
#include "Pawns/Vehicles/Riders_Vehicle.h"



ARiders_CheckPoint::ARiders_CheckPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<class UParticleSystem> MainPSobject(TEXT("ParticleSystem'/Game/Particles/P_Sparks.P_Sparks'"));

	USceneComponent* SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComp"));
	RootComponent = SceneComponent;

	SphereCollision = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereCapsule"));
	SphereCollision->InitSphereRadius(250.0f);
	SphereCollision->SetupAttachment(RootComponent);


	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ARiders_CheckPoint::OnOverlapBegin);        // set up a notification for when this component overlaps something
	//SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ARiders_CheckPoint::OnOverlap);      // set up a notification for when this component overlaps something
}



void ARiders_CheckPoint::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Create CheckPoint!"));
	}

}


void ARiders_CheckPoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ARiders_Vehicle* RidersVH = Cast<ARiders_Vehicle>(OtherActor);

		
		if (RidersVH)
		{
			if (TypeCheckPoint == ETypeCheckPoint::ETCP_RaceGame)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("CheckPoint RaceGame"));
				RidersVH->VehicleRespawnPosition.SetLocation(RidersVH->GetActorLocation());
				RidersVH->VehicleRespawnPosition.SetRotation((GetActorRotation()).Quaternion());
				RidersVH->VehicleRespawnPosition.SetScale3D(RidersVH->GetActorScale());
				VehicleSpeed = RidersVH->GetVehicleMovement()->GetForwardSpeed();
			}

			if (TypeCheckPoint == ETypeCheckPoint::ETCP_FreeGame)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("CheckPoint FreeGame"));
				RidersVH->VehicleRespawnPosition.SetLocation(RidersVH->GetActorLocation());
				RidersVH->VehicleRespawnPosition.SetRotation((RidersVH->GetActorRotation()).Quaternion());
				RidersVH->VehicleRespawnPosition.SetScale3D(RidersVH->GetActorScale());
			}
		}
		

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Begin Overlap CheckPoint!"));
	}
}


