#pragma once

#include <map>

#include "material.hpp"
#include "common.hpp"
#include "named.hpp"

namespace meov::core {

class Vertex;
class Texture;
class Graphics;

class Mesh : public mixin::Named {
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned> &&indices, Material &&textures);
    ~Mesh();

    void Draw(Graphics &g) const;

    uint32_t GetID() const;
    bool HasIndices() const;
    size_t IndicesCount() const;
    size_t VerticesCount() const;

    const Material &Material() const;

private:
    GLuint VAO{}, VBO{}, EBO{};
    std::vector<Vertex> mVertices;
    std::vector<unsigned> mIndices;
    core::Material mMaterial;

    void Load();

    void ResetBuffer(GLuint &buffer);
    void GenerateBuffer(GLuint &buffer, GLenum type);
};

}  // namespace meov::core
