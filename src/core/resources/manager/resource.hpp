#pragma once

#include "named.hpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace meov::core::resources {

class Resource : public mixin::Named {
public:
    explicit Resource(std::string &&name) noexcept;
    virtual ~Resource() = default;

    void SetPath(const fs::path &path);
    fs::path GetPath() const;

private:
    fs::path mPath{};
};

}  // namespace meov::core::resources
