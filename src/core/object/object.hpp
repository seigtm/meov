#pragma once

#include <vector>
#include <string>

#include "Named.h"
#include "component.hpp"
#include "holder.hpp"

namespace meov::core {

class Object
    : public mixin::Named,
      public components::Holder {
public:
    explicit Object(std::string &&name);

    virtual void Draw(Graphics &g);
    virtual void Update(double delta);
    virtual void Serialize();  // for ImGui
};

}  // namespace meov::core
