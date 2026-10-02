#pragma once
#include "PlayerCamera.h"
#include "SystemCamera.h"

enum class CameraType {
    Player,
    System
};

class CameraController {
public:
    CameraController();
    void Init();
    void Update();
    void SetActiveCamera(CameraType type);

    CameraType GetActiveType() const { return activeType_; }
    const Camera3D& GetActiveRaylibCamera() const;

    PlayerCamera& GetPlayerCamera() { return playerCamera_; }

private:
    PlayerCamera playerCamera_;
    SystemCamera systemCamera_;
    ICamera* currentCamera_{ nullptr };
    CameraType activeType_{ CameraType::Player };
};