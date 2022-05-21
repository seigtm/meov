#define SDL_MAIN_HANDLED

#include "common.hpp"
#include "core.hpp"

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
