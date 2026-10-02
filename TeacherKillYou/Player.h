#pragma once
#include "raylib.h"

class Player
{
public:
    Player() = default;
    ~Player() = default;

    void Init();
    void Reset();
    void Update(float deltaTime, Vector3 forward = { 0,0,1 }, Vector3 right = { 1,0,0 });
    void Draw() const;
    void End();

    // ゲッター / セッター
    Vector3 GetPosition() const { return position_; }
    void SetPosition(Vector3 pos) { position_ = pos; }

private:
    Vector3 position_{ 0.0f, 0.0f, 0.0f };
    float moveSpeed_{ 5.0f }; // 移動速度
};