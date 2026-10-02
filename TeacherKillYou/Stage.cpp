#include "Stage.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "raymath.h"

void Stage::Init()
{
    Reset();
}

void Stage::Reset()
{
    position_ = { 0.0f, 0.0f, 0.0f };
    scale_ = 1.0f;
}

void Stage::Update(float deltaTime)
{
}

void Stage::Draw() const
{
    Model stageModel = ResourceManager::GetInstance().GetModel(ResourceKeys::Model_Stage1);
    DrawModel(stageModel, position_, scale_, WHITE);
}

void Stage::End()
{
}

// Raylib標準の GetRayCollisionMesh を使ってレイキャストを実行
RayCollision Stage::Raycast(Ray ray) const
{
    Model stageModel = ResourceManager::GetInstance().GetModel(ResourceKeys::Model_Stage1);

    RayCollision closestHit = { 0 };
    closestHit.hit = false;
    closestHit.distance = 999999.0f; // 最も近い交差距離を保持

    // モデル内の全メッシュに対して交差判定を実施
    for (int i = 0; i < stageModel.meshCount; i++)
    {
        // メッシュとレイの衝突情報を取得
        Matrix transform = MatrixTranslate(position_.x, position_.y, position_.z);
        RayCollision hit = GetRayCollisionMesh(ray, stageModel.meshes[i], transform);

        // ヒットしており、かつこれまでの最小距離より近ければ更新
        if (hit.hit && hit.distance < closestHit.distance)
        {
            closestHit = hit;
        }
    }

    return closestHit;
}