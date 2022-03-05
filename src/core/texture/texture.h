#pragma once

namespace meov::core {

class Texture {
public:
    enum class Type {
        Diffuse,
        Specular,
        Normal,
        Height,
    };

    explicit Texture(const std::string_view &path, const Type type);
    ~Texture();

    void Bind();
    void Activate(const int id);

    bool Valid() const;
    unsigned GetID() const;
    Type GetType() const;


private:
    unsigned mId{};
    std::string mPath;
    Type mType;
    bool mValid{ false };
};

}  // namespace meov::core
