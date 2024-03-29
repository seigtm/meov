#include <common>

#include "core/mesh/mesh.hpp"
#include "core/mesh/vertex.hpp"
#include "core/shaders/shader/shader.hpp"
#include "core/resources/texture/texture.hpp"
#include "core/graphics/graphics.hpp"

namespace meov::core {

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned> &&indices, core::Material &&material)
    : mVertices{ std::move(vertices) }
    , mIndices{ std::move(indices) }
    , mMaterial{ std::move(material) } {
    Load();
}

Mesh::~Mesh() {
    ResetBuffer(EBO);
    ResetBuffer(VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw(Graphics &g) const {
    g.DrawMesh(*this);
}

uint32_t Mesh::GetID() const {
    return VAO;
}

bool Mesh::HasIndices() const {
    return !mIndices.empty();
}

size_t Mesh::IndicesCount() const {
    return mIndices.size();
}

size_t Mesh::VerticesCount() const {
    return mVertices.size();
}

const Material &Mesh::Material() const {
    return mMaterial;
}

void Mesh::Load() {
    if(mVertices.empty()) return;

    glGenVertexArrays(1, &VAO);
    GenerateBuffer(VBO, GL_ARRAY_BUFFER);
    GenerateBuffer(EBO, GL_ELEMENT_ARRAY_BUFFER);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * Vertex::Length(), mVertices.data(), GL_STATIC_DRAW);
    if(HasIndices()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned),
                     mIndices.data(), GL_STATIC_DRAW);
    }

    GLuint attributePos{};
    const auto InitializeAttribute{
        [&](GLint count, GLuint offset, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE) {
            glEnableVertexAttribArray(attributePos);
            glVertexAttribPointer(
                attributePos, count, type, normalized, Vertex::Length(), (GLvoid *)offset);
            ++attributePos;
        }
    };

    InitializeAttribute(Vertex::PositionCount(), Vertex::PositionOffset());
    InitializeAttribute(Vertex::ColorCount(), Vertex::ColorOffset()); //, GL_UNSIGNED_BYTE, GL_TRUE);
    InitializeAttribute(Vertex::TexturePositionCount(), Vertex::TexturePositionOffset());
    // InitializeAttribute(Vertex::TangentCount(), Vertex::TangentOffset());
    // InitializeAttribute(Vertex::BitAgentCount(), Vertex::BitAgentOffset());

    glBindVertexArray(0);
}

void Mesh::ResetBuffer(GLuint &buffer) {
    glDeleteBuffers(1, &buffer);
    buffer = 0;
}

void Mesh::GenerateBuffer(GLuint &buffer, GLenum type) {
    ResetBuffer(buffer);
    glGenBuffers(1, &buffer);
}

}  // namespace meov::core
