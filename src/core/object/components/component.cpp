#include "component.hpp"

namespace meov::core::components {

Component::Component(std::string &&name)
    : mixin::Named{ std::move(name) } {}

void Component::Serialize() {}

void Component::SetHolder(std::weak_ptr<Holder> &&holder) {
    mHolder = std::move(holder);
}

}  // namespace meov::core::components
