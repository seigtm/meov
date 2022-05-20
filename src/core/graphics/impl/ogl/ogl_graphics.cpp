#include "common.hpp"

#include "mesh.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include "ogl_graphics.hpp"

namespace meov::core::gl {

void OGLGraphicsImpl::DrawDot(const glm::vec3 &position, const float radius) {
    if(mProgramQueue.empty()) return;
}

void OGLGraphicsImpl::DrawLine(std::initializer_list<glm::vec3> &&positions) {
    if(mProgramQueue.empty()) return;

    const auto &clr{ mColorQueue.front() };
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

    const auto &clr{ mColorQueue.front() };
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

    const auto &clr{ mColorQueue.front() };
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

    const auto &clr{ mColorQueue.front() };
    const Mesh mesh{
        { Vertex{ positions[0], clr, glm::vec2{ 0.0f, 1.0f } },
          Vertex{ positions[1], clr, glm::vec2{ 1.0f, 1.0f } },
          Vertex{ positions[2], clr, glm::vec2{ 1.0f, 0.0f } },
          Vertex{ positions[3], clr, glm::vec2{ 0.0f, 0.0f } } },
        { 0u, 1u, 2u, 0u, 3u, 2u },
        { tex }
    };

    DrawMesh(mesh);
}

void OGLGraphicsImpl::DrawMesh(const Mesh &mesh) {
    if(mProgramQueue.empty()) return;

    auto &program{ mProgramQueue.front() };
    program.Use();
    program.Get("model")->Set(mResultTransform);

    std::unordered_map<Texture::Type, unsigned> counters{
        { Texture::Type::Diffuse, 1 },
        { Texture::Type::Specular, 1 },
        { Texture::Type::Normal, 1 },
        { Texture::Type::Height, 1 },
        { Texture::Type::Invalid, std::numeric_limits<unsigned>::max() }
    };

    const auto &textures{ mesh.Textures() };
    for(size_t i{}; i < textures.size(); ++i) {
        auto &texture{ textures[i] };
        if(!(texture && texture->Valid())) {
            continue;
        }
        const auto name{ texture->Activate(i) + std::to_string(counters[texture->GetType()]++) };

        texture->Bind();
        if(auto &var{ program.Get(name) }; var != nullptr)
            var->Set(static_cast<int>(i));
    }

    glBindVertexArray(mesh.GetID());
    if(mesh.HasIndices()) {
        glDrawElements(mRenderMode, mesh.IndicesCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(mRenderMode, mesh.GetID(), mesh.VerticesCount());
    }
    program.UnUse();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}


}  // namespace meov::core::gl