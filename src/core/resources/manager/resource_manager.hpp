#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

#include "core/resources/loader/loader.hpp"
#include "core/shaders/shaders_program/shaders_program.hpp"

namespace meov::core::resources {

class Manager {
    template<class T>
    using Resources = std::unordered_map<std::string, std::shared_ptr<T>>;

    Manager();

public:
    ~Manager();

    static Manager *Instance();

    std::shared_ptr<shaders::Program> LoadProgram(fs::path name, bool reload = false);
    std::shared_ptr<Texture> LoadTexture(fs::path name,
                                         Texture::Type type = Texture::Type::Invalid,
                                         bool reload = false);
    std::shared_ptr<Texture> LoadSkybox(fs::path name, bool reload = false);
    std::shared_ptr<Model> LoadModel(fs::path name, bool reload = false);

private:
    const fs::path mResourcesRoot;
    std::shared_ptr<Loader> mLoader;

    Resources<shaders::Program> mPrograms;
    Resources<Texture> mTextures;
    Resources<Model> mModels;
};

}  // namespace meov::core::resources

#define RESOURCES meov::core::resources::Manager::Instance()
