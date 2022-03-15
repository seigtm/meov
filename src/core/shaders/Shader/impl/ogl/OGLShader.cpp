#include "Common.hpp"

#include "OGLShader.hpp"

namespace meov::core::shaders::gl {

OGLShaderImpl::OGLShaderImpl(ShaderType type, const std::string_view &source)
    : Shader::Impl{ type,  glCreateShader(GetOriginalType(type)) }
{
    if (source.empty()) {
        const std::string defaultSrc{ getDefaultShaderSource(type) };
        const char *data{ defaultSrc.c_str() };
        glShaderSource(mId, 1, &data, nullptr);
    } else {
        const char *data{ source.data() };
        glShaderSource(mId, 1, &data, nullptr);
    }
    glCompileShader(mId);

    GLboolean compiled;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &compiled);
    if(compiled != GL_TRUE) {
        char error[512];
        glGetShaderInfoLog(mId, sizeof(error), nullptr, error);
        LOGE << "Error while compiling " << getShaderName(type) << " shader:\n" << error << "\n";
    } else {
        mValid = true;
    }
}

OGLShaderImpl::~OGLShaderImpl() {
    glDeleteShader(mId);
    mId = 0;
    mValid = false;
}

GLenum OGLShaderImpl::GetOriginalType(ShaderType type) {
    switch(type) {
        case ShaderType::Vertex: return GL_VERTEX_SHADER;
        case ShaderType::TesselationControl: return GL_TESS_CONTROL_SHADER;
        case ShaderType::TesselationEvaluation: return GL_TESS_EVALUATION_SHADER;
        case ShaderType::Geometry: return GL_GEOMETRY_SHADER;
        case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
        case ShaderType::Compute: return GL_COMPUTE_SHADER;
    }
    return GL_VERTEX_SHADER;
}

bool OGLShaderImpl::IsValid() const {
    return mValid;
}

std::string getDefaultShaderSource(ShaderType type) {
    switch(type) {
        case ShaderType::Vertex:
            return
#include "default_shaders/vertex.glsl"
        case ShaderType::Fragment:
            return
#include "default_shaders/fragment.glsl"
        default:
            break;
    }
    return "";
}

} // namespace meov::core::gl