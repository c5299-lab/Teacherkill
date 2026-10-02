#include "GameContext.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "raylib.h"

void GameContext::Init()
{
    // カメラコントローラーの初期化（ウィンドウ生成後に呼ばれ、PlayerCameraとカーソル非表示を確定させる）
    cameraController_.Init();
	player_.Init();
}

void GameContext::Reset()
{
	player_.Reset();
}

void GameContext::Update(float deltaTime)
{
    // 1. カメラの向きに合わせてプレイヤーを動かす
    Vector3 forward = cameraController_.GetPlayerCamera().GetForwardVector();
    Vector3 right = cameraController_.GetPlayerCamera().GetRightVector();
    player_.Update(deltaTime, forward, right);

    // 2. プレイヤーの移動後位置をカメラに教える
    cameraController_.GetPlayerCamera().SetPlayerPosition(player_.GetPosition());

    // 3. カメラ全体のUpdate（Update() 1つのみ）を呼ぶ
    cameraController_.Update();
}

void GameContext::Draw() const
{
    BeginMode3D(cameraController_.GetActiveRaylibCamera());

    DrawGrid(20, 1.0f);

    player_.Draw();

    EndMode3D();
}

void GameContext::End()
{
    player_.End();
}