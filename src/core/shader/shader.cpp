#include "Common.hpp"
#include "AppInfo.hpp"

#include "shader.h"

namespace meov::core {

Shader::Setter::Setter(Shader &parent, const std::string_view &name)
    : mParent{ parent } {
    Get(name);
}

Shader::Setter &Shader::Setter::Get(const std::string_view &name) {
    mId = glGetUniformLocation(mParent.GetID(), name.data());
    return *this;
}

Shader::Setter &Shader::Setter::Set(float value) {
    glUniform1f(mId, value);
    return *this;
}
Shader::Setter &Shader::Setter::Set(float v1, float v2) {
    glUniform2f(mId, v1, v2);
    return *this;
}
Shader::Setter &Shader::Setter::Set(float v1, float v2, float v3) {
    glUniform3f(mId, v1, v2, v3);
    return *this;
}
Shader::Setter &Shader::Setter::Set(float v1, float v2, float v3, float v4) {
    glUniform4f(mId, v1, v2, v3, v4);
    return *this;
}
Shader::Setter &Shader::Setter::Set(int value) {
    glUniform1i(mId, value);
    return *this;
}
Shader::Setter &Shader::Setter::Set(int v1, int v2) {
    glUniform2i(mId, v1, v2);
    return *this;
}
Shader::Setter &Shader::Setter::Set(int v1, int v2, int v3) {
    glUniform3i(mId, v1, v2, v3);
    return *this;
}
Shader::Setter &Shader::Setter::Set(int v1, int v2, int v3, int v4) {
    glUniform4i(mId, v1, v2, v3, v4);
    return *this;
}
Shader::Setter &Shader::Setter::Set(unsigned value) {
    glUniform1ui(mId, value);
    return *this;
}
Shader::Setter &Shader::Setter::Set(unsigned v1, unsigned v2) {
    glUniform2ui(mId, v1, v2);
    return *this;
}
Shader::Setter &Shader::Setter::Set(unsigned v1, unsigned v2, unsigned v3) {
    glUniform3ui(mId, v1, v2, v3);
    return *this;
}
Shader::Setter &Shader::Setter::Set(unsigned v1, unsigned v2, unsigned v3, unsigned v4) {
    glUniform4ui(mId, v1, v2, v3, v4);
    return *this;
}
Shader::Setter &Shader::Setter::Set(bool value) {
    Set(static_cast<int>(value));
    return *this;
}
Shader::Setter &Shader::Setter::Set(bool v1, bool v2) {
    Set(static_cast<int>(v1), static_cast<int>(v2));
    return *this;
}
Shader::Setter &Shader::Setter::Set(bool v1, bool v2, bool v3) {
    Set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3));
    return *this;
}
Shader::Setter &Shader::Setter::Set(bool v1, bool v2, bool v3, bool v4) {
    Set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3),
        static_cast<int>(v4));
    return *this;
}

Shader::Setter &Shader::Setter::Set(const glm::mat4 &matrix) {
    glUniformMatrix4fv(mId, 1, GL_FALSE, glm::value_ptr(matrix));
    return *this;
}

//====================== Shader ======================//

Shader::Shader(const std::string_view &vertexPath, const std::string_view &fragmentPath)
    : mProgram{ glCreateProgram() } {
    const unsigned vertex{ MakeShader(GL_VERTEX_SHADER, Load(vertexPath)) };
    if(vertex == std::numeric_limits<unsigned>::max()) return;
    const unsigned fragment{ MakeShader(GL_FRAGMENT_SHADER, Load(fragmentPath)) };
    if(fragment == std::numeric_limits<unsigned>::max()) {
        glDeleteShader(vertex);
        return;
    }

    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);
    glLinkProgram(mProgram);
    int success{};
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char error[512];
        glGetProgramInfoLog(mProgram, sizeof(error), nullptr, error);
        LOGE << "Failed while linking mProgram:\n"
             << error;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(mProgram);
}

void Shader::Use() const {
    glUseProgram(mProgram);
}

Shader::Setter Shader::Get(const std::string_view &name) {
    return Setter{ *this, name };
}

unsigned Shader::GetID() const {
    return mProgram;
}

std::string Shader::Load(const std::string_view &path) {
    if (path.empty())
        return "";
    std::ifstream ifs{ path.data() };
    return std::string{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };
}

unsigned Shader::MakeShader(GLenum type, const std::string &source) {
    const std::string defaultSrc{ GetDefaultShaderSource(type) };
    unsigned shader{ glCreateShader(type) };
    const char *src{ source.empty() ? defaultSrc.c_str() : source.c_str() };
    LOGD << GetShaderName(type) << " shader source: \n"
         << src;
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        char error[512];
        glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
        LOGE << "Error while compiling " << GetShaderName(type) << " shader:\n"
             << error << "\n";
        return std::numeric_limits<unsigned>::max();
    }
    return shader;
}

std::string Shader::GetDefaultShaderSource(GLenum type) {
    switch(type) {
    case GL_VERTEX_SHADER:
        return {
            AppInfo::GLSLVersion() + R"glsl(
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aClr;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec4 aBitAgent;

out vec4 vertexColor;
out vec2 vertexTexCoord;

uniform mat4 localTransform;
uniform mat4 globalTransform;

void main() {
    gl_Position = localTransform * globalTransform * aPos;
    vertexColor = aClr;
    vertexTexCoord = aTex;
}
)glsl"
        };
        break;
    case GL_FRAGMENT_SHADER:
        return {
            AppInfo::GLSLVersion() + R"glsl(
in vec4 vertexColor;
in vec2 vertexTexCoord;

out vec4 FragColor;

uniform sampler2D textureDiffuse1;

void main() {
    FragColor = texture(textureDiffuse1, vertexTexCoord) * vertexColor;
};
)glsl"
        };
        break;
    default:
        break;
    }
    return {};
}

std::string Shader::GetShaderName(GLenum type) {
    switch(type) {
    case GL_VERTEX_SHADER:
        return "Vertex";
    case GL_FRAGMENT_SHADER:
        return "Fragment";
    case GL_GEOMETRY_SHADER:
        return "Geometry";
    default:
        break;
    }
    return "Unknown";
}

}  // namespace meov::core