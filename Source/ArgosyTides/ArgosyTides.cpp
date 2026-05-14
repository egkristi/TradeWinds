// Copyright 2026 Argosy Tides. All Rights Reserved.

#include "ArgosyTides.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FArgosyTidesModule"

void FArgosyTidesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	UE_LOG(LogTemp, Log, TEXT("ArgosyTides Module: Loading..."));
}

void FArgosyTidesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	UE_LOG(LogTemp, Log, TEXT("ArgosyTides Module: Unloading..."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FArgosyTidesModule, ArgosyTides)
