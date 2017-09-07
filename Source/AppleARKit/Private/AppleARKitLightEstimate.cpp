// AppleARKit
#include "AppleARKit.h"
#include "AppleARKitLightEstimate.h"

#if ARKIT_SUPPORT

FAppleARKitLightEstimate::FAppleARKitLightEstimate( ARLightEstimate* InARLightEstimate )
{
	bIsValid = InARLightEstimate != nullptr;
	AmbientIntensity = InARLightEstimate != nullptr ? InARLightEstimate.ambientIntensity : 0.0f;
}

#endif // #ARKIT_SUPPORT
