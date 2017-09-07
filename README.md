# ARKit Plugin for UE4 with some fixes

* XCode 9 Beta 6 compatible
* Fixed hardcoded version of hit test

# Structures and dependencies of Apple ARKit wrapper in UE4 (temporal solution before the official docs)

* Current early dev branch: https://github.com/EpicGames/UnrealEngine/tree/dev-ar-kit (Apple ARKit support will be released with 4.17 in ~August 2017).

Known issues:
* https://answers.unrealengine.com/questions/667449/arsample-editor-crashing-after-load.html
* https://answers.unrealengine.com/questions/660723/arkit-arsample-failed-to-compile-global-shader.html

Forum thread:
* https://forums.unrealengine.com/showthread.php?146909-IOS11-ARkit


## ARKit plugin's summary:
```
ARKitCameraComponent = ARKitCamera:
    ARKitHitTestResult[] HitTestAtScreenPoint(HitTestResultType)
    SetOrientationAndPosition()

GetSession() = ARKitSession:
    ARKitHitTestResult[] HitTestAtScreenPoint(HitTestResultType)
    ARKitFrame GetCurrentFrame()
    Run()
    Stop()
    bool IsRunning
    EnablePlaneDetection(bool)
    SetBaseTransform(Transform)
    Transform GetBaseTransform()
    RunWithConfiguration(ARKitSessionConfiguration)
    GetAnchors(ARKitAnchor[])

ARKitFrame:
    ARKit Struct Camera
        Tracking Quality
        Transform
        Resolution
        Focal Length
        Principal Point
    ARKit Light Estimate
        float Intensity

ARKitAnchor:
    Transform
        
ARKitHitTestResult:
    ARKitHitTestResultType
    Distance
    Transform
    Anchor

ARKitHitTestResultType:
    Feature Point
    Estimated Horizontal Plane
    Existing Plane
    Existing Plane Using Extent
```
  
## How to set ARKit camera position
![How to set ARKit camera position](http://i.imgur.com/RuSMcy3.png)
