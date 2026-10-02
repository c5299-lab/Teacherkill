#pragma once
#include "raylib.h"

class Stage;

class Player
{
public:
    Player() = default;
    ~Player() = default;

    void Init();
    void Reset();
    // Stageの参照を受け取るように修正
    void Update(float deltaTime, const Stage& stage, Vector3 forward = { 0,0,1 }, Vector3 right = { 1,0,0 });
    void Draw() const;
    void End();

    Vector3 GetPosition() const { return position_; }
    void SetPosition(Vector3 pos) { position_ = pos; }

private:
    Vector3 position_{ 0.0f, 0.0f, 0.0f };
    float moveSpeed_{ 5.0f };

    // プレイヤーの当たり判定用パラメータ（半径と高さ）
    float playerRadius_{ 0.4f }; // 半径（横幅）
    float playerHeight_{ 1.8f }; // 高さ
};