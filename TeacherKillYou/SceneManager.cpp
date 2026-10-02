#include "SceneManager.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ResourceManager.h"
#include "imgui.h"

void SceneManager::Init()
{
    // ウィンドウやImGuiの初期設定はここで行う
    InitWindow(1920, 1080, u8"学校脱出 3D");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    // ImGuiとraylibのカーソル競合を防ぐ設定
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // アセットの一括ロード
    RM().LoadAll();

    // 各シーンにコンテキストを伝搬
    titleScene.SetGameContext(&gameContext);
    gameScene.SetGameContext(&gameContext);

    // 最初はタイトルシーンから開始
    currentScene = &titleScene;
    currentScene->Init();
}

void SceneManager::Shutdown()
{
    RM().UnloadAll();
    rlImGuiShutdown();
    CloseWindow();
}

Scene* SceneManager::GetScene(SceneID id)
{
    switch (id)
    {
    case SceneID::Title: return &titleScene;
    case SceneID::Game:  return &gameScene;
    }
    return &titleScene;
}

void SceneManager::Run()
{
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // 更新
        if (currentScene)
        {
            currentScene->Update(deltaTime);

            if (currentScene->IsFinished())
            {
                currentScene->End();
                Scene* next = currentScene->GetNextScene();
                if (next)
                {
                    currentScene = next;
                    currentScene->Init();
                }
                else
                {
                    break; // 次のシーンがなければ終了
                }
            }
        }

        // 描画
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScene)
        {
            currentScene->Render();
        }

        EndDrawing();
    }
}