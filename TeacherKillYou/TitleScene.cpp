#include "TitleScene.h"
#include "SceneManager.h"

void TitleScene::Init()
{
    finished = false;
    nextScene = nullptr;
    // タイトル時はマウスカーソルを表示状態にする
    EnableCursor();
}

void TitleScene::Update(float deltaTime)
{
    // スペースキーまたは画面クリックでゲームシーンへ遷移
    if (IsKeyPressed(KEY_SPACE))
    {
        SetNextScene(SceneManager::GetInstance().GetScene(SceneID::Game));
    }
}

void TitleScene::Render() const
{
    ClearBackground(RAYWHITE);
    DrawText("ESCAPE SCHOOL 3D", 750, 400, 40, DARKGRAY);
    DrawText("PRESS SPACE TO START", 780, 500, 20, GRAY);
}

void TitleScene::End()
{
}