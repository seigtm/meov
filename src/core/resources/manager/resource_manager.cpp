#include "common.hpp"

#include "resource_manager.hpp"

#include "assimp_loader.hpp"
#include "texture.hpp"
#include "mesh.hpp"

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

std::shared_ptr<shaders::Program> Manager::LoadProgram(const fs::path &path, bool reload) {
    if(path.empty()) return nullptr;

    const auto name{ path.stem().string() };
    if(mPrograms.find(name) == mPrograms.end() || reload) {
        auto program = mLoader->LoadProgram(mResourcesRoot / path);
        if(!program) {
            LOGE << "Error while loading texture " << path.string();
        }
        mPrograms[name] = std::move(program);
    }
    return mPrograms[name];
}

std::shared_ptr<Texture> Manager::LoadTexture(const fs::path &path, Texture::Type type, bool reload) {
    if(!mLoader || path.empty()) return nullptr;

    const auto name{ path.stem().string() };
    if(mTextures.find(name) == mTextures.end() || reload) {
        auto texture = mLoader->LoadTexture(mResourcesRoot / path, type);
        if(!texture) {
            LOGE << "Error while loading texture " << path.string();
            return nullptr;
        }
        mTextures[name] = std::move(texture);
    }
    return mTextures[name];
}

std::shared_ptr<Model> Manager::LoadModel(const fs::path &path, bool reload) {
    if(!mLoader || path.empty()) return nullptr;

    const auto name{ path.stem().string() };
    if(mModels.find(name) == mModels.end() || reload) {
        auto model = mLoader->LoadModel(mResourcesRoot / path);
        if(!model) {
            LOGE << "Error while loading mesh " << path.string();
            return nullptr;
        }
        mModels[name] = std::move(model);
    }
    return mModels[name];
}

}  // namespace meov::core::resources
