#pragma once

#include "Common.hpp"
#include "windows/Base.hpp"

namespace meov::Window {

class Test final : public Base {
public:
    Test();

protected:
    void DrawImpl() override final;
};

}  // namespace meov::Window
