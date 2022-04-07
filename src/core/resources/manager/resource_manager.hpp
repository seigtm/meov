#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

#include "loader.hpp"
#include "ShadersProgram.hpp"

namespace meov::core::resources {

class Manager {
    template<class T>
    using Resources = std::unordered_map<std::string, std::shared_ptr<T>>;

    Manager();

public:
    ~Manager();

    static Manager *Instance();

    std::shared_ptr<shaders::Program> LoadProgram(const std::string &name, bool reload = false);
    std::shared_ptr<Texture> LoadTexture(const std::string &name,
                                         Texture::Type type = Texture::Type::Diffuse,
                                         bool reload = false);
    std::shared_ptr<Model> LoadModel(const std::string &name, bool reload = false);

private:
    const fs::path mResourcesRoot;
    std::shared_ptr<Loader> mLoader;

    Resources<shaders::Program> mPrograms;
    Resources<Texture> mTextures;
    Resources<Model> mModels;
};

}  // namespace meov::core::resources

#define RESOURCES meov::core::resources::Manager::Instance()
