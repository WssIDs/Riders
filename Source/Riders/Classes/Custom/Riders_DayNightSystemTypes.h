#pragma once


#include "Riders_DayNightSystemTypes.generated.h"



USTRUCT(BlueprintType)
struct FTime
{
	GENERATED_USTRUCT_BODY()

		/** Hour */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (UIMin = "0", UIMax = "24"))
		int32 Hours;

	/** Minutes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (UIMin = "0", UIMax = "60"))
		int32 Minutes;

	/** Seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (UIMin = "0", UIMax = "60"))
		int32 Seconds;
};

UENUM(BlueprintType)
enum class ETimesOfDay : uint8
{
	DNS_Day		UMETA(DisplayName = "Day"),
	DNS_Night	UMETA(DisplayName = "Night"),
};

UENUM(BlueprintType)
enum class ETimesOfYear : uint8
{
	DNS_Spring,
	DNS_Summer,
	DNS_Autumn,
	DNS_Winter,
};


UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	DNS_Clear,
	DNS_SmallCloudy,
	DNS_MeduimCloudy,
	DNS_HighCloudy,
	DNS_Overcast,
	DNS_SmallRain,
	DNS_MeduimRain,
	DNS_HighRain,
	DNS_SmallStorm,
	DNS_MediumStorm,
	DNS_HighStorm,
};
