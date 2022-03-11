#pragma once

#include <map>

namespace meov::core {

class Vertex;
class Shader;
class Texture;

class Mesh {
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned> &&indices,
         std::vector<std::shared_ptr<Texture>> &&textures);
    ~Mesh();

    void Draw(const std::shared_ptr<Shader> &shader);
    void Draw(Shader &shader);

    bool HasIndices() const;
    size_t IndicesCount() const;
    size_t VerticesCount() const;

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
