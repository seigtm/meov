#include "common.hpp"

#include "lighting_component.hpp"
#include "holder.hpp"
#include "graphics.hpp"

#include "transform_component.hpp"
#include "model_component.hpp"

#include "utils/scope_wrapper/scope_wrapper.hpp"

namespace meov::core::components {

LightingComponent::LightingComponent(std::string &&name)
    : Component{ name.empty() ? "Lighting component" : std::move(name) }
    , mEnabled{ true } {
}

void LightingComponent::Serialize() {
    const auto valid{ Valid() };
    if(!valid) ImGui::PushStyleColor(ImGuiCol_Header, { 0.6f, 0.1f, 0.3f, 1.0f });
    if(mSerializerOpened = ImGui::CollapsingHeader(Name().c_str()); !mSerializerOpened) {
        if(!valid) ImGui::PopStyleColor();
        return;
    }

    utils::ScopeWrapper wrapper{
        [name = Name()] {
            ImGui::Indent();
            ImGui::PushID(name.c_str());
        },
        [] {
            ImGui::PopID();
            ImGui::Unindent();
        }
    };


    if(!valid) {
        ImGui::PopStyleColor();
        auto holder{ mHolder.lock() };
        if(holder == nullptr) {
            ImGui::Text("Error! Holder not found!");
            return;
        }
        ImGui::Text("Error! I cannot find the following components:");
        if(!HasTransformComponent()) ImGui::Text("   > Transform component");
        ImGui::Text("Would you like to create them?");
        if(ImGui::Button("Create transform component")) {
            holder->AddComponent<TransformComponent>();
        }
        return;
    }
    ImGui::Checkbox("Enabled", &mEnabled);
    if(ImGui::TreeNode("Phong's variables:")) {
        ImGui::DragFloat3("Ambient", glm::value_ptr(mAmbient), 0.01f, 0.01f, 1.0f);
        ImGui::DragFloat3("Diffuse", glm::value_ptr(mDiffuse), 0.05f, 0.0f, 1.0f);
        ImGui::DragFloat3("Specular", glm::value_ptr(mSpecular), 0.05f, 0.0f, 1.0f);
        ImGui::TreePop();
    }
}

bool LightingComponent::Valid() const {
    return true;
}

void LightingComponent::SetupDefaults(const std::string &name, shaders::Program &program) {
    if(name.empty() || !program.IsValid())
        return;

    program.Get(name + ".enabled")->Set(mEnabled);
    if(mEnabled) {
        program.Get(name + ".params.ambient")->Set(mAmbient);
        program.Get(name + ".params.diffuse")->Set(mDiffuse);
        program.Get(name + ".params.specular")->Set(mSpecular);
    }
}

bool LightingComponent::HasTransformComponent() const {
    if(auto holder{ mHolder.lock() }; holder)
        return holder->GetComponent<TransformComponent>() != nullptr;
    return false;
}

//================================= DirectionalLightingComponent =================================//

bool DirectionalLightingComponent::sInstanced{ false };

DirectionalLightingComponent::DirectionalLightingComponent(glm::vec3 &&dir)
    : LightingComponent{ "Directional lighting component" }
    , mDirection{ std::move(dir) } {
    assert(!sInstanced);
    mAmIExcess = sInstanced;
    sInstanced = true;
}

DirectionalLightingComponent::~DirectionalLightingComponent() {
    sInstanced = false;
}

void DirectionalLightingComponent::PreDraw(Graphics &g) {
    if(mAmIExcess || !Valid())
        return;

    auto program{ g.CurrentProgram() };
    if(!program.IsValid())
        return;
    program.Use();
    SetupDefaults("dirLight", program);
    if(mEnabled)
        program.Get("dirLight.direction")->Set(mDirection);
    program.UnUse();
}

void DirectionalLightingComponent::Serialize() {
    if(mAmIExcess) {
        ImGui::TextColored({ 0.9f, 0.1f, 0.1f, 1.0f }, "I am excess!!!");
        return;
    }
    LightingComponent::Serialize();
    if(!Valid() || !mSerializerOpened)
        return;

    ImGui::Indent();
    ImGui::DragFloat3("Direction", glm::value_ptr(mDirection));
    ImGui::Unindent();
}

//==================================== PointLightingComponent ====================================//

PointLightingComponent::ControlBlock PointLightingComponent::sControl{};

PointLightingComponent::PointLightingComponent()
    : LightingComponent{ "Point lighting component" } {
    if(!sControl.mInitialized) {
        sControl.mUsing.fill(false);
        sControl.mInitialized = true;
    }

    for(int i{}; i < sControl.mUsing.size(); ++i) {
        if(!sControl.mUsing[i]) {
            mId = i;
            sControl.mUsing[i] = true;
            break;
        }
    }

    mTextureName = "pointLight[" + std::to_string(mId) + "]";
}

PointLightingComponent::~PointLightingComponent() {
    if(mId >= 0 && mId <= sControl.mUsing.size())
        sControl.mUsing[mId] = false;
}

void PointLightingComponent::PreDraw(Graphics &g) {
    if(!Valid())
        return;

    auto program{ g.CurrentProgram() };
    if(!program.IsValid())
        return;
    program.Use();
    SetupDefaults(mTextureName, program);
    if(mEnabled) {
        auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };
        const glm::vec3 position{ transform ? transform->GetPosition() : glm::vec3{} };
        program.Get(mTextureName + ".position")->Set(position);
        program.Get(mTextureName + ".constant")->Set(mConstant);
        program.Get(mTextureName + ".linear")->Set(mLinear);
        program.Get(mTextureName + ".quadratic")->Set(mQuadratic);
    }
    program.UnUse();
}

