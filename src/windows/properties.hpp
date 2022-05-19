#pragma once

#include "windows/base_window.hpp"

namespace meov::core {
class Object;
}  // namespace meov::core


namespace meov::Window {

class Properties final : public Base {
public:
    Properties(ImVec2 const &size = {}, bool isClosable = false);

    void Select(std::weak_ptr<core::Object> &&object);
    void Reset();

private:
    std::weak_ptr<core::Object> mObject;

    void DrawImpl() override;
};

}  // namespace meov::Window
