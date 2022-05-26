#include "skybox_component.hpp"

#include "common.hpp"
#include "graphics.hpp"
#include "resource_manager.hpp"
#include "vertex.hpp"

namespace meov::core::components {

SkyboxComponent::SkyboxComponent(const fs::path &path)
    : Component{ "Skybox component" }
    , mPath{ path }
    , mSkyboxTexture{ RESOURCES->LoadSkybox(path) } {}

void SkyboxComponent::Draw(Graphics &g) {
    if(!Valid())
        return;
    
}

void SkyboxComponent::Update(double) {
}

void SkyboxComponent::Serialize() {
}

bool SkyboxComponent::Valid() const {
    const auto holder{ mHolder.lock() };
    return holder != nullptr;
}


}  // namespace meov::core::components
