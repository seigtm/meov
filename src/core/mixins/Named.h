#pragma once

#include <string>

namespace meov::core::mixin {

class Named {
public:
    explicit Named(std::string &&name);

    const std::string &Name() const;
    void Rename(std::string &&name);

private:
    std::string mName;
};

}  // namespace meov::core::mixin
