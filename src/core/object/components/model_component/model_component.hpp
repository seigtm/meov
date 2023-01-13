#pragma once

#include <utils/types.hpp>
#include "core/object/components/component.hpp"

namespace meov::core {
class Mesh;
class Model;
} // namespace meov::core


namespace meov::core::components {

class ModelComponent : public Component {
public:
    explicit ModelComponent(const fs::path &model);
    explicit ModelComponent(const sptr<core::Model> &model);
    ~ModelComponent() override = default;

    void Draw(Graphics &) override;
    void Update(const f64 delta) override;
    void Serialize() override;

    bool Reset(const sptr<core::Model> &model);
    bool Valid() const;

private:
    sptr<Model> mModel;
    std::string mSelectedTextureType;

    void Serialize(const sptr<Mesh> &mesh);
    void ShowChangeModelDialog();
};

}  // namespace meov::core::components
