#pragma once

#include "component.hpp"

namespace meov::core {
class Graphics;
}  // namespace meov::core


namespace meov::core::components {

class LightingComponent final : public Component {
public:
    explicit LightingComponent(std::weak_ptr<Graphics> &&graphics);
    ~LightingComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::weak_ptr<Graphics> mWeakGraphics;

    bool mEnabled{ true };
    bool mUseBlinnPhongModel{ false };

    bool HasTransformComponent() const;
    bool HasModelComponent() const;
};

}  // namespace meov::core::components
