#pragma once

#include "core/object/components/component.hpp"
#include "core/mixins/transformable.hpp"

namespace meov::core::components {

class TransformComponent final
    : public Component,
      public mixin::Transformable {
public:
    TransformComponent();
    ~TransformComponent() override = default;

    void PreDraw(Graphics &) override;
    void PostDraw(Graphics &) override;
    void Serialize() override;

private:
    bool mWasPushed{ false };
};

}  // namespace meov::core::components
