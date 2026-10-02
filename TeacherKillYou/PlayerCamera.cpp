#include "PlayerCamera.h"
#include "raymath.h"

PlayerCamera::PlayerCamera() {
    camera_.position = Vector3{ 0.0f, eyeHeight_, 0.0f };
        camera_.target = Vector3{ 0.0f, eyeHeight_, 1.0f };
        camera_.up = Vector3{ 0.0f, 1.0f, 0.0f };
        camera_.fovy = 70.0f;
        camera_.projection = CAMERA_PERSPECTIVE;
}

void PlayerCamera::Update() {
    Vector2 mouseDelta = GetMouseDelta();

        // 1. マウス移動量に合わせて角度（回転）を更新
        yaw_ -= mouseDelta.x * sensitivity_;
        pitch_ -= mouseDelta.y * sensitivity_;

        // 2. 首の可動域制限（上向きと下向きを個別で制限）
        constexpr float maxUpPitch = 1.40f; // 上向きの限界（約80度）
    constexpr float maxDownPitch = -0.80f; // 下向きの限界（約-45度で下に向きすぎないように制限）

    if (pitch_ > maxUpPitch)   pitch_ = maxUpPitch;
        if (pitch_ < maxDownPitch) pitch_ = maxDownPitch;

            // 3. 角度（yaw / pitch）から正面方向ベクトル（forward）を算出
            Vector3 forward = {
                cosf(pitch_) * sinf(yaw_),
                sinf(pitch_),
                cosf(pitch_) * cosf(yaw_)
        };
            forward = Vector3Normalize(forward);

            // 4. カメラ位置をプレイヤーの頭の高さに同期
            camera_.position = Vector3Add(playerPosition_, Vector3{ 0.0f, eyeHeight_, 0.0f });

    // 5. カメラの注視点を設定
    camera_.target = Vector3Add(camera_.position, forward);
}

void PlayerCamera::OnActivate() {
    DisableCursor();
}

Vector3 PlayerCamera::GetForwardVector() const {
    Vector3 forward = { sinf(yaw_), 0.0f, cosf(yaw_) };
        return Vector3Normalize(forward);
}

Vector3 PlayerCamera::GetRightVector() const {
    Vector3 forward = GetForwardVector();
        return Vector3{ forward.z, 0.0f, -forward.x };
}