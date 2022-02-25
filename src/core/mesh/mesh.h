#pragma once

#include <map>

namespace meov::core {

class Vertex;
class Vertices;

class Mesh {
public:
    Mesh();
    explicit Mesh(const Vertices &vertices);
    Mesh(const Vertices &vertices, const std::vector<unsigned> &indices);

    void load(const Vertices &vertices);
    void load(const std::vector<unsigned> &indices);
    void load(const Vertices &vertices, const std::vector<unsigned> &indices);

    void bind() const;
    void unbind() const;

    bool hasIndices() const;
    size_t indices() const;
    size_t vertices() const;

private:
    size_t mIndices{};
    size_t mVertices{};

    enum class BufferType {
        VAO, VBO, EBO
    };

    std::map<BufferType, GLuint> mBuffers;

    void resetBuffer(BufferType type);
    void loadBuffer(BufferType type, GLenum target, size_t size, const GLubyte *data);
};

} // namespace meov::core
