#include "Player.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "raymath.h"

void Player::Init()
{
    Reset();
}

void Player::Reset()
{
    position_ = { 0.0f, 0.0f, 0.0f };
}

// カメラの方向ベクトルを引数で受け取る
void Player::Update(float deltaTime, Vector3 forward, Vector3 right)
{
    Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) moveDir = Vector3Add(moveDir, forward);
    if (IsKeyDown(KEY_S)) moveDir = Vector3Subtract(moveDir, forward);
    if (IsKeyDown(KEY_D)) moveDir = Vector3Add(moveDir, right);
    if (IsKeyDown(KEY_A)) moveDir = Vector3Subtract(moveDir, right);

    // 移動入力がある場合は正規化して移動速度を掛ける
    if (Vector3Length(moveDir) > 0.0f)
    {
        moveDir = Vector3Normalize(moveDir);
        position_ = Vector3Add(position_, Vector3Scale(moveDir, moveSpeed_ * deltaTime));
    }
}

void Player::Draw() const
{
    Model playerModel = ResourceManager::GetInstance().GetModel(ResourceKeys::Model_Player);
    DrawModel(playerModel, position_, 1.0f, WHITE);
}

void Player::End()
{
}