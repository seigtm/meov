#pragma once

namespace meov::core {

struct Vertex {
    glm::vec3 mPos;
    glm::vec4 mClr;
    glm::vec2 mTexCoords;

    Vertex(glm::vec3 pos, glm::vec4 clr, glm::vec2 texCoords);
    std::vector<float> raw() const;
};

class Vertices {
public:
    Vertices() = default;
    explicit Vertices(std::initializer_list<Vertex> &&source);

    std::vector<float> raw() const;
    bool empty() const;

    // length in bytes
    size_t length() const;

    // count of vertices
    size_t count() const;

    Vertex &operator[](size_t id);
    const Vertex &operator[](size_t id) const;

private:
    std::vector<Vertex> mSource;
};

namespace VertexInfo {

constexpr size_t count{ 9 };
constexpr size_t stride{ sizeof(float) * count };

namespace Count {

constexpr int pos{ glm::vec3::length() };
constexpr int clr{ glm::vec4::length() };
constexpr int tex{ glm::vec2::length() };

}  // namespace Count

namespace Offset {

constexpr size_t pos{ 0 };
constexpr size_t clr{ sizeof(float) * Count::pos };
constexpr size_t tex{ sizeof(float) * Count::pos + Count::clr };

}  // namespace Offset

}  // namespace VertexInfo

}  // namespace meov::core
