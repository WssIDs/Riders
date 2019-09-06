// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "UserWidget.h"
#include "Riders_WorkShopPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RIDERS_API ARiders_WorkShopPlayerController : public APlayerController
{
	GENERATED_BODY()
	
		// Constructor declaration
		ARiders_WorkShopPlayerController(const FObjectInitializer& ObjectInitializer);
	
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UUserWidget* UserWidget;

	/** Player Money */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GamePlay")
	int32 PlayerMoney;

};
