#pragma once

#include "windows/Base.hpp"

namespace MEOV::Window {

class Git : public Base {
public:
    Git();
    virtual ~Git();

protected:
    void DrawImpl() override;
};

}  // namespace MEOV::Window