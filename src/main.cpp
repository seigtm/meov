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
    // bool showLightning{ true };

    // // Start main loop.
    // LOGI << "Start main loop";
    // while(!done) {
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
