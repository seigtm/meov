#pragma once

namespace meov::core {

//=================================== Vertex ===================================//

struct Vertex {
    Vertex() = default;
    Vertex(glm::vec3 &&pos, glm::u8vec4 &&clr, glm::vec2 &&texCoords) noexcept;
    Vertex(const glm::vec3 &pos, const glm::u8vec4 &clr, const glm::vec2 &texCoords) noexcept;

    glm::vec3 mPos{};
    glm::u8vec4 mClr{};
    glm::vec2 mTexCoords{};
    // glm::vec3 mTangent;
    // glm::vec3 mBitAgent;

    /// @brief Length in bytes
    static GLsizei Length();

    /// @brief Count of floats (Stride)
    static GLsizei Count();

    static GLint PositionCount();
    static GLint ColorCount();
    static GLint TexturePositionCount();
    // static GLint TangentCount();
    // static GLint BitAgentCount();

    static GLint PositionOffset();
    static GLint ColorOffset();
    static GLint TexturePositionOffset();
    // static GLint TangentOffset();
    // static GLint BitAgentOffset();
};

}  // namespace meov::core
