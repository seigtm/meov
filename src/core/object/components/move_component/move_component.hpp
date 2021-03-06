#pragma once

#include <glm/vec3.hpp>

#include "component.hpp"

namespace meov::core::components {

class TransformComponent;

class MoveComponent : public Component {
public:
    explicit MoveComponent();
    ~MoveComponent() override = default;

    void Draw(Graphics &g) override;
    void Update(double delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    glm::vec3 mVelocity{};
    float mSpeed{ 50.f };

    glm::vec3 GetDirection(TransformComponent &transform) const;
};

}  // namespace meov::core::components
