#include "CameraController.h"
#include "raylib.h" // キー入力(IsKeyPressed)のために追加

CameraController::CameraController() {
    currentCamera_ = &playerCamera_;
}

void CameraController::Init() {
    if (currentCamera_) {
        currentCamera_->OnActivate(); // InitWindow 後に呼ばれるため正常にカーソルが非表示になる
    }
}

void CameraController::Update() {
// デバッグビルド時のみ K/L キーでの切り替えを有効化
#ifdef _DEBUG
    // Kキーで プレイヤーカメラ に切り替え
    if (IsKeyPressed(KEY_K)) {
        SetActiveCamera(CameraType::Player);
    }
    // Lキーで システム（デバッグ）カメラ に切り替え
    if (IsKeyPressed(KEY_L)) {
        SetActiveCamera(CameraType::System);
    }
#endif

    // 現在のアクティブカメラの更新
    if (activeType_ == CameraType::Player) {
        playerCamera_.Update(); // プレイヤー位置は既に設定されている
    } else if (currentCamera_) {
        currentCamera_->Update();
    }
}

void CameraController::SetActiveCamera(CameraType type) {
    if (activeType_ == type) return;

    if (currentCamera_) {
        currentCamera_->OnDeactivate();
    }

    activeType_ = type;
    currentCamera_ = (activeType_ == CameraType::Player)
        ? static_cast<ICamera*>(&playerCamera_)
        : static_cast<ICamera*>(&systemCamera_);

    currentCamera_->OnActivate();
}

const Camera3D& CameraController::GetActiveRaylibCamera() const {
    return currentCamera_->GetRaylibCamera();
}