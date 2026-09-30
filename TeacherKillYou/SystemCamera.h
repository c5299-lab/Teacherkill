#pragma once
#include "ICamera.h"

class SystemCamera : public ICamera {
public:
    SystemCamera();

    void Update() override;
    void OnActivate() override;

private:
    float moveSpeed_{ 10.0f };   // 移動速度
    float mouseSensitivity_{ 0.003f }; // マウス感度

    // 現在のカメラの向き（ラジアン）
    float yaw_{ 0.0f };
    float pitch_{ 0.0f };
};