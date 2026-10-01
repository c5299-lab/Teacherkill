#include "GameContext.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "raylib.h"

void GameContext::Init()
{
    // カメラコントローラーの初期化（ウィンドウ生成後に呼ばれ、PlayerCameraとカーソル非表示を確定させる）
    cameraController_.Init();
}

void GameContext::Reset()
{

}

void GameContext::Update(float deltaTime)
{
    // カメラの更新（K/Lキーによる切り替えやプレイヤー視点の更新）
    cameraController_.Update();
}

void GameContext::Draw() const
{
    // 3D描画の開始（アクティブなカメラを使用）
    BeginMode3D(cameraController_.GetActiveRaylibCamera());

    DrawGrid(20, 1.0f);

    // プレイヤーモデル等の描画
    Model playerModel = ResourceManager::GetInstance().GetModel(ResourceKeys::Model_Player);
    DrawModel(playerModel, Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

    EndMode3D();
}

void GameContext::End()
{
}