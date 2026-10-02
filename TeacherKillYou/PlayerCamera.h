#pragma once
#include "ICamera.h"

class PlayerCamera : public ICamera {
public:
    PlayerCamera();

    // インターフェースのオーバーライド（1つに集約）
    void Update() override;

    void OnActivate() override;

    Vector3 GetForwardVector() const;
    Vector3 GetRightVector() const;

    // プレイヤーの位置を設定するヘルパーメソッド
    void SetPlayerPosition(Vector3 pos) { playerPosition_ = pos; }

private:
    Vector3 playerPosition_{ 0.0f, 0.0f, 0.0f }; // 追従対象の位置
    float eyeHeight_{ 1.6f };       // 目線の高さ（160cm付近）
    float sensitivity_{ 0.0025f };  // マウス感度

    // カメラの現在の角度（ラジアン）5
    float yaw_{ 0.0f };             // 水平角度
    float pitch_{ 0.0f };           // 垂直角度
};