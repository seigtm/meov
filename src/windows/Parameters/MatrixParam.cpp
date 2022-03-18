#include "Common.hpp"

#include "MatrixParam.hpp"

namespace meov::Window {

Matrix::Matrix(std::string &&name, glm::mat4 &matrix)
    : Value{ std::move(name), false }
    , mMatrix{ &matrix } {}

void Matrix::Draw() {
    for(glm::length_t row{}; row < mMatrix->length(); ++row) {
        ImGui::InputFloat4("", reinterpret_cast<float *>(&((*mMatrix)[row])));
    }
}

}  // namespace meov::Window