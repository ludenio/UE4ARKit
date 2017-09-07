// AppleARKit
#include "AppleARKit.h"
#include "AppleARKitBlueprintFunctionLibrary.h"
#include "AppleARKitSession.h"

UAppleARKitSession* UAppleARKitBlueprintFunctionLibrary::GetSession()
{
	return FAppleARKitModule::Get().GetSession();
}

float UAppleARKitBlueprintFunctionLibrary::GetAspectRatio( const FAppleARKitCamera& Camera )
{
	return Camera.GetAspectRatio();
}

float UAppleARKitBlueprintFunctionLibrary::GetHorizontalFieldOfView( const FAppleARKitCamera& Camera )
{
	return Camera.GetHorizontalFieldOfView();
}

float UAppleARKitBlueprintFunctionLibrary::GetVerticalFieldOfView( const FAppleARKitCamera& Camera )
{
	return Camera.GetVerticalFieldOfView();
}

float UAppleARKitBlueprintFunctionLibrary::GetHorizontalFieldOfViewForScreen( const FAppleARKitCamera& Camera, EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight )
{
	return Camera.GetHorizontalFieldOfViewForScreen( BackgroundFitMode, ScreenWidth, ScreenHeight );
}
