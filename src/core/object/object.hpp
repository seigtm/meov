#pragma once

#include <vector>
#include <string>
#include <memory>

#include "named.hpp"
#include "selectable.hpp"
#include "component.hpp"
#include "holder.hpp"

namespace meov::core {

class Object
    : public mixin::Named,
      public mixin::Selectable,
      public components::Holder {
public:
    explicit Object(std::string &&name);

    virtual void PreDraw(Graphics &g);
    virtual void Draw(Graphics &g);
    virtual void PostDraw(Graphics &g);
    virtual void PreUpdate(double delta);
    virtual void Update(double delta);
    virtual void PostUpdate(double delta);
    virtual void Serialize();  // for ImGui

    bool Enabled() const;
    void Enable();
    void Disable();

private:
    bool mEnabled{ true };
};

}  // namespace meov::core
