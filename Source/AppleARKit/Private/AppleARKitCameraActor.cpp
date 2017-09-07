// AppleARKitPlugin
#include "AppleARKit.h"
#include "AppleARKitCameraActor.h"
#include "AppleARKitCameraComponent.h"

AAppleARKitCameraActor::AAppleARKitCameraActor(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
  : Super(
  		ObjectInitializer.SetDefaultSubobjectClass<UAppleARKitCameraComponent>("CameraComponent")
  	)
{
}
