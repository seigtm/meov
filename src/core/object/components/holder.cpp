#include "core/object/components/holder.hpp"

namespace meov::core::components {

void Holder::ForEachComponent(std::function<void(Component::Shared &comp)> &&method) {
    if(!method)
        return;

    for([[maybe_unused]] auto &&[name, component] : mComponents)
        method(component);
}

}  // namespace meov::core::components
