#pragma once

#include <map>

#include "Common.hpp"

namespace meov::core {

class Vertex;
class Texture;
class Graphics;

class Mesh {
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned> &&indices,
         std::vector<std::shared_ptr<Texture>> &&textures);
    ~Mesh();

    void Draw(Graphics &g) const;

    uint32_t GetID() const;
    bool HasIndices() const;
    size_t IndicesCount() const;
    size_t VerticesCount() const;

    const std::vector<std::shared_ptr<Texture>> &Textures() const;

private:
    GLuint VAO{}, VBO{}, EBO{};
    std::vector<Vertex> mVertices;
    std::vector<unsigned> mIndices;
    std::vector<std::shared_ptr<Texture>> mTextures;

    void Load();

    void ResetBuffer(GLuint &buffer);
    void GenerateBuffer(GLuint &buffer, GLenum type);
};

}  // namespace meov::core
