#pragma once

namespace meov::core {

class Texture {
public:
    enum class Type {
        Diffuse,
        Specular,
        Normal,
        Height,
        Cubemap,
        Invalid,
    };

    Texture();
    // Basic texture c-tor.
    Texture(const unsigned char *bytes, int width, int height, int channels, Type type);
    // Cubemap texture c-tor.
    Texture(std::array<unsigned char *, 6> bytes, int width, int height, int channels);
    ~Texture();

    Texture(const Texture &other) = delete;
    Texture &operator=(const Texture &other) = delete;

    void Bind();
    [[nodiscard]] std::string Activate(const int id);

    bool Valid() const;
    unsigned GetID() const;
    Type GetType() const;

private:
    unsigned mId{};
    Type mType;
    bool mValid{ false };
};

}  // namespace meov::core
