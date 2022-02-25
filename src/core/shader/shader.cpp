#include "Common.hpp"

#include "shader.h"

namespace meov::core {

Shader::Setter::Setter(Shader &parent, const std::string &name)
    : parent{ parent }, id{ glGetUniformLocation(parent, name.c_str()) } {
}

Shader::Setter &Shader::Setter::set(float value) {
    glUniform1f(id, value);
    return *this;
}

Shader::Setter &Shader::Setter::set(float v1, float v2) {
    glUniform2f(id, v1, v2);
    return *this;
}

Shader::Setter &Shader::Setter::set(float v1, float v2, float v3) {
    glUniform3f(id, v1, v2, v3);
    return *this;
}

Shader::Setter &Shader::Setter::set(float v1, float v2, float v3, float v4) {
    glUniform4f(id, v1, v2, v3, v4);
    return *this;
}

Shader::Setter &Shader::Setter::set(int value) {
    glUniform1i(id, value);
    return *this;
}

Shader::Setter &Shader::Setter::set(int v1, int v2) {
    glUniform2i(id, v1, v2);
    return *this;
}

Shader::Setter &Shader::Setter::set(int v1, int v2, int v3) {
    glUniform3i(id, v1, v2, v3);
    return *this;
}

Shader::Setter &Shader::Setter::set(int v1, int v2, int v3, int v4) {
    glUniform4i(id, v1, v2, v3, v4);
    return *this;
}

Shader::Setter &Shader::Setter::set(bool value) {
    set(static_cast<int>(value));
    return *this;
}

Shader::Setter &Shader::Setter::set(bool v1, bool v2) {
    set(static_cast<int>(v1),
        static_cast<int>(v2));
    return *this;
}

Shader::Setter &Shader::Setter::set(bool v1, bool v2, bool v3) {
    set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3));
    return *this;
}

Shader::Setter &Shader::Setter::set(bool v1, bool v2, bool v3, bool v4) {
    set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3),
        static_cast<int>(v4));
    return *this;
}

//====================== Shader ======================//

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
    : program{ glCreateProgram() } {
    unsigned vertex{ makeShader(GL_VERTEX_SHADER, load(vertexPath)) };
    unsigned fragment{ makeShader(GL_FRAGMENT_SHADER, load(fragmentPath)) };

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        char error[512];
        glGetProgramInfoLog(program, sizeof(error), nullptr, error);
        LOGE << "[Shader] Failed while linking program:\n"
             << error;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::use() const {
    glUseProgram(program);
}

Shader::Setter Shader::get(const std::string &name) {
    return Setter{ *this, name };
}

Shader::operator unsigned() const {
    return program;
}

std::string Shader::load(const std::string &path) const {
    std::ifstream file{ path };
    return std::string{ std::istreambuf_iterator<char>{ file }, {} };
}

unsigned Shader::makeShader(GLenum type, const std::string &source) const {
    const std::string defaultSrc{ getDefaultShaderSource(type) };
    unsigned shader{ glCreateShader(type) };
    const char *src{ source.empty() ? defaultSrc.c_str() : source.c_str() };
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        char error[512];
        glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
        LOGE << "[Shader] Error while compiling shader "
             << static_cast<long>(type) << ":\n"
             << error << "\n";
    }
    return shader;
}

std::string Shader::getDefaultShaderSource(GLenum type) const {
    switch(type) {
    case GL_VERTEX_SHADER:
        return {
            R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aClr;
layout (location = 2) in vec2 aTex;

out vec3 vertexColor;
out vec2 vertexTexCoord;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aClr;
    vertexTexCoord = aTex;
}
)glsl"
        };
        break;
    case GL_FRAGMENT_SHADER:
        return {
            R"glsl(
#version 330 core
in vec3 vertexColor;
in vec2 vertexTexCoord;

out vec4 FragColor;

uniform bool useTexture = false;
uniform sampler2D defTexture;

void main() {
    if(useTexture) {
        FragColor = texture(defTexture, vertexTexCoord) * vec4(vertexColor, 1.0);
    } else {
        FragColor = vec4(vertexColor, 1.0);
    }
};
)glsl"
        };
        break;
    default:
        break;
    }
    return {};
}

}  // namespace meov::core