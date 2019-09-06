
#include "Riders/Classes/Player/Riders_PlayerCameraManager.h"
#include "Riders.h"



ARiders_PlayerCameraManager::ARiders_PlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseClientSideCameraUpdates = false;
	bAlwaysApplyModifiers = true;
}