void PointLightingComponent::Serialize() {
    LightingComponent::Serialize();
    if(!Valid() || !mSerializerOpened)
        return;

    ImGui::Indent();
    ImGui::PushID(mTextureName.c_str());
    ImGui::DragFloat("Constrain", &mConstant);
    ImGui::DragFloat("Linear", &mLinear);
    ImGui::DragFloat("Quadratic", &mQuadratic, 0.2f, 0.0f, 1.0f);
    ImGui::PopID();
    ImGui::Unindent();
}

//===================================== SpotLightingComponent ====================================//

bool SpotLightingComponent::sInstanced{ false };

SpotLightingComponent::SpotLightingComponent(glm::vec3 &&dir)
    : LightingComponent{ "Directional lighting component" }
    , mDirection{ std::move(dir) } {
    assert(!sInstanced);
    mAmIExcess = sInstanced;
    sInstanced = true;
}

SpotLightingComponent::~SpotLightingComponent() {
    sInstanced = false;
}

void SpotLightingComponent::PreDraw(Graphics &g) {
    if(mAmIExcess || !Valid())
        return;

    auto program{ g.CurrentProgram() };
    if(!program.IsValid())
        return;
    program.Use();
    SetupDefaults("spotLight", program);
    if(mEnabled) {
        auto transform{ mHolder.lock()->GetComponent<TransformComponent>() };
        const glm::vec3 position{ transform ? transform->GetPosition() : glm::vec3{} };
        program.Get("spotLight.position")->Set(position);
        program.Get("spotLight.direction")->Set(mDirection);
        program.Get("spotLight.cutOff")->Set(mCutOff);
        program.Get("spotLight.outerCutOff")->Set(mOuterCutOff);
        program.Get("spotLight.constant")->Set(mConstant);
        program.Get("spotLight.linear")->Set(mLinear);
        program.Get("spotLight.quadratic")->Set(mQuadratic);
    }
    program.UnUse();
}

void SpotLightingComponent::Serialize() {
    if(mAmIExcess) {
        ImGui::TextColored({ 0.9f, 0.1f, 0.1f, 1.0f }, "I am excess!!!");
        return;
    }
    LightingComponent::Serialize();
    if(!Valid() || !mSerializerOpened)
        return;

    ImGui::Indent();
    ImGui::DragFloat3("Direction", glm::value_ptr(mDirection));
    ImGui::DragFloat("Constrain", &mConstant);
    ImGui::DragFloat("Linear", &mLinear);
    ImGui::DragFloat("Quadratic", &mQuadratic, 0.2f, 0.0f, 1.0f);
    float angle{ glm::degrees(mCutOff) };
    if(ImGui::DragFloat("Cut off degrees", &angle, 1.0f, 0.0f, 90.0f)) {
        mCutOff = glm::cos(glm::radians(angle));
    }
    angle = glm::degrees(mOuterCutOff);
    if(ImGui::DragFloat("Outer cut off degrees", &angle, 1.0f, 0.0f, 90.0f)) {
        mOuterCutOff = glm::cos(glm::radians(angle));
    }
    ImGui::Unindent();
}


}  // namespace meov::core::components
