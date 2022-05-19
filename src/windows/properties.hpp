#pragma once

#include "windows/base_window.hpp"

namespace meov::core {
class Model;
class Texture;
}  // namespace meov::core


namespace meov::Window {

class Properties final : public Base {
public:
    Properties(ImVec2 const &size = {}, bool isClosable = false);

    void Select(std::weak_ptr<core::Model> &&model);
    void Select(std::weak_ptr<core::Texture> &&texture);
    void Reset();

private:
    std::weak_ptr<core::Model> mModelTarget;
    std::weak_ptr<core::Texture> mTextureTarget;

    void DrawImpl() override;

    void DrawInfo(std::shared_ptr<core::Model> model) const;
    void DrawInfo(std::shared_ptr<core::Texture> texture) const;
    void DrawInfo(glm::mat4 &transform) const;
};

}  // namespace meov::Window
