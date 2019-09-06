
#pragma once

#include "CoreMinimal.h"
#include "Custom/Riders_VehicleTypes.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Riders_VehicleImpactEffect.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ARiders_VehicleImpactEffect : public AActor
{
	GENERATED_BODY()

	// Constructor declaration
	ARiders_VehicleImpactEffect(const FObjectInitializer& ObjectInitializer);

public:

	/** default impact FX used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	UParticleSystem* DefaultFX;

	/** impact FX on asphalt */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* AsphaltFX;

	/** impact FX on dirt */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* DirtFX;

	/** impact FX on water */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* WaterFX;

	/** impact FX on wood */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* WoodFX;

	/** impact FX on stone */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* StoneFX;

	/** impact FX on metal */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* MetalFX;

	/** impact FX on grass */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* GrassFX;

	/** impact FX on gravel */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
		UParticleSystem* GravelFX;

	/** default impact sound used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
		USoundCue* DefaultSound;

	/** impact sound on asphalt */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* AsphaltSound;

	/** impact sound on dirt */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* DirtSound;

	/** impact sound on water */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* WaterSound;

	/** impact sound on wood */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* WoodSound;

	/** impact sound on stone */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* StoneSound;

	/** impact sound on metal */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* MetalSound;

	/** impact sound on grass */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* GrassSound;

	/** impact sound on gravel */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundCue* GravelSound;

	/** impact sound when landing on wheels */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
		USoundCue* WheelLandingSound;

	/** surface data for spawning */
	UPROPERTY()
		FHitResult HitSurface;

	/** impact force */
	UPROPERTY()
		FVector HitForce;

	/** whether impact was coming from landing on wheels (otherwise - hit with body) */
	bool bWheelLand;

	/** spawn effect */
	virtual void PostInitializeComponents() override;

protected:

	/** get FX for material type */
	UParticleSystem* GetImpactFX(TEnumAsByte<EPhysicalSurface> MaterialType);

	/** get sound for material type */
	USoundCue* GetImpactSound(TEnumAsByte<EPhysicalSurface> MaterialType);
	
};

UCLASS(abstract,Blueprintable,BlueprintType,EditInlineNew)
class RIDERS_API UMyConfig : public UObject
{
	GENERATED_BODY()
};

UCLASS(Blueprintable,BlueprintType,abstract,meta = (BlueprintSpawnableComponent))
class RIDERS_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UMyConfig*> Config;
};




