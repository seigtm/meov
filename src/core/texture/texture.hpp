#pragma once

namespace meov::core {

class Texture {
public:
    enum class Type {
        Diffuse,
        Specular,
        Normal,
        Height,
        Invalid,
    };

    Texture();
    Texture(const unsigned char *bytes, int width, int height, int channels, Type type);
    ~Texture();

    Texture(const Texture &other) = delete;
    Texture &operator=(const Texture &other) = delete;

    void Bind();
    void Activate(const int id);

    bool Valid() const;
    unsigned GetID() const;
    Type GetType() const;

private:
    unsigned mId{};
    Type mType;
    bool mValid{ false };
};

}  // namespace meov::core
