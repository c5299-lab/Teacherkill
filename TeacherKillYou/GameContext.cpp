#include "GameContext.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ResourceManager.h"

void GameContext::Init() {
    InitWindow(screenWidth_, screenHeight_, u8"学校脱出 3D");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    // アセットの一括ロード（これでキーを使って呼び出せる状態になる）
    RM().LoadAll();
}

void GameContext::Update() {
    cameraController_.Update();
}

void GameContext::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(cameraController_.GetActiveRaylibCamera());
    DrawGrid(20, 1.0f);

    playerModel = RM().GetModel(ResourceKeys::Model_Player);
    DrawModel(playerModel, Vector3{ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

    EndMode3D();

    rlImGuiBegin();
    debugUI_.Draw(cameraController_);
    rlImGuiEnd();

    EndDrawing();
}

void GameContext::End() {
    RM().UnloadAll();

    rlImGuiShutdown();
    CloseWindow();
}