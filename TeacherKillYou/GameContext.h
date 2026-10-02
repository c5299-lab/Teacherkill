#pragma once
#include "CameraController.h"
#include "Player.h"
#include "Stage.h"

class GameContext
{
public:
    GameContext() = default;
    ~GameContext() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;
    void End();

    CameraController& GetCameraController() { return cameraController_; }
    const CameraController& GetCameraController() const { return cameraController_; }

private:
    CameraController cameraController_;
    Player player_;
    Stage stage_;
};