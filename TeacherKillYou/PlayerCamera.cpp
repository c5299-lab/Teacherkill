#include "PlayerCamera.h"

PlayerCamera::PlayerCamera() {
    camera_.position = Vector3{ 0.0f, 2.0f, 4.0f };
    camera_.target = Vector3{ 0.0f, 2.0f, 0.0f };
    camera_.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera_.fovy = 60.0f;
    camera_.projection = CAMERA_PERSPECTIVE;
}

void PlayerCamera::Update() {
    UpdateCamera(&camera_, CAMERA_FIRST_PERSON);
}

void PlayerCamera::OnActivate() {
    DisableCursor();
}