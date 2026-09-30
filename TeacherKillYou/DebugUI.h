#pragma once
#include "CameraController.h"

class DebugUI {
public:
    DebugUI() = default;
    ~DebugUI() = default;

    void Draw(CameraController& cameraController);
};