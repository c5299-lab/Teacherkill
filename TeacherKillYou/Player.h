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
    Vector3 velocity_{ 0.0f, 0.0f, 0.0f };
    float moveSpeed_{ 5.0f };

    // プレイヤーの当たり判定用パラメータ（半径と高さ）
    float playerRadius_{ 0.4f }; // 半径（横幅）
    float playerHeight_{ 1.8f }; // 高さ

	//プレイヤーの重力加速度
	float gravity_{ -9.81f }; // 重力加速度
	float jumpForce_{ 3.0f }; // ジャンプ力

	bool isGrounded_{ false }; // 地面に接地しているかどうかのフラグ

};