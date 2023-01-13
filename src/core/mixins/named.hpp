#pragma once

#include <string>
#include <string_view>

namespace meov::core::mixin {

class Named {
public:
    static constexpr std::string_view DefaultName{ "unnamed" };

    explicit Named(std::string &&name = std::string{ DefaultName }) noexcept;

    [[nodiscard]] const std::string &Name() const;
    void Rename(std::string &&name);

private:
    std::string mName;
};

}  // namespace meov::core::mixin
