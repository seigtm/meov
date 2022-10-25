#pragma once

#include "windows/base/base_window.hpp"

namespace meov::Window {

class Git final : public Base {
public:
    Git();

protected:
    void DrawImpl() override final;
};

}  // namespace meov::Window
