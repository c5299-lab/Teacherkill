#pragma once
#include "raylib.h"

class ICamera {
public:
    virtual ~ICamera() = default;

    virtual void Update() = 0;
    virtual void OnActivate() {}
    virtual void OnDeactivate() {}

    const Camera3D& GetRaylibCamera() const { return camera_; }
    Camera3D& GetRaylibCamera() { return camera_; }

protected:
    Camera3D camera_{};
};