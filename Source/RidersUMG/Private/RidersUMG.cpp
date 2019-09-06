// Fill out your copyright notice in the Description page of Project Settings.

#include "RidersUMG.h"
#include "UI/Styles/RidersStyles.h"
#include "Modules/ModuleManager.h"


class RidersUMGModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		FSlateStyleRegistry::UnRegisterSlateStyle("RidersStyle");
		FRidersStyle::Initialize();

		FSlateStyleRegistry::UnRegisterSlateStyle("RidersUMGStyle");
		FRidersUMGStyle::Initialize();

		UE_LOG(RidersUMGLog, Log, TEXT("RidersUMGModule Inititalized"));
	}

	virtual void ShutdownModule() override
	{
		FRidersStyle::Shutdown();

		FRidersUMGStyle::Shutdown();

		UE_LOG(RidersUMGLog, Log, TEXT("RidersUMGModule Shutdown"));
	}
};




IMPLEMENT_PRIMARY_GAME_MODULE(RidersUMGModule, RidersUMG, "RidersUMG" );

DEFINE_LOG_CATEGORY(RidersUMGLog);