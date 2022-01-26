#pragma once

#include "windows/Base.hpp"

namespace MEOV::Window {

class Git final : public Base {
public:
    Git();
    virtual ~Git() = default;

protected:
    void DrawImpl() override final;
};

}  // namespace MEOV::Window
