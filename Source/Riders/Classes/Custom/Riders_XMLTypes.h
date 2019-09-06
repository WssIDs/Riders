#include "Riders_XMLTypes.generated.h"
#pragma once



USTRUCT(BlueprintType)
struct FXmlColorData
{
	GENERATED_USTRUCT_BODY();

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XmlData")
		int32 ColumnIndex;

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XmlData")
		int32 RowIndex;

	/* Name of button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XmlData")
		FColor Color;

	FXmlColorData()
	{
		ColumnIndex = 0;
		RowIndex = 0;
	}
};
