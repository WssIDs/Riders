// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "AssetPtr.h"
#include "Riders_HUD.generated.h"

/**
 * 
 */
UCLASS()
class ARiders_HUD : public AHUD
{
	GENERATED_BODY()

	// Constructor declaration
	ARiders_HUD();


	virtual void BeginPlay() override;

	virtual void DrawHUD() override;
	
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* UserWidget;

	UFUNCTION(BlueprintCallable, Category = "Behavior")
	UUserWidget* GetUserWidget()
	{
		return UserWidget;
	}

	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void SetUserWidget(UUserWidget* inWidget)
	{
		UserWidget = inWidget;
	}

};
