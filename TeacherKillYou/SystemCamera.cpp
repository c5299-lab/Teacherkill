#include "SystemCamera.h"
#include "raylib.h"
#include "raymath.h"

SystemCamera::SystemCamera() {
    camera_.position = Vector3{ 0.0f, 10.0f, 10.0f };
    camera_.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera_.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera_.fovy = 60.0f;
    camera_.projection = CAMERA_PERSPECTIVE;

    // 初期位置からyaw, pitchを大体計算しておく
    Vector3 dir = Vector3Subtract(camera_.target, camera_.position);
    yaw_ = atan2f(dir.z, dir.x);
    pitch_ = asinf(dir.y / Vector3Length(dir));
}

void SystemCamera::Update() {
    // 1. 右クリックを押している間だけ視点回転を行う
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 mouseDelta = GetMouseDelta();

        // 左右（Unityと同じ：右に動かすと右を向く）
        yaw_ += mouseDelta.x * mouseSensitivity_;

        // 上下も反転（Unityと同じ：上に動かすと上を向く / 下に動かすと下を向く）
        pitch_ -= mouseDelta.y * mouseSensitivity_;

        // ピッチ角の制限（真上・真下を向きすぎてバグるのを防ぐ）
        constexpr float limit = 1.55f; // 約89度
        if (pitch_ > limit)  pitch_ = limit;
        if (pitch_ < -limit) pitch_ = -limit;
    }

    // カメラの向きベクトル（前・右）を計算
    Vector3 forward = {
        cosf(pitch_) * cosf(yaw_),
        sinf(pitch_),
        cosf(pitch_) * sinf(yaw_)
    };
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3CrossProduct(forward, camera_.up);
    right = Vector3Normalize(right);

    // 2. WASDによる水平移動 & Space(上昇) / Shift(下降)
    float dt = GetFrameTime();
    float currentSpeed = moveSpeed_ * dt;

    if (IsKeyDown(KEY_W)) camera_.position = Vector3Add(camera_.position, Vector3Scale(forward, currentSpeed));
    if (IsKeyDown(KEY_S)) camera_.position = Vector3Subtract(camera_.position, Vector3Scale(forward, currentSpeed));
    if (IsKeyDown(KEY_D)) camera_.position = Vector3Add(camera_.position, Vector3Scale(right, currentSpeed));
    if (IsKeyDown(KEY_A)) camera_.position = Vector3Subtract(camera_.position, Vector3Scale(right, currentSpeed));

    // Space: 上昇, Shift: 下降
    if (IsKeyDown(KEY_SPACE)) camera_.position.y += currentSpeed;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) camera_.position.y -= currentSpeed;

    // 3. 常にカメラの注視点を更新
    camera_.target = Vector3Add(camera_.position, forward);
}

void SystemCamera::OnActivate() {
    EnableCursor(); // システムカメラ時はいつでもカーソルを表示・自由移動
}