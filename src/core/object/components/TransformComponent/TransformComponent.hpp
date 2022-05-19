#pragma once

#include "component.hpp"
#include "Transformable.h"

namespace meov::core::components {

class TransformComponent final
    : public Component,
      public mixin::Transformable {
public:
    TransformComponent();
    ~TransformComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;
};

}  // namespace meov::core::components
