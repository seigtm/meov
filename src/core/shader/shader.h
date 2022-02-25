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

    Shader(const std::string &vertexPath = {}, const std::string &fragmentPath = {});
    ~Shader();

    void use() const;

    Setter get(const std::string &name);

    unsigned getID() const;
    operator unsigned() const;

private:
    unsigned program;

    std::string load(const std::string &path) const;
    unsigned makeShader(GLenum type, const std::string &source) const;
    std::string getDefaultShaderSource(GLenum type) const;
};

class Shader::Setter {
    friend class Shader;

    Setter(Shader &parent, const std::string &name);

public:
    Setter &set(float value);
    Setter &set(float v1, float v2);
    Setter &set(float v1, float v2, float v3);
    Setter &set(float v1, float v2, float v3, float v4);

    Setter &set(int value);
    Setter &set(int v1, int v2);
    Setter &set(int v1, int v2, int v3);
    Setter &set(int v1, int v2, int v3, int v4);

    Setter &set(bool value);
    Setter &set(bool v1, bool v2);
    Setter &set(bool v1, bool v2, bool v3);
    Setter &set(bool v1, bool v2, bool v3, bool v4);

private:
    Shader &parent;
    int id;
};

}  // namespace meov::core
