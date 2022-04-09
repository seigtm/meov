#include "common.hpp"

#include "vertex.h"

namespace meov::core {

//=================================== Vertex ===================================//
Vertex::Vertex(glm::vec3 &&pos, glm::u8vec4 &&clr, glm::vec2 &&texCoords) noexcept
    : mPos{ std::move(pos) }
    , mClr{ std::move(clr) }
    , mTexCoords{ std::move(texCoords) } {}

Vertex::Vertex(const glm::vec3 &pos, const glm::u8vec4 &clr, const glm::vec2 &texCoords) noexcept
    : mPos{ pos }
    , mClr{ clr }
    , mTexCoords{ texCoords } {}

GLsizei Vertex::Length() { return sizeof(Vertex); }
GLsizei Vertex::Count() { return sizeof(Vertex) / sizeof(float); }

GLint Vertex::PositionCount() { return glm::vec3::length(); }
GLint Vertex::ColorCount() { return glm::u8vec4::length(); }
GLint Vertex::TexturePositionCount() { return glm::vec2::length(); }
// GLint Vertex::TangentCount() { return glm::vec3::length(); }
// GLint Vertex::BitAgentCount() { return glm::vec3::length(); }

GLint Vertex::PositionOffset() { return offsetof(Vertex, mPos); }
GLint Vertex::ColorOffset() { return offsetof(Vertex, mClr); }
GLint Vertex::TexturePositionOffset() { return offsetof(Vertex, mTexCoords); }
// GLint Vertex::TangentOffset() { return offsetof(Vertex, mTangent); }
// GLint Vertex::BitAgentOffset() { return offsetof(Vertex, mBitAgent); }

}  // namespace meov::core
