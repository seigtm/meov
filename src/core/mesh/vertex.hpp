#pragma once

namespace meov::core {

struct Vertex {
    using position_type = glm::vec3;
    using color_type = glm::vec4;
    using tex_coords_type = glm::vec2;

    Vertex() = default;
    constexpr Vertex(position_type &&pos, color_type &&clr, tex_coords_type &&texCoords) noexcept
        : mPos{ std::move(pos) }, mClr{ std::move(clr) }, mTexCoords{ std::move(texCoords) } {}
    constexpr Vertex(const position_type &pos, const color_type &clr, const tex_coords_type &texCoords) noexcept
        : mPos{ pos }, mClr{ clr }, mTexCoords{ texCoords } {}

    position_type mPos{};
    color_type mClr{};
    tex_coords_type mTexCoords{};
    // glm::vec3 mTangent;
    // glm::vec3 mBitAgent;

    /// @brief Length in bytes
    [[nodiscard]] static constexpr GLsizei Length() noexcept { return sizeof(Vertex); };

    /// @brief Count of floats (Stride)
    [[nodiscard]] static constexpr GLsizei Count() noexcept {
        return position_type::length() + color_type::length() + tex_coords_type::length();
    };

    [[nodiscard]] static constexpr GLint PositionCount() noexcept {
        return position_type::length();
    };
    [[nodiscard]] static constexpr GLint ColorCount() noexcept {
        return color_type::length();
    };
    [[nodiscard]] static constexpr GLint TexturePositionCount() noexcept {
        return tex_coords_type::length();
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
