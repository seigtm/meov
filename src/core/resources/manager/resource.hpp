#pragma once

#include "core/mixins/named.hpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace meov::core::resources {

class Resource : public mixin::Named {
public:
    explicit Resource(std::string &&name) noexcept;
    explicit Resource(fs::path &&path) noexcept;
    Resource(std::string &&name, fs::path &&path) noexcept;
    Resource(const std::string_view name, const fs::path &path) noexcept;
    virtual ~Resource() = default;

    void SetPath(const fs::path &path);
    fs::path GetPath() const;

private:
    fs::path mPath{};
};

}  // namespace meov::core::resources
