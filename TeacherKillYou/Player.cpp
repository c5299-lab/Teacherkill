#include "Player.h"
#include "Stage.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "raymath.h"

void Player::Init()
{
    Reset();
}

void Player::Reset()
{
    // 階段やテーブルの近くなど、スタート位置を少し浮かせて設定
    position_ = { 0.0f, 0.5f, 0.0f };
}

void Player::Update(float deltaTime, const Stage& stage, Vector3 forward, Vector3 right)
{
    Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) moveDir = Vector3Add(moveDir, forward);
    if (IsKeyDown(KEY_S)) moveDir = Vector3Subtract(moveDir, forward);
    if (IsKeyDown(KEY_D)) moveDir = Vector3Add(moveDir, right);
    if (IsKeyDown(KEY_A)) moveDir = Vector3Subtract(moveDir, right);

    if (Vector3Length(moveDir) > 0.0f)
    {
        moveDir = Vector3Normalize(moveDir);
        Vector3 moveAmount = Vector3Scale(moveDir, moveSpeed_ * deltaTime);

        // ----------------------------------------------------
        // 1. 壁との距離判定（レイキャストによる移動制御）
        // ----------------------------------------------------
        float checkDistance = 0.5f; // プレイヤーの体から壁までの限界距離（半径）

        // --- X軸移動のレイキャストチェック ---
        if (moveAmount.x != 0.0f)
        {
            Vector3 xDir = { (moveAmount.x > 0.0f) ? 1.0f : -1.0f, 0.0f, 0.0f };
            // 腰の高さ（y + 0.8f 付近）から移動方向へレイを発射
            Ray xRay = { Vector3Add(position_, Vector3{ 0.0f, 0.8f, 0.0f }), xDir };
            RayCollision hit = stage.Raycast(xRay);

            // 壁に衝突していない、または壁までの距離がチェック距離より遠ければ移動許可
            if (!hit.hit || hit.distance > checkDistance)
            {
                position_.x += moveAmount.x;
            }
        }

        // --- Z軸移動のレイキャストチェック ---
        if (moveAmount.z != 0.0f)
        {
            Vector3 zDir = { 0.0f, 0.0f, (moveAmount.z > 0.0f) ? 1.0f : -1.0f };
            Ray zRay = { Vector3Add(position_, Vector3{ 0.0f, 0.8f, 0.0f }), zDir };
            RayCollision hit = stage.Raycast(zRay);

            if (!hit.hit || hit.distance > checkDistance)
            {
                position_.z += moveAmount.z;
            }
        }
    }

    // ----------------------------------------------------
    // 2. 床の高低差・接地処理（真下へのレイキャスト）
    // ----------------------------------------------------
    // プレイヤーの腰の高さから真下（-Y方向）へレイを発射
    Ray downRay = { Vector3Add(position_, Vector3{ 0.0f, 1.0f, 0.0f }), Vector3{ 0.0f, -1.0f, 0.0f } };
    RayCollision groundHit = stage.Raycast(downRay);

    if (groundHit.hit)
    {
        // レイの発射点（Y+1.0）からヒット地点までの距離から、正確な床の高さ（Y座標）を算出
        float groundY = (position_.y + 1.0f) - groundHit.distance;

        // 床の高さに合わせてプレイヤーのY座標を補正（坂道や階段にも自動で沿うようになります）
        position_.y = groundY;
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