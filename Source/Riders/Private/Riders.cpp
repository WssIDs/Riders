// Copyright 2014 GameTwice, Inc.

#include "Riders.h"

//Custom implementation of the Default Game Module. 
class FRidersGameModule : public FDefaultGameModuleImpl
{
	// Called whenever the module is starting up. In here, we unregister any style sets 
	// (which may have been added by other modules) sharing our 
	// style set's name, then initialize our style set. 
	virtual void StartupModule() override
	{
		//Hot reload hack
	}

	// Called whenever the module is shutting down. Here, we simply tell our MenuStyles to shut down.
	virtual void ShutdownModule() override
	{
	}

}; 

IMPLEMENT_PRIMARY_GAME_MODULE(FRidersGameModule, Riders, "Riders" );


DEFINE_LOG_CATEGORY(RidersLog);
DEFINE_LOG_CATEGORY(SaveGameLog);