#pragma once

#include "windows/base/base_window.hpp"

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
    const std::vector<std::string> mComponents;
    std::vector<std::string>::const_iterator mSelectedComponent;

    void DrawImpl() override;
    void DrawComponentsDropBox();
};

}  // namespace meov::Window
