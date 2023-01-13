#include "core/model/model.hpp"

namespace meov::core {

Model::Model(std::vector<std::shared_ptr<core::Mesh>>&& meshes)
    : resources::Resource{ std::string{ "model" } }, mMeshes{ std::move(meshes) } {}

void Model::Draw(core::Graphics& g) const {
    g.DrawModel(*this);
}

const std::vector<std::shared_ptr<Mesh>>& Model::GetMeshes() const {
    return mMeshes;
}

}  // namespace meov::core
