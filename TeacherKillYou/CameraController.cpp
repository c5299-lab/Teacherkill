#include "CameraController.h"

CameraController::CameraController() {
    currentCamera_ = &playerCamera_;
    currentCamera_->OnActivate();
}

void CameraController::Update() {
    if (currentCamera_) {
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