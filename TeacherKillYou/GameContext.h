#pragma once
#include "CameraController.h"
#include "DebugUI.h"

class GameContext {
public:
    GameContext() = default;
    ~GameContext() = default;

    void Init();
    void Update();
    void Draw();
    void End();

private:
    CameraController cameraController_;
    DebugUI debugUI_; // デバッグUIクラスの保持
    const int screenWidth_ = 1280;
    const int screenHeight_ = 720;

    Model playerModel;

    Vector3 position = { 0.0f, 0.0f, 0.0f }; // 原点に配置
    float scale = 1.0f;                      // サイズ（モデルが大きすぎる/小さすぎる場合は調整）
};