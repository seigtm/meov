#pragma once

#include "glm/matrix.hpp"
#include "ParamWin.hpp"

namespace meov::Window {

class Matrix final : public Value {
public:
    explicit Matrix(std::string &&name, glm::mat4 &matrix);

    void Draw() override;

private:
    glm::mat4 *mMatrix{ nullptr };
};

}  // namespace meov::Window