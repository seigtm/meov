#pragma once

#include <memory>

#include "windows/base_window.hpp"

namespace meov::core {
class Graphics;
}

namespace meov::Window {

class ShaderWindow final : public Base {
public:
    ShaderWindow();

    void Select(std::weak_ptr<core::Graphics> &&g);

protected:
    void DrawImpl() override final;

private:
    std::weak_ptr<core::Graphics> mGraphics;
};

}  // namespace meov::Window
