#include "component.hpp"

namespace meov::core::components {

Component::Component(std::string &&name)
    : mName{ std::move(name) } {}

const std::string &Component::Name() const {
    return mName;
}

}  // namespace meov::core::components
