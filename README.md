# Structures and dependencies of Apple ARKit wrapper in UE4 (temporal solution before the official docs)

* Current early dev branch: https://github.com/EpicGames/UnrealEngine/tree/dev-ar-kit (Apple ARKit support will be released with 4.17 in ~August 2017).

Known issues:
* https://answers.unrealengine.com/oauth/authorized?code=0e85ad4e6a47431397499b69690a1918
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
