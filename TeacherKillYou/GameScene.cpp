#include "GameScene.h"
#include "SceneManager.h"

void GameScene::Init()
{
    finished = false;
    nextScene = nullptr;

    // ゲームコンテキスト側の初期化（カメラコントローラーやステージの準備）
    if (gameContext)
    {
        gameContext->Init();
    }
}

void GameScene::Update(float deltaTime)
{
    if (gameContext)
    {
        gameContext->Update(deltaTime);
    }

    // Bキーでタイトルに戻る（デバッグ用など）
    if (IsKeyPressed(KEY_B))
    {
        SetNextScene(SceneManager::GetInstance().GetScene(SceneID::Title));
    }
}

void GameScene::Render() const
{
    if (gameContext)
    {
        gameContext->Draw();
    }
}

void GameScene::End()
{
    if (gameContext)
    {
        gameContext->End();
    }
}