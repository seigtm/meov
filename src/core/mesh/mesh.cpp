#include "Common.hpp"

#include "mesh.h"
#include "vertex.h"
#include "shader.h"

namespace meov::core {

Mesh::Mesh() {
    mBuffers[BufferType::VAO] = 0u;
    glGenVertexArrays(1, &mBuffers[BufferType::VAO]);
}

Mesh::Mesh(const Vertices &vertices)
    : Mesh{} {
    load(vertices);
}

Mesh::Mesh(const Vertices &vertices, const std::vector<unsigned> &indices)
    : Mesh{ vertices } {
    load(indices);
}

void Mesh::load(const Vertices &vertices) {
    if(vertices.empty()) {
        return;
    }
    mVertices = vertices.count();

    bind();
    resetBuffer(BufferType::VBO);
    loadBuffer(BufferType::VBO, GL_ARRAY_BUFFER, vertices.length(),
               reinterpret_cast<const GLubyte *>(vertices.raw().data()));

    glVertexAttribPointer(Position::Position, VertexInfo::Count::pos, GL_FLOAT, GL_FALSE,
                          VertexInfo::stride, (void *)VertexInfo::Offset::pos);
    glEnableVertexAttribArray(Position::Position);

    glVertexAttribPointer(Position::Color, VertexInfo::Count::clr, GL_FLOAT, GL_FALSE,
                          VertexInfo::stride, (void *)VertexInfo::Offset::clr);
    glEnableVertexAttribArray(Position::Color);

    glVertexAttribPointer(Position::TextureCoordinates, VertexInfo::Count::clr, GL_FLOAT, GL_FALSE,
                          VertexInfo::stride, (void *)VertexInfo::Offset::tex);
    glEnableVertexAttribArray(Position::TextureCoordinates);

    unbind();
}

void Mesh::load(const std::vector<unsigned> &indices) {
    if(indices.empty()) {
        return;
    }
    mIndices = indices.size();

    bind();
    resetBuffer(BufferType::EBO);
    loadBuffer(BufferType::EBO, GL_ELEMENT_ARRAY_BUFFER,
               sizeof(float) * indices.size(),
               reinterpret_cast<const GLubyte *>(indices.data()));
    unbind();
}

void Mesh::load(const Vertices &vertices, const std::vector<unsigned> &indices) {
    load(vertices);
    load(indices);
}

void Mesh::bind() const {
    glBindVertexArray(mBuffers.at(BufferType::VAO));
}

void Mesh::unbind() const {
    glBindVertexArray(0);
}

bool Mesh::hasIndices() const {
    return mIndices != 0;
}

size_t Mesh::indices() const {
    return mIndices;
}

size_t Mesh::vertices() const {
    return mVertices;
}

void Mesh::resetBuffer(BufferType type) {
    if(auto found{ mBuffers.find(type) }; found != mBuffers.end()) {
        glDeleteBuffers(1, &(found->second));
        found->second = 0u;
    } else {
        mBuffers[type] = 0u;
    }
}

void Mesh::loadBuffer(BufferType type, GLenum target, size_t size, const GLubyte *data) {
    if(nullptr == data) {
        return;
    }

    auto &buffer{ mBuffers[type] };

    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, GL_STATIC_DRAW);
}

}  // namespace meov::core
