#pragma once

#include "graphics.hpp"

namespace meov::core::gl {

class OGLGraphicsImpl final : public Graphics::Impl {
public:
    void DrawDot(const glm::vec3 &position, const float radius = 1) override;
    void DrawLine(std::initializer_list<glm::vec3> &&vertices) override;
    void DrawTriangle(const std::array<glm::vec3, 3> &positions) override;
    void DrawRectangle(const std::array<glm::vec3, 4> &positions) override;
    void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) override;
    void DrawMesh(const Mesh &mesh) override;

private:
    GLenum mRenderMode{ GL_TRIANGLES };
};

}  // namespace meov::core::gl
