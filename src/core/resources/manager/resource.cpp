#include "resource.hpp"

namespace meov::core::resources {

Resource::Resource(std::string &&name) noexcept
    : mixin::Named{ std::move(name) } {}

void Resource::SetPath(const fs::path &path) {
    mPath = path;
}
fs::path Resource::GetPath() const {
    return mPath;
}

}  // namespace meov::core::resources
