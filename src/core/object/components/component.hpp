#pragma once

#include <string>

#include <utils/types.hpp>
#include "core/mixins/named.hpp"

namespace meov::core {

class Graphics;

namespace components {

class Holder;

class Component : public mixin::Named {
public:
    using Shared = sptr<Component>;

    explicit Component(std::string &&name) noexcept;
    virtual ~Component() = default;

    virtual void PreDraw(Graphics &);
    virtual void Draw(Graphics &);
    virtual void PostDraw(Graphics &);
    virtual void PreUpdate(f64);
    virtual void Update(f64);
    virtual void PostUpdate(f64);
    virtual void Serialize();  // for ImGui

    void SetHolder(wptr<Holder> &&holder);
    [[nodiscard]] wptr<Holder> GetHolder() const;

private:
    wptr<Holder> mHolder;
};

}  // namespace components
}  // namespace meov::core
