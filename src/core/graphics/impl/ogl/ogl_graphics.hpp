#pragma once

#include "core/graphics/graphics.hpp"

namespace meov::core::gl {

class OGLGraphicsImpl final : public Graphics::Impl {
public:
    void DrawDot(const glm::vec3 &position, const float radius = 1) override;
    void DrawLine(std::initializer_list<glm::vec3> &&vertices) override;
    void DrawTriangle(const std::array<glm::vec3, 3> &positions) override;
    void DrawRectangle(const std::array<glm::vec3, 4> &positions) override;
    void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) override;
    void DrawMesh(const Mesh &mesh) override;
    void DrawModel(const Model &model) override;

private:
    GLenum mRenderMode{ GL_TRIANGLES };

    void DrawMeshRaw(const Mesh &mesh, shaders::Program &program);
};

}  // namespace meov::core::gl
