#include "model.hpp"

namespace meov::core {

Model::Model(std::vector<std::shared_ptr<core::Mesh>>&& meshes)
    : mMeshes{ std::move(meshes) } {}

void Model::Draw(core::Graphics& g) const {
    auto wrapper{ MakePushPopWrapper(g) };
    for(auto const& mesh : mMeshes) {
        mesh->Draw(g);
    }
}

const std::vector<std::shared_ptr<Mesh>>& Model::GetMeshes() const {
    return mMeshes;
}

}  // namespace meov::core
