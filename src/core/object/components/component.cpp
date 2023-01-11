#include "core/object/components/component.hpp"

namespace meov::core::components {

Component::Component(std::string &&name) noexcept : mixin::Named{ std::move(name) } {}

void Component::PreDraw(Graphics &) {}
void Component::Draw(Graphics &) {}
void Component::PostDraw(Graphics &) {}
void Component::PreUpdate(double) {}
void Component::Update(double) {}
void Component::PostUpdate(double) {}

void Component::Serialize() {}

void Component::SetHolder(std::weak_ptr<Holder> &&holder) {
    mHolder = std::move(holder);
}

std::weak_ptr<Holder> Component::GetHolder() const {
    return mHolder;
}

}  // namespace meov::core::components
