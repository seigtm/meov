#pragma once

#include "core/object/components/component.hpp"

#include <common>
#include "core/texture/texture.hpp"

namespace meov::core::components {

class SkyboxComponent : public Component {
public:
    explicit SkyboxComponent(const fs::path &path);
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
