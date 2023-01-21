#include "core/object/components/component.hpp"

namespace meov::core::components {

Component::Component(std::string &&name) noexcept : mixin::Named{ std::move(name) } {}

void Component::PreDraw(Graphics &) {}
void Component::Draw(Graphics &) {}
void Component::PostDraw(Graphics &) {}
void Component::PreUpdate(f64) {}
void Component::Update(f64) {}
void Component::PostUpdate(f64) {}

void Component::Serialize() {}

void Component::SetHolder(wptr<Holder> &&holder) {
    mHolder = std::move(holder);
}

wptr<Holder> Component::GetHolder() const {
    return mHolder;
}

}  // namespace meov::core::components
