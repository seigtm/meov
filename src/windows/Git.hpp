#pragma once

#include "windows/Base.hpp"

namespace MEOV::Window {

class Git final : public Base {
public:
    Git();

protected:
    void DrawImpl() override final;
};

}  // namespace MEOV::Window
