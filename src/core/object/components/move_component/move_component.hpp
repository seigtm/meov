#pragma once

#include <glm/vec3.hpp>
#include <utils/types.hpp>

#include "core/object/components/component.hpp"
#include "core/event_manager/event_manager.hpp"

namespace meov::core::components {

class TransformComponent;

class MoveComponent
    : public Component
    , managers::MouseManager::Listener {
public:
    static constexpr f32 MaxSpeed{ 500.f };
    static constexpr f32 MinSpeed{ 0.1f };
    static constexpr f32 DefaultSpeed{ 10.f };
    static constexpr f32 DeltaSpeed{ 10.f };

    explicit MoveComponent();
    ~MoveComponent() override;

    void Draw(Graphics &g) override;
    void Update(const f64 delta) override;
    void Serialize() override;

    bool Valid() const;

private:
    glm::vec3 mVelocity{};
    f32 mSpeed{ DefaultSpeed };

    glm::vec3 GetDirection(TransformComponent &transform) const;

    void OnMouseScroll(const glm::vec2 &direction) final;
};

}  // namespace meov::core::components
