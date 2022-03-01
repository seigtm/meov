#include "Common.hpp"

#include "mesh.h"
#include "vertex.h"
#include "shader.h"
#include "texture.h"

namespace meov::core {

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned> &&indices, std::vector<Texture> &&textures)
    : mVertices{ std::move(vertices) }
    , mIndices{ std::move(indices) }
    , mTextures{ std::move(textures) } {
    Load();
}

Mesh::~Mesh() {
    ResetBuffer(EBO);
    ResetBuffer(VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw(const std::shared_ptr<Shader> &shader) {
    if(shader != nullptr) Draw(*shader);
}

void Mesh::Draw(Shader &shader) {
    unsigned diffuseCount{ 1 };
    unsigned specularCount{ 1 };
    unsigned normalCount{ 1 };
    unsigned heightCount{ 1 };

    shader.Use();

    for(size_t i{}; i < mTextures.size(); ++i) {
        auto &texture{ mTextures[i] };
        if(!texture.Valid()) {
            continue;
        }
        glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream name;
        name << "texture";
        switch(texture.GetType()) {
            case Texture::Type::Diffuse: {
                name << "Diffuse" << diffuseCount++;
            } break;
            case Texture::Type::Specular: {
                name << "Specular" << specularCount++;
            } break;
            case Texture::Type::Normal: {
                name << "Normal" << normalCount++;
            } break;
            case Texture::Type::Height: {
                name << "Height" << heightCount++;
            } break;
        }

        // LOGD << "Setting texture " << name.str() << " as " << i;
        shader.Get(name.str()).Set(static_cast<int>(texture.GetID()));
        texture.Bind();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    shader.UnUse();
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
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
        [&](GLint count, GLuint offset) {
            glVertexAttribPointer(
                attributePos, count, GL_FLOAT, GL_FALSE, Vertex::Length(), (GLvoid *)offset);
            glEnableVertexAttribArray(attributePos);
            ++attributePos;
        }
    };

    InitializeAttribute(Vertex::PositionCount(), Vertex::PositionOffset());
    InitializeAttribute(Vertex::ColorCount(), Vertex::ColorOffset());
    InitializeAttribute(Vertex::TexturePositionCount(), Vertex::TexturePositionOffset());
    InitializeAttribute(Vertex::TangentCount(), Vertex::TangentOffset());
    InitializeAttribute(Vertex::BitAgentCount(), Vertex::BitAgentOffset());

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
