#pragma once

#include <memory>
#include <string>
#include "Named.h"

namespace meov::core {

class Graphics;

namespace components {

class Holder;

class Component : public mixin::Named {
public:
    using Shared = std::shared_ptr<Component>;

    explicit Component(std::string &&name);
    virtual ~Component() = default;

    virtual void Draw(Graphics &) = 0;
    virtual void Update(double) = 0;
    virtual void Serialize();  // for ImGui

    void SetHolder(std::weak_ptr<Holder> &&holder);

protected:
    std::weak_ptr<Holder> mHolder;
};

}  // namespace components
}  // namespace meov::core
