#include "skybox_component.hpp"

#include "common.hpp"

#include <vector>

#include "graphics.hpp"
#include "holder.hpp"
#include "mesh.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "vertex.hpp"

#include "model_component.hpp"
#include "shader_component.hpp"

const glm::u8vec4 whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };

namespace meov::core::components {

SkyboxComponent::SkyboxComponent(const fs::path &path)
    : Component{ "Skybox component" }
    , mPath{ path }
    , mSkyboxTexture{ RESOURCES->LoadSkybox(path) } {
}

void SkyboxComponent::PreDraw(Graphics &g) {
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
}

void SkyboxComponent::Draw(Graphics &g) {}

void SkyboxComponent::PostDraw(Graphics &g) {
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void SkyboxComponent::Update(double) {
    if(!mDirtyFlag) {
        return;
    }
    if(auto holder{ mHolder.lock() }; holder) {
        if(auto modelComponent{ holder->GetComponent<components::ModelComponent>() };
           modelComponent && modelComponent->Valid()) {
            modelComponent->Reset(RESOURCES->LoadModel(mPath));
        }
    }
    mDirtyFlag = false;
}

void SkyboxComponent::Serialize() {
    const bool valid{ Valid() };
    if(!valid) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(!ImGui::CollapsingHeader(Name().c_str())) {
        if(!valid) ImGui::PopStyleColor();
        return;
    }
    if(!valid) ImGui::PopStyleColor();

    ImGui::Indent();

    if(valid)
        OnValidSerialize();
    else
        OnInvalidSerialize();

    ImGui::Unindent();
}

bool SkyboxComponent::Valid() const {
    auto holder{ mHolder.lock() };
    return {
        mSkyboxTexture &&
        mSkyboxTexture->Valid() &&
        holder &&
        holder->GetComponent<components::ModelComponent>() &&
        holder->GetComponent<components::ShaderComponent>()
    };
}

void SkyboxComponent::OnInvalidSerialize() {
    auto holder{ mHolder.lock() };
    if(!holder) {
        ImGui::TextColored({ 0.6f, 0.1f, 0.3f, 1.0f }, "I have no holder!!!!!!!!!");
        return;
    }

    const bool hasModelComponent{ !!holder->GetComponent<components::ModelComponent>() };
    const bool hasShaderComponent{ !!holder->GetComponent<components::ShaderComponent>() };

    ImGui::Text("Cannot find the following components:");
    if(!hasModelComponent) {
        ImGui::Text(" -> Model component");
        ImGui::SameLine();
        if(ImGui::Button("Create component##ModelComponent")) {
            holder->AddComponent<components::ModelComponent>(RESOURCES->LoadModel(mPath));
        }
    }
    if(!hasShaderComponent) {
        ImGui::Text(" -> Shader component");
        ImGui::SameLine();
        if(ImGui::Button("Create component##ShaderComponent")) {
            holder->AddComponent<components::ShaderComponent>("shaders/skybox/skybox");
        }
    }
    mDirtyFlag = false;
}

void SkyboxComponent::OnValidSerialize() {
    ImGui::Text("Current texture: %s", mPath.string().c_str());
    const bool isValid{ mSkyboxTexture && mSkyboxTexture->Valid() };
    ImGui::Text("Texture status: %s", isValid ? "valid" : "invalid");

    if(ImGui::Button("Reload mesh?")) {
        mDirtyFlag = true;
    }
}

}  // namespace meov::core::components
