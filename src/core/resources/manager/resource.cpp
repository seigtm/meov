#include "core/resources/manager/resource.hpp"

namespace meov::core::resources {

Resource::Resource(std::string &&name) noexcept : mixin::Named{ std::move(name) } {}
Resource::Resource(fs::path &&path) noexcept
    : mixin::Named{ path.stem().string() }, mPath{ std::move(path) } {};

Resource::Resource(std::string &&name, fs::path &&path) noexcept
    : mixin::Named{ std::move(name) }
    , mPath{ std::move(path) } {}

Resource::Resource(const std::string_view name, const fs::path &path) noexcept
    : mixin::Named{ std::string{ name } }
    , mPath{ path } {}

void Resource::SetPath(const fs::path &path) {
    mPath = path;
}
fs::path Resource::GetPath() const {
    return mPath;
}

}  // namespace meov::core::resources
