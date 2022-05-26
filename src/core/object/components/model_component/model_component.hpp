#pragma once

#include "component.hpp"

#include "model.hpp"

namespace meov::core::components {

class ModelComponent : public Component {
public:
    explicit ModelComponent(const fs::path &model);
    ~ModelComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;

    bool Reset(const std::shared_ptr<core::Model> &model);
    bool Valid() const;

private:
    fs::path mPath;
    std::shared_ptr<Model> mModel;
};

}  // namespace meov::core::components
