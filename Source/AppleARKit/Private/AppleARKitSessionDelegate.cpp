#if ARKIT_SUPPORT

// AppleARKit
#include "AppleARKit.h"
#include "AppleARKitSessionDelegate.h"
#include "AppleARKitSession.h"

@implementation FAppleARKitSessionDelegate
{
	UAppleARKitSession* _AppleARKitSession;
	CVMetalTextureCacheRef _metalTextureCache;
}



- (id)initWithAppleARKitSession:(UAppleARKitSession*)InAppleARKitSession
{
	self = [super init];
	if (self)
	{
		UE_LOG(LogAppleARKit, Log, TEXT("Delegate created with session: %p"), InAppleARKitSession);
		_AppleARKitSession = InAppleARKitSession;
		_metalTextureCache = NULL;	
	}
	return self;
}

- (void)setMetalTextureCache:(CVMetalTextureCacheRef)InMetalTextureCache
{
	// Release current?
	if ( _metalTextureCache != nullptr )
	{
		CFRelease( _metalTextureCache );
	}
	// Set new & retain
	_metalTextureCache = InMetalTextureCache;
	if ( _metalTextureCache != nullptr )
	{
		CFRetain( _metalTextureCache );
	}
}
#pragma mark - ARSessionDelegate Methods

- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame 
{
	// check if we get an update when the session is not initialized.
	if (!_metalTextureCache)
	{
		UE_LOG(LogAppleARKit, Log, TEXT("Delegate didUpdateFrame with no valid _metalTextureCache (ignoring)"));
		return;
	}

	// Bundle results into FAppleARKitFrame
	TSharedPtr< FAppleARKitFrame, ESPMode::ThreadSafe > AppleARKitFrame( new FAppleARKitFrame( frame, _metalTextureCache ) );
	
	// Pass result to session
	_AppleARKitSession->SessionDidUpdateFrame_DelegateThread( AppleARKitFrame );
}

- (void)session:(ARSession *)session didFailWithError:(NSError *)error
{
	// Log error
	NSString *ErrorDescription = [error localizedDescription];
	UE_LOG( LogAppleARKit, Warning, TEXT("Session failed with error: %s"), *FString(ErrorDescription) );
}

- (void)session:(ARSession *)session didAddAnchors:(NSArray<ARAnchor*>*)anchors 
{
	// Pass updates to sessiom
	_AppleARKitSession->SessionDidAddAnchors_DelegateThread( anchors );
}

- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<ARAnchor*>*)anchors 
{    
	// Pass updates to sessiom
	_AppleARKitSession->SessionDidUpdateAnchors_DelegateThread( anchors );
}

- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<ARAnchor*>*)anchors 
{    
	// Pass updates to sessiom
	_AppleARKitSession->SessionDidRemoveAnchors_DelegateThread( anchors );
}

@end
#endif // ARKIT_SUPPORT

