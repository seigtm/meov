#include "common.hpp"
#include "shader_component.hpp"

#include "resource_manager.hpp"
#include "shaders_program.hpp"
#include "graphics.hpp"

namespace meov::core::components {

ShaderComponent::ShaderComponent(const fs::path &shaders) noexcept
    : Component{ "Shader component" }
    , mProgram{ RESOURCES->LoadProgram(shaders) }
    , mPath{ shaders }
    , mTargetPath{ shaders.string() } {
    if(Valid()) {
        mStatus = "Loaded successfully";
    } else {
        mStatus = "Failed to load" + mTargetPath;
    }
}

void ShaderComponent::PreDraw(Graphics &g) {
    if(mEnabled && Valid()) {
        g.PushProgram(*mProgram);
        mWasPushed = true;
    }
}

void ShaderComponent::Draw(Graphics &g) {}

void ShaderComponent::PostDraw(Graphics &g) {
    if(mWasPushed) {
        g.PopProgram();
        mWasPushed = false;
    }
}

void ShaderComponent::Update(double) {}

void ShaderComponent::Serialize() {
    if(!Valid()) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        if(!Valid()) ImGui::PopStyleColor();
        return;
    }
    if(!Valid()) ImGui::PopStyleColor();

    ImGui::Indent();

    if(ImGui::Checkbox("Enabled", &mEnabled)) {
        LOGD << "Shader component is" << (mEnabled ? "" : " not") << " active";
    }
    ImGui::SameLine();
    ImGui::Text("(%s)", mEnabled ? "Enabled" : "Disabled");
    if(ImGui::Button("Load")) {
        if(auto texture{ RESOURCES->LoadProgram(mTargetPath) }; texture) {
            mProgram = texture;
            mPath = mTargetPath;
            mStatus = "Loaded successfully";
        } else {
            mStatus = "Failed to load " + mTargetPath;
        }
    }
    ImGui::SameLine();
    ImGui::InputText("Current shader", &mTargetPath);
    ImGui::Text("Status: %s", mStatus.c_str());
    ImGui::Text("Current texture: %s", mPath.string().c_str());

    ImGui::Unindent();
}

bool ShaderComponent::Valid() const {
    return mProgram && mProgram->IsValid();
}

}  // namespace meov::core::components
