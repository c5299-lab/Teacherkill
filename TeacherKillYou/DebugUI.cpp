#include "DebugUI.h"
#include "imgui.h"

void DebugUI::Draw(CameraController& cameraController) {
    ImGui::Begin("Camera Controller");

    bool isPlayer = (cameraController.GetActiveType() == CameraType::Player);

    if (ImGui::RadioButton("Player Camera", isPlayer)) {
        cameraController.SetActiveCamera(CameraType::Player);
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("System Camera", !isPlayer)) {
        cameraController.SetActiveCamera(CameraType::System);
    }

    const auto& cam = cameraController.GetActiveRaylibCamera();
    ImGui::Separator();
    ImGui::Text("Pos   : (%.2f, %.2f, %.2f)", cam.position.x, cam.position.y, cam.position.z);
    ImGui::Text("Target: (%.2f, %.2f, %.2f)", cam.target.x, cam.target.y, cam.target.z);

    ImGui::End();
}