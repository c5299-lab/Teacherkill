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
    position_ = { 0.0f, 0.0f, 0.0f };
    velocity_ = { 0.0f, 0.0f, 0.0f };
    isGrounded_ = false;
}

void Player::Update(float deltaTime, const Stage& stage, Vector3 forward, Vector3 right)
{
    // ----------------------------------------------------
    // 移動入力
    // ----------------------------------------------------
    Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_W))
        moveDir = Vector3Add(moveDir, forward);

    if (IsKeyDown(KEY_S))
        moveDir = Vector3Subtract(moveDir, forward);

    if (IsKeyDown(KEY_A))
        moveDir = Vector3Add(moveDir, right);

    if (IsKeyDown(KEY_D))
        moveDir = Vector3Subtract(moveDir, right);

    // ----------------------------------------------------
    // 水平移動
    // ----------------------------------------------------
    if (Vector3Length(moveDir) > 0.0f)
    {
        moveDir = Vector3Normalize(moveDir);

        Vector3 moveAmount =
            Vector3Scale(moveDir, moveSpeed_ * deltaTime);

        float checkDistance = playerRadius_;

        // X方向
        if (moveAmount.x != 0.0f)
        {
            Vector3 direction =
            { moveAmount.x > 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f };

            Vector3 rayPosition =
                Vector3Add(position_, { 0.0f, 0.8f, 0.0f });

            Ray ray = { rayPosition, direction };
            RayCollision hit = stage.Raycast(ray);

            if (!hit.hit || hit.distance > checkDistance)
            {
                position_.x += moveAmount.x;
            }
        }

        // Z方向
        if (moveAmount.z != 0.0f)
        {
            Vector3 direction =
            { 0.0f, 0.0f, moveAmount.z > 0.0f ? 1.0f : -1.0f };

            Vector3 rayPosition =
                Vector3Add(position_, { 0.0f, 0.8f, 0.0f });

            Ray ray = { rayPosition, direction };
            RayCollision hit = stage.Raycast(ray);

            if (!hit.hit || hit.distance > checkDistance)
            {
                position_.z += moveAmount.z;
            }
        }
    }

    // ----------------------------------------------------
    // ジャンプ
    // ----------------------------------------------------
    if (IsKeyDown(KEY_SPACE) && isGrounded_)
    {
        velocity_.y = jumpForce_;
        isGrounded_ = false;
    }

    // ----------------------------------------------------
    // 重力
    // ----------------------------------------------------
    if (!isGrounded_)
    {
        velocity_.y += gravity_ * deltaTime;
    }

    // ----------------------------------------------------
    // Y方向移動
    // ----------------------------------------------------
    position_.y += velocity_.y * deltaTime;

    // ----------------------------------------------------
    // 地面判定
    // ----------------------------------------------------
    Vector3 rayPosition =
        Vector3Add(position_, { 0.0f, 1.0f, 0.0f });

    Ray downRay =
    {
        rayPosition,
        { 0.0f, -1.0f, 0.0f }
    };

    RayCollision groundHit = stage.Raycast(downRay);

    if (groundHit.hit)
    {
        float groundY =
            (position_.y + 1.0f) - groundHit.distance;

        if (position_.y <= groundY + 0.01f)
        {
            position_.y = groundY;
            velocity_.y = 0.0f;
            isGrounded_ = true;
        }
        else
        {
            isGrounded_ = false;
        }
    }
    else
    {
        isGrounded_ = false;
    }
}

void Player::Draw() const
{
    Model playerModel =
        ResourceManager::GetInstance().GetModel(ResourceKeys::Model_Player);

    DrawModel(playerModel, position_, 1.0f, WHITE);
}

void Player::End()
{}