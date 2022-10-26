#pragma once

#include "component.hpp"

#include "common.hpp"
#include "texture.hpp"

namespace meov::core::components {

class SkyboxComponent : public Component {
public:
    SkyboxComponent(const fs::path &path = "models/skybox");
    ~SkyboxComponent() override = default;

    void PreDraw(Graphics &g) override;
    void Draw(Graphics &g) override;
    void PostDraw(Graphics &g) override;
    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    bool mDirtyFlag{ true };

    fs::path mPath;
    std::shared_ptr<Texture> mSkyboxTexture;

    void OnInvalidSerialize();
    void OnValidSerialize();
};

}  // namespace meov::core::components
