#pragma once
#include "raylib.h"

class Stage
{
public:
    Stage() = default;
    ~Stage() = default;

    void Init();
    void Reset();
    void Update(float deltaTime);
    void Draw() const;
    void End();

    // レイキャストを実行し、衝突情報（ヒットした座標や距離）を返す
    RayCollision Raycast(Ray ray) const;

    // 当たり判定（プレイヤーのバウンディングボックスとの衝突チェック）
    bool CheckCollision(BoundingBox playerBox) const;

    Vector3 GetPosition() const { return position_; }
    void SetPosition(Vector3 pos) { position_ = pos; }

    float GetScale() const { return scale_; }
    void SetScale(float scale) { scale_ = scale; }

private:
    Vector3 position_{ 0.0f, 0.0f, 0.0f };
    float scale_{ 1.0f };
};