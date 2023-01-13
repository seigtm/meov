#pragma once

namespace meov::core {

struct Vertex {
    Vertex() = default;
    constexpr Vertex(glm::vec3 &&pos, glm::u8vec4 &&clr, glm::vec2 &&texCoords) noexcept
        : mPos{ std::move(pos) }, mClr{ std::move(clr) }, mTexCoords{ std::move(texCoords) } {}
    constexpr Vertex(const glm::vec3 &pos, const glm::u8vec4 &clr, const glm::vec2 &texCoords) noexcept
        : mPos{ pos }, mClr{ clr }, mTexCoords{ texCoords } {}

    glm::vec3 mPos{};
    glm::u8vec4 mClr{};
    glm::vec2 mTexCoords{};
    // glm::vec3 mTangent;
    // glm::vec3 mBitAgent;

    /// @brief Length in bytes
    [[nodiscard]] static constexpr GLsizei Length() noexcept { return sizeof(Vertex); };

    /// @brief Count of floats (Stride)
    [[nodiscard]] static constexpr GLsizei Count() noexcept {
        return glm::vec3::length() + glm::u8vec4::length() + glm::vec2::length();
    };

    [[nodiscard]] static constexpr GLint PositionCount() noexcept {
        return glm::vec3::length();
    };
    [[nodiscard]] static constexpr GLint ColorCount() noexcept {
        return glm::u8vec4::length();
    };
    [[nodiscard]] static constexpr GLint TexturePositionCount() noexcept {
        return glm::vec2::length();
    };
    // [[nodiscard]] static constexpr GLint TangentCount() noexcept {
    //     return glm::vec3::length();
    // }
    // [[nodiscard]] static constexpr GLint BitAgentCount() noexcept {
    //     return glm::vec3::length();
    // }

    [[nodiscard]] static constexpr GLint PositionOffset() noexcept {
        return offsetof(Vertex, mPos);
    };
    [[nodiscard]] static constexpr GLint ColorOffset() noexcept {
        return offsetof(Vertex, mClr);
    };
    [[nodiscard]] static constexpr GLint TexturePositionOffset() noexcept {
        return offsetof(Vertex, mTexCoords);
    };
    // [[nodiscard]] static constexpr GLint TangentOffset() noexcept {
    //     return offsetof(Vertex, mTangent);
    // }
    // [[nodiscard]] static constexpr GLint BitAgentOffset() noexcept {
    //     return offsetof(Vertex, mBitAgent);
    // }
};

}  // namespace meov::core
