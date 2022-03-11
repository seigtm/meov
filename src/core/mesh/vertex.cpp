#include "Common.hpp"

#include "vertex.h"

namespace meov::core {

//=================================== Vertex ===================================//

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
