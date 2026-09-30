#pragma once
#include "ICamera.h"

class PlayerCamera : public ICamera {
public:
    PlayerCamera();

    void Update() override;
    void OnActivate() override;
};