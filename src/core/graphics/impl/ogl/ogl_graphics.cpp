#include <common>

#include "core/model/model.hpp"
#include "core/mesh/mesh.hpp"
#include "core/mesh/vertex.hpp"
#include "core/texture/texture.hpp"
#include "core/graphics/impl/ogl/ogl_graphics.hpp"

namespace meov::core::gl {

void OGLGraphicsImpl::DrawDot(const glm::vec3 &position, const float radius) {
    if(mProgramQueue.empty()) return;
}

void OGLGraphicsImpl::DrawLine(std::initializer_list<glm::vec3> &&positions) {
    if(mProgramQueue.empty()) return;

    const auto &clr{ CurrentColor() };
    std::vector<Vertex> vertices;
    vertices.resize(positions.size());
    std::transform(
        positions.begin(), positions.end(), vertices.begin(),
        [&clr](const glm::vec3 &pos) -> Vertex {
            return Vertex{ pos, clr, glm::vec2{} };
        }  //
    );

    const Mesh mesh{ std::move(vertices), {}, {} };

    mRenderMode = GL_LINES;
    DrawMesh(mesh);
    mRenderMode = GL_TRIANGLES;
}

void OGLGraphicsImpl::DrawTriangle(const std::array<glm::vec3, 3> &positions) {
    if(mProgramQueue.empty()) return;

    const auto &clr{ CurrentColor() };
    const Mesh mesh{
        { Vertex{ positions[0], clr, glm::vec2{ 0.0f, 0.0f } },
          Vertex{ positions[1], clr, glm::vec2{ 0.5f, 1.0f } },
          Vertex{ positions[2], clr, glm::vec2{ 1.0f, 0.0f } } },
        { 0u, 1u, 2u },
        {}
    };

    DrawMesh(mesh);
}

void OGLGraphicsImpl::DrawRectangle(const std::array<glm::vec3, 4> &positions) {
    if(mProgramQueue.empty()) return;

    const auto &clr{ CurrentColor() };
    const Mesh mesh{
        { Vertex{ positions[0], clr, glm::vec2{ 0.0f, 1.0f } },
          Vertex{ positions[1], clr, glm::vec2{ 1.0f, 1.0f } },
          Vertex{ positions[2], clr, glm::vec2{ 1.0f, 0.0f } },
          Vertex{ positions[3], clr, glm::vec2{ 0.0f, 0.0f } } },
        { 0u, 1u, 2u, 0u, 3u, 2u },
        {}
    };

    DrawMesh(mesh);
}

void OGLGraphicsImpl::DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) {
    if(mProgramQueue.empty()) return;

    const auto &clr{ CurrentColor() };
    Material mat;
    mat[Texture::Type::Diffuse] = tex;
    const Mesh mesh{
        { Vertex{ positions[0], clr, glm::vec2{ 0.0f, 1.0f } },
          Vertex{ positions[1], clr, glm::vec2{ 1.0f, 1.0f } },
          Vertex{ positions[2], clr, glm::vec2{ 1.0f, 0.0f } },
          Vertex{ positions[3], clr, glm::vec2{ 0.0f, 0.0f } } },
        { 0u, 1u, 2u, 0u, 3u, 2u },
        std::move(mat)
    };

    DrawMesh(mesh);
}

void OGLGraphicsImpl::DrawMesh(const Mesh &mesh) {
    if(mProgramQueue.empty()) return;

    auto program{ CurrentProgram() };
    program.Use();
    program.Get("projection")->Set(GetProjection());
    program.Get("view")->Set(GetViewMatrix());
    program.Get("model")->Set(ResultingTransform());
    DrawMeshRaw(mesh, program);
    program.UnUse();
}

void OGLGraphicsImpl::DrawModel(const Model &model) {
    if(mProgramQueue.empty() || model.GetMeshes().empty()) return;

    auto program{ CurrentProgram() };
    program.Use();
    program.Get("projection")->Set(GetProjection());
    program.Get("view")->Set(GetViewMatrix());
    program.Get("model")->Set(ResultingTransform());

    for(auto &&mesh : model.GetMeshes())
        if(mesh) DrawMeshRaw(*mesh, program);

    program.UnUse();
}

void OGLGraphicsImpl::DrawMeshRaw(const Mesh &mesh, shaders::Program &program) {
    const std::array<Texture::Type, 4> types{
        Texture::Type::Diffuse,
        Texture::Type::Specular,
        Texture::Type::Normal,
        Texture::Type::Height,
    };

    const auto &material{ mesh.Material() };
    int counter{};
    for(const auto type : types) {
        if(auto texture{ material[type] }; texture) {
            const std::string name{ texture->Activate(counter++) };
            texture->Bind();
            program.Get("material." + name)->Set(counter);
        }
    }
    program.Get("material.shininess")->Set(material.GetShininess());

    glBindVertexArray(mesh.GetID());
    if(mesh.HasIndices()) {
        glDrawElements(mRenderMode, mesh.IndicesCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mRenderMode, 0, mesh.VerticesCount());
    }
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

}  // namespace meov::core::gl
