#include "model.hpp"

namespace meov::core {

Model::Model(std::vector<std::shared_ptr<core::Mesh>>&& meshes)
    : mMeshes{ std::move(meshes) } {}

void Model::Draw(core::Graphics& g) const {
    for(auto const& mesh : mMeshes) {
        mesh->Draw(g);
    }
}

}  // namespace meov::core
