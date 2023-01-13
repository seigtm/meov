#pragma once

#include <span>
#include <utils/types.hpp>

#include "core/resources/manager/resource.hpp"

namespace meov::utils::stb {
struct image;
} // namespace meov::utils::stb

namespace meov::core::resources {

class Image;

class Texture : public Resource {
public:
    static constexpr u64 CubeMapImageCount{ 6 };
    enum class Type : u8 {
        Diffuse,
        Specular,
        Height,
        Normal,
        Ambient,
        Cubemap,
        Invalid,
    };
    [[nodiscard]] static std::string_view Type2String(Type type) noexcept;

    Texture() = default;
    // Basic texture c-tor.
    Texture(const std::span<byte> bytes, i32 width, i32 height, i32 channels, Type type);
    explicit Texture(const Image &image, Type type);
    explicit Texture(const utils::stb::image &image, Type type);

    // Cubemap texture c-tor.
    Texture(const std::array<std::span<byte>, CubeMapImageCount> &bytes, i32 width, i32 height, i32 channels);
    explicit Texture(const std::array<Image, CubeMapImageCount> &images);
    explicit Texture(const std::array<utils::stb::image, CubeMapImageCount> &images);
    ~Texture();

    Texture(const Texture &other) = delete;
    Texture &operator=(const Texture &other) = delete;

    void Bind();
    [[nodiscard]] std::string Activate(const i32 id);

    bool Valid() const;
    u32 GetID() const;
    Type GetType() const;

private:
    u32 mId{};
    Type mType{ Type::Invalid };
    bool mValid{ false };

    void MakeFrom(const std::span<const byte> bytes, const u32 width, const u32 height,
        const i32 channels);

    void SetupCubeMapParams();
    void AppendIDToName();
};

}  // namespace meov::core::resources
