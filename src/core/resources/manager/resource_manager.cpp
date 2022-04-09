#include "common.hpp"

#include "resource_manager.hpp"

#include "assimp_loader.hpp"
#include "texture.hpp"
#include "mesh.h"

namespace meov::core::resources {

Manager::Manager()
    : mResourcesRoot{ fs::current_path() }
    , mLoader(std::make_shared<AssimpLoader>()) {}

Manager::~Manager() {
    for(auto &&program : mPrograms) {
        program.second->Destroy();
    }
}

Manager *Manager::Instance() {
    static Manager manager;
    return &manager;
}

std::shared_ptr<shaders::Program> Manager::LoadProgram(const fs::path &name, bool reload) {
    if(name.empty()) return nullptr;

    if(mPrograms.find(name.string()) == mPrograms.end() || reload) {
        auto program = mLoader->LoadProgram(mResourcesRoot / name);
        if(!program) {
            LOGE << "Error while loading texture " << name.string();
        }
        mPrograms[name.string()] = std::move(program);
    }
    return mPrograms[name.string()];
}

std::shared_ptr<Texture> Manager::LoadTexture(const fs::path &name, Texture::Type type, bool reload) {
    if(!mLoader || name.empty()) return nullptr;

    if(mTextures.find(name.string()) == mTextures.end() || reload) {
        auto texture = mLoader->LoadTexture(mResourcesRoot / name, type);
        if(!texture) {
            LOGE << "Error while loading texture " << name.string();
            return nullptr;
        }
        mTextures[name.string()] = std::move(texture);
    }
    return mTextures[name.string()];
}

std::shared_ptr<Model> Manager::LoadModel(const fs::path &name, bool reload) {
    if(!mLoader || name.empty()) return nullptr;

    if(mModels.find(name.string()) == mModels.end() || reload) {
        auto model = mLoader->LoadModel(mResourcesRoot / name);
        if(!model) {
            LOGE << "Error while loading mesh " << name.string();
            return nullptr;
        }
        mModels[name.string()] = std::move(model);
    }
    return mModels[name.string()];
}

}  // namespace meov::core::resources
