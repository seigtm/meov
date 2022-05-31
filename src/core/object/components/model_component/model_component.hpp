#pragma once

#include "component.hpp"

#include "model.hpp"

namespace meov::core::components {

class ModelComponent : public Component {
public:
    explicit ModelComponent(const fs::path &model);
    explicit ModelComponent(const std::shared_ptr<core::Model> &model);
    ~ModelComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;

    bool Reset(const std::shared_ptr<core::Model> &model);
    bool Valid() const;

private:
    std::shared_ptr<Model> mModel;
    std::string mSelectedTextureType;

    void Serialize(const std::shared_ptr<Mesh> &mesh);
};

}  // namespace meov::core::components
