#pragma once

#include "component.hpp"

#include "common.hpp"
#include "texture.hpp"

namespace meov::core::components {

class SkyboxComponent : public Component {
public:
    explicit SkyboxComponent(const fs::path &path);
    ~SkyboxComponent() override = default;

    void Draw(Graphics &g) override;
    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    fs::path mPath;
    std::shared_ptr<Texture> mSkyboxTexture;
};

}  // namespace meov::core::components
