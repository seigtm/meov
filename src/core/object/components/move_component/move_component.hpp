#pragma once

#include <glm/vec3.hpp>
#include <utils/types.hpp>

#include "core/object/components/component.hpp"

namespace meov::core::components {

class TransformComponent;

class MoveComponent : public Component {
public:
    explicit MoveComponent();
    ~MoveComponent() override = default;

    void Draw(Graphics &g) override;
    void Update(const f64 delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    glm::vec3 mVelocity{};
    f32 mSpeed{ 10.f };

    glm::vec3 GetDirection(TransformComponent &transform) const;
};

}  // namespace meov::core::components
