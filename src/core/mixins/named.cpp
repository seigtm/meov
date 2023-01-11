#include "core/mixins/named.hpp"


namespace meov::core::mixin {

Named::Named(std::string &&name) noexcept : mName{ std::move(name) } {}

const std::string &Named::Name() const {
    return mName;
}
void Named::Rename(std::string &&name) {
    if(name.empty())
        return;
    mName = std::move(name);
}

}  // namespace meov::core::mixin
