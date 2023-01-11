#pragma once

#include "core/windows/base/base_window.hpp"

namespace meov::core {
class Object;
}  // namespace meov::core


namespace meov::Window {

class Properties final : public Base {
public:
    Properties(ImVec2 const &size = {}, bool isClosable = false);

    void Select(std::vector<std::weak_ptr<core::Object>> &&objects);
    void Reset();

private:
    std::vector<std::weak_ptr<core::Object>> mObjects;

    void DrawImpl() override;
};

}  // namespace meov::Window
