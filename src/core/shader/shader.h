#pragma once

namespace meov::core {

namespace Position {

enum Type {
    Position,
    Color,
    TextureCoordinates
};

};

class Shader {
public:
    class Setter;

    Shader(const std::string_view &vertexPath = {}, const std::string_view &fragmentPath = {});
    ~Shader();

    void Use() const;
    void UnUse() const;

    Setter Get(const std::string_view &name);

    unsigned GetID() const;

private:
    unsigned mProgram;

    static std::string Load(const std::string_view &path);
    static unsigned MakeShader(GLenum type, const std::string &source);
    static std::string GetDefaultShaderSource(GLenum type);
    static std::string GetShaderName(GLenum type);
};

class Shader::Setter {
    friend class Shader;

    Setter(Shader &parent, const std::string_view &name);

public:
    Setter &Get(const std::string_view &name);

    Setter &Set(float value);
    Setter &Set(float v1, float v2);
    Setter &Set(float v1, float v2, float v3);
    Setter &Set(float v1, float v2, float v3, float v4);

    Setter &Set(int value);
    Setter &Set(int v1, int v2);
    Setter &Set(int v1, int v2, int v3);
    Setter &Set(int v1, int v2, int v3, int v4);

    Setter &Set(unsigned value);
    Setter &Set(unsigned v1, unsigned v2);
    Setter &Set(unsigned v1, unsigned v2, unsigned v3);
    Setter &Set(unsigned v1, unsigned v2, unsigned v3, unsigned v4);

    Setter &Set(bool value);
    Setter &Set(bool v1, bool v2);
    Setter &Set(bool v1, bool v2, bool v3);
    Setter &Set(bool v1, bool v2, bool v3, bool v4);

    Setter &Set(const glm::mat4 &matrix);

private:
    Shader &mParent;
    int mId{ -1 };
};

}  // namespace meov::core
