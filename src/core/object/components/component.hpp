#pragma once

#include <memory>
#include <string>

#include "core/mixins/named.hpp"

namespace meov::core {

class Graphics;

namespace components {

class Holder;

class Component : public mixin::Named {
public:
    using Shared = std::shared_ptr<Component>;

    explicit Component(std::string &&name) noexcept;
    virtual ~Component() = default;

    virtual void PreDraw(Graphics &);
    virtual void Draw(Graphics &);
    virtual void PostDraw(Graphics &);
    virtual void PreUpdate(double);
    virtual void Update(double);
    virtual void PostUpdate(double);
    virtual void Serialize();  // for ImGui

    void SetHolder(std::weak_ptr<Holder> &&holder);
    [[nodiscard]] std::weak_ptr<Holder> GetHolder() const;

private:
    std::weak_ptr<Holder> mHolder;
};

}  // namespace components
}  // namespace meov::core
