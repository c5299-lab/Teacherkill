#include "raylib.h"
#include "GameContext.h"

int main() {
    GameContext gameContext;

    // ウィンドウ初期化と初期セットアップ
    gameContext.Init();

    // メインゲームループ
    while (!WindowShouldClose()) {
        // 更新
        gameContext.Update();

        // 描画（内部で BeginDrawing / EndDrawing が呼ばれます）
        gameContext.Draw();
    }

    // 終了処理
    gameContext.End();

    return 0;
}