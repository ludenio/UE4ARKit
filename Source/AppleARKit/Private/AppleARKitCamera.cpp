// AppleARKit
#include "AppleARKit.h"
#include "AppleARKitCamera.h"
#include "AppleARKitTransform.h"
	
// UE4
#include "CoreGlobals.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "RenderingCommon.h"

#if ARKIT_SUPPORT

FAppleARKitCamera::FAppleARKitCamera( ARCamera* InARCamera )
{
	// Sanity check
	check( InARCamera );

	// Copy / convert timestamp & camera intrinsics
	FocalLength.X = InARCamera.intrinsics.columns[0][0];
    FocalLength.Y = InARCamera.intrinsics.columns[1][1];
    PrincipalPoint.X = InARCamera.intrinsics.columns[2][0];
    PrincipalPoint.Y = InARCamera.intrinsics.columns[2][1];
    ImageResolution.X = InARCamera.imageResolution.width;
    ImageResolution.Y = InARCamera.imageResolution.height;

    // Copy / convert camera transform
    Transform = FAppleARKitTransform::ToFTransform( InARCamera.transform );
    Translation = Transform.GetTranslation();
	Orientation = Transform.GetRotation();
}

#endif // #ARKIT_SUPPORT

float FAppleARKitCamera::GetAspectRatio() const
{
	return ImageResolution.X / ImageResolution.Y;
}

float FAppleARKitCamera::GetHorizontalFieldOfView() const
{
	return (FocalLength.X > 0.0f)
		? FMath::RadiansToDegrees( 2.0f * FMath::Atan( ( ImageResolution.X / 2.0f ) / FocalLength.X ) )
		: 0.0f;
}

float FAppleARKitCamera::GetVerticalFieldOfView() const
{
	return (FocalLength.Y > 0.0f)
		? FMath::RadiansToDegrees( 2.0f * FMath::Atan( ( ImageResolution.Y / 2.0f ) / FocalLength.Y ) )
		: 0.0f;
}

float FAppleARKitCamera::GetHorizontalFieldOfViewForScreen( EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight ) const
{
	// Sanity check?
	if ( FocalLength.X <= 0.0f )
	{
		return 0.0f;
	}

	// Are they the same aspect ratio anyway?
	float ScreenAspectRatio = ScreenWidth / ScreenHeight;
	float CameraAspectRatio = GetAspectRatio();
	if ( ScreenAspectRatio == CameraAspectRatio )
	{
		return GetHorizontalFieldOfView();
	}

	// Not matching, figure out FOV for fit mode
	switch ( BackgroundFitMode )
	{
		/** The background image will be letterboxed to fit the screen */
		case EAppleARKitBackgroundFitMode::Fit:
		{
			// @todo implement Fir FOV calculation
			return GetHorizontalFieldOfView();
		}
		/** The background will be scaled & cropped to the screen */
		case EAppleARKitBackgroundFitMode::Fill:
		{
			// Is the screen wider than the camera (is the camera taller than the screen)?
			if ( ScreenAspectRatio > CameraAspectRatio )
			{
				// The camera texture will be scaled uniformly to fill the width of the screen, 
				// leaving the full horizonatal FOV visibile
				return GetHorizontalFieldOfView();
			} 
			// The camera is wider than the screen (the screen is taller than the camera)
			else
			{
				// The camera texture will be scaled uniformly to fill the height of the screen.
				// As the camera is wider than the screen, the camera image will extend beyond 
				// the sides of the screen, thus cropping the image & FOV to the screen aspect 
				// ratio.
				const float CroppedImageWidth = ImageResolution.Y * ScreenAspectRatio;
				return FMath::RadiansToDegrees( 2.0f * FMath::Atan( ( CroppedImageWidth / 2.0f ) / FocalLength.X ) );
			}
		}	
		/** The background image will be stretched to fill the screen */
		case EAppleARKitBackgroundFitMode::Stretch:
		{
			return GetHorizontalFieldOfView();
		}
	}

	// Fallback
	return GetHorizontalFieldOfView();
}

FVector2D FAppleARKitCamera::GetImageCoordinateForScreenPosition( FVector2D ScreenPosition, EAppleARKitBackgroundFitMode BackgroundFitMode, float ScreenWidth, float ScreenHeight ) const
{
	// Are they the same aspect ratio anyway?
	float ScreenAspectRatio = ScreenWidth / ScreenHeight;
	float CameraAspectRatio = GetAspectRatio();
	if ( ScreenAspectRatio == CameraAspectRatio )
	{
		// Normalize ScreenPosition by viewport size
		return FVector2D(ScreenPosition.X / ScreenWidth, ScreenPosition.Y / ScreenHeight);
	}

	// Not matching, figure out screen pos for fit mode
	switch ( BackgroundFitMode )
	{
		case EAppleARKitBackgroundFitMode::Fill:
		{
			// Is the screen wider than the camera (is the camera taller than the screen)?
			if ( ScreenAspectRatio > CameraAspectRatio )
			{
				// The camera texture will be scaled uniformly to fill the width of the screen.
				// As the camera is taller than the screen, the camera image will extend beyond 
				// the top and bottom of the screen, thus cropping the image to the screen aspect 
				// ratio.
				float ImageOnScreenHeight = ScreenWidth / CameraAspectRatio;
				return FVector2D(
					ScreenPosition.X / ScreenWidth, 
					( ( ImageOnScreenHeight - ScreenHeight ) / 2.0f + ScreenPosition.Y ) / ImageOnScreenHeight );
			} 
			// The camera is wider than the screen (the screen is taller than the camera)
			else
			{
				// The camera texture will be scaled uniformly to fill the height of the screen.
				// As the camera is wider than the screen, the camera image will extend beyond 
				// the sides of the screen, thus cropping the image to the screen aspect 
				// ratio.
				float ImageOnScreenWidth = ScreenHeight * CameraAspectRatio;
				return FVector2D(
					( ( ImageOnScreenWidth - ScreenWidth ) / 2.0f + ScreenPosition.X ) / ImageOnScreenWidth,
					ScreenPosition.Y / ScreenHeight ); 
			}
		}
	}

	// Fallback to screen space
	return FVector2D( ScreenPosition.X / ScreenWidth, ScreenPosition.Y / ScreenHeight );
}
