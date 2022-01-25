#pragma once

#include "Common.hpp"
#include "windows/Base.hpp"

namespace MEOV::Window {

class Test : public Base {
public:
    Test();
    virtual ~Test();

protected:
    void DrawImpl() override;
};

}  // namespace MEOV::Window
