#include "Common.hpp"

#include "resource_manager.hpp"

#include "assimp_loader.hpp"
#include "texture.h"
#include "mesh.h"

namespace meov::core::resources {

Manager::Manager()
    : mResourcesRoot{ fs::current_path() }
    , mLoader(std::make_shared<AssimpLoader>()) {}

Manager::~Manager() {
    for(auto &&program : mPrograms) {
        // program->Destroy();
        program.second->Destroy();
    }
}

Manager *Manager::Instance() {
    static Manager manager;
    return &manager;
}

std::shared_ptr<shaders::Program> Manager::LoadProgram(const std::string &name, bool reload) {
    if(name.empty()) return nullptr;

    if(mPrograms.find(name) == mPrograms.end() || !reload) {
        auto program = mLoader->LoadProgram(mResourcesRoot / name);
        if(!program) {
            LOGE << "Error while loading texture " << name;
        }
        mPrograms[name] = std::move(program);
    }
    return mPrograms[name];
}

std::shared_ptr<Texture> Manager::LoadTexture(const std::string &name, Texture::Type type, bool reload) {
    if(!mLoader || name.empty()) return nullptr;

    if(mTextures.find(name) == mTextures.end() || !reload) {
        auto texture = mLoader->LoadTexture(mResourcesRoot / name, type);
        if(!texture) {
            LOGE << "Error while loading texture " << name;
            return nullptr;
        }
        mTextures[name] = std::move(texture);
    }
    return mTextures[name];
}

std::shared_ptr<Model> Manager::LoadModel(const std::string &name, bool reload) {
    if(!mLoader || name.empty()) return nullptr;

    if(mModels.find(name) == mModels.end() || !reload) {
        auto model = mLoader->LoadModel(mResourcesRoot / name);
        if(!model) {
            LOGE << "Error while loading mesh " << name;
            return nullptr;
        }
        mModels[name] = std::move(model);
    }
    return mModels[name];
}

}  // namespace meov::core::resources
