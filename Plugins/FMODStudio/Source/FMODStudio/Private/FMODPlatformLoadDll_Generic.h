// Copyright (c), Firelight Technologies Pty, Ltd. 2012-2019.
#pragma once

void *FMODPlatformLoadDll(const TCHAR *LibToLoad)
{
    return FPlatformProcess::GetDllHandle(LibToLoad);
}

FMOD_RESULT FMODPlatformSystemSetup()
{
    return FMOD_OK;
}