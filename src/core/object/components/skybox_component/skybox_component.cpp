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
// #include "shader_component.hpp"


namespace meov::core::components {

SkyboxComponent::SkyboxComponent(const fs::path &path)
    : Component{ "Skybox component" }
    , mPath{ path }
    , mSkyboxTexture{ RESOURCES->LoadSkybox(path) } {
}

void SkyboxComponent::Draw(Graphics &g) {
    if(!Valid())
        return;


    // clang-format on
    // cubeMesh.Draw(g);

    // mSkyboxTexture->Bind(GL_TEXTURE_CUBE_MAP);
    // g.DrawTexture({}, mSkyboxTexture);
}

void SkyboxComponent::Update(double) {
    const static glm::u8vec4 whiteColor{ 1.0f, 1.0f, 1.0f, 1.0f };
    // clang-format off
    const static core::Mesh cubeMesh{ 
        std::vector<core::Vertex>{
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f,  1.0f }, { whiteColor }, {} },
            { { -1.0f,  1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f, -1.0f }, { whiteColor }, {} },
            { { -1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
            { {  1.0f, -1.0f,  1.0f }, { whiteColor }, {} },
    }, {}, { mSkyboxTexture } };
    
    if(mDirtyFlag) {
        if(auto holder{ mHolder.lock() }; holder) {
            if(auto modelComponent{ holder->GetComponent<components::ModelComponent>() };
               modelComponent && modelComponent->Valid()) {
                   modelComponent->Reset(std::make_shared<core::Model>(std::move(cubeMesh)));
            }
        }
    }
    // auto holder{ mHolder.lock() };
    // holder->GetComponent<components::ShaderComponent>();
    // holder->GetComponent<components::ModelComponent>();
}

void SkyboxComponent::Serialize() {
}

bool SkyboxComponent::Valid() const {
    return mHolder.lock() && mSkyboxTexture && mSkyboxTexture->Valid();
}


}  // namespace meov::core::components
