#include "shader_window.hpp"

#include "common.hpp"
#include "graphics.hpp"
#include "shaders_program.hpp"
#include "resource_manager.hpp"

namespace meov::Window {

ShaderWindow::ShaderWindow()
    : Base{ "Shader manager" } {}

void ShaderWindow::Select(std::weak_ptr<core::Graphics> &&g) {
    mGraphics = std::move(g);
}

void ShaderWindow::DrawImpl() {
    const auto graphics{ mGraphics.lock() };

    const auto LoadProgram{ [graphics](const std::string_view name, const auto reload) {
        if(const auto program{ RESOURCES->LoadProgram(name, reload) }; program && program->IsValid()) {
            LOGI << "Loaded shader program '" << program->GetName() << "' to the resource manager.";
            graphics->PushProgram(*program);
            LOGI << "Shader program '" << program->GetName() << "' pushed to the graphics object.";
        }
    } };

    ImGui::Text("Current shader program name is '%s'", graphics->CurrentProgram().GetName().c_str());
    static char path[128]{ "" };
    ImGui::InputTextWithHint("Shader program path", "enter directory here", path, IM_ARRAYSIZE(path));

    // TODO: Add ImGui colorizing for buttons.

    if(ImGui::Button("Push shader")) {
        LOGI << "Pushing shader...";
        LoadProgram(path, false);
    }

    if(ImGui::Button("Pop shader")) {
        LOGI << "Popping shader...";
        graphics->PopProgram();
    }

    if(ImGui::Button("Reload shader (F5)")) {
        LOGI << "Reloading shader...";
        LOGW << "           " << ("shaders/" + graphics->CurrentProgram().GetName());
        LoadProgram("shaders/" + graphics->CurrentProgram().GetName(), true);
    }

    if(ImGui::Button("Default shader")) {
        LOGI << "Setting default shader...";
        LoadProgram("shaders/default", true);
    }
}

}  // namespace meov::Window
