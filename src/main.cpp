#define SDL_MAIN_HANDLED

#include "ImGuiFileDialog.h"

#include "common.hpp"
#include "app_info.hpp"
#include "log_utils.hpp"
#include "time_utils.hpp"

#include "windows/git_window.hpp"
#include "windows/log_window.hpp"
#include "windows/toolbar_window.hpp"
#include "windows/properties_window.hpp"

#include "shaders_program.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include "graphics.hpp"

#include "core.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"

#include "transform_component.hpp"
#include "model_component.hpp"
#include "object.hpp"

int main(int argc, char *argv[]) {
    return meov::core::Core{ std::vector<std::string>{ argv, argv + argc } }.Run();

    // // light shit
    // glm::vec3 lightPos{ 1.f, 1.f, 1.f };
    // bool blinn{ true };  // Use Phong reflection model.

    // // Visibility booleans for windows.
    // bool showCamera{ true };
    // bool showLightning{ true };

    // // Start main loop.
    // LOGI << "Start main loop";
    // while(!done) {

    //     if(showCamera) {
    //         ImGui::Begin("Camera");
    //         auto position{ camera->Position() };
    //         if(ImGui::InputFloat3("Position", glm::value_ptr(position))) {
    //             camera->SetPosition(std::move(position));
    //         }
    //         ImGui::Text("Yaw | Pitch: [%.2f | %.2f]", camera->Yaw(), camera->Pitch());
    //         auto speed{ camera->Speed() };
    //         if(ImGui::InputFloat("Speed", &speed)) {
    //             camera->SetSpeed(speed);
    //         }
    //         auto sensitivity{ camera->MouseSensitivity() };
    //         if(ImGui::InputFloat("Sensitivity", &sensitivity)) {
    //             camera->SetMouseSensitivity(sensitivity);
    //         }
    //         auto zoom{ camera->Zoom() };
    //         if(ImGui::InputFloat("Zoom", &zoom)) {
    //             camera->SetZoom(zoom);
    //         }
    //         ImGui::Text(
    //             "View: [%.2f, %.2f, %.2f, %.2f]\n"
    //             "      [%.2f, %.2f, %.2f, %.2f]\n"
    //             "      [%.2f, %.2f, %.2f, %.2f]",
    //             view[0].x, view[0].y, view[0].z, view[0].w,
    //             view[1].x, view[1].y, view[1].z, view[1].w,
    //             view[2].x, view[2].y, view[2].z, view[2].w);
    //         // ImGui::Text("Object position: [%.2f, %.2f, %.2f]", model[0].w, model[1].w, model[2].w);
    //         ImGui::End();
    //     }
    //     // Draw lightning window.
    //     if(showLightning) {
    //         ImGui::Begin("Lightning");
    //         program->Use();
    //         if(ImGui::InputFloat3("Light position", glm::value_ptr(lightPos)))
    //             program->Get("lightPos")->Set(lightPos);
    //         if(ImGui::Checkbox("Use phong", &blinn))
    //             program->Get("blinn")->Set(blinn);
    //         program->UnUse();
    //         ImGui::End();
    //     }
    // }
}
