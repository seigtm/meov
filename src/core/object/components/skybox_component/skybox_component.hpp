#pragma once

#include <utils/types.hpp>
#include "core/object/components/component.hpp"

namespace meov::core::resources {
class Texture;
} // namespace meov::core::resources

namespace meov::core::components {

class SkyboxComponent : public Component {
public:
    explicit SkyboxComponent(const fs::path &path);
    ~SkyboxComponent() override = default;

    void PreDraw(Graphics &g) override;
    void Draw(Graphics &g) override;
    void PostDraw(Graphics &g) override;
    void Update(const f64 delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    bool mDirtyFlag{ true };

    fs::path mPath;
    sptr<resources::Texture> mSkyboxTexture;

    void OnInvalidSerialize();
    void OnValidSerialize();
};

}  // namespace meov::core::components
