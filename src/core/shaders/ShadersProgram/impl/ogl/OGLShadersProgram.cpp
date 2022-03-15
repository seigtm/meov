#include "Common.hpp"

#include "OGLShadersProgram.hpp"


namespace meov::core::shaders::gl {

// ============================= OGLProgramImpl ==============================//

OGLProgramImpl::OGLProgramImpl(const std::string &name) noexcept
    : Program::Impl{ name, glCreateProgram() }
{ }

OGLProgramImpl::~OGLProgramImpl() {
    glDeleteProgram(mId);
}

bool OGLProgramImpl::Attach(const std::shared_ptr<Shader> &shader) {
    if (shader == nullptr || !shader->IsValid()) return false;

    glAttachShader(mId, shader->GetID());

    mValid = Link();
    if (mValid) {
        mShaders[shader->GetType()] = shader;
    }
    return mValid;
}

bool OGLProgramImpl::Detach(const std::shared_ptr<Shader> &shader) {
    if (shader == nullptr) return false;

    size_t count{ mShaders.erase(shader->GetType()) };
    if (count == 0) {
        LOGW << "[" << mName << "] The " << shader->GetTypeName() << " shader with ID #"
            << shader->GetID() << " is not in " << mName << " shaders program.";
        return false;
    }

    glDetachShader(mId, shader->GetID());

    mValid = Link();
    if (mValid) {
        mShaders[shader->GetType()] = shader;
    }
    return mValid;
}

void OGLProgramImpl::Use() {
    glUseProgram(mId);
}
void OGLProgramImpl::UnUse() {
    glUseProgram(0);
}

bool OGLProgramImpl::IsValid() const {
    return mValid;
}

std::shared_ptr<Setter> OGLProgramImpl::Get(Program &parent, const std::string_view &name) {
    return std::make_shared<OGLSetter>(parent, name);
}

bool OGLProgramImpl::Link() {
    glLinkProgram(mId);
    int success{};
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if(!success) {
        char error[512];
        glGetProgramInfoLog(mId, sizeof(error), nullptr, error);
        LOGE << "[" << mName << "] Failed while linking mProgram:\n" << error;
        return false;
    }
    return true;
}

// ================================ OGLSetter ================================//

OGLSetter::OGLSetter(Program &parent, const std::string_view &name) : Setter{ parent } {
    Get(name);
}

Setter *OGLSetter::Get(const std::string_view &name) {
    mId = glGetUniformLocation(mParent.GetID(), name.data());
    return this;
}

Setter *OGLSetter::Set(float value) {
    glUniform1f(mId, value);
    return this;
}
Setter *OGLSetter::Set(float v1, float v2) {
    glUniform2f(mId, v1, v2);
    return this;
}
Setter *OGLSetter::Set(float v1, float v2, float v3) {
    glUniform3f(mId, v1, v2, v3);
    return this;
}
Setter *OGLSetter::Set(float v1, float v2, float v3, float v4) {
    glUniform4f(mId, v1, v2, v3, v4);
    return this;
}
Setter *OGLSetter::Set(int value) {
    glUniform1i(mId, value);
    return this;
}
Setter *OGLSetter::Set(int v1, int v2) {
    glUniform2i(mId, v1, v2);
    return this;
}
Setter *OGLSetter::Set(int v1, int v2, int v3) {
    glUniform3i(mId, v1, v2, v3);
    return this;
}
Setter *OGLSetter::Set(int v1, int v2, int v3, int v4) {
    glUniform4i(mId, v1, v2, v3, v4);
    return this;
}
Setter *OGLSetter::Set(unsigned value) {
    glUniform1ui(mId, value);
    return this;
}
Setter *OGLSetter::Set(unsigned v1, unsigned v2) {
    glUniform2ui(mId, v1, v2);
    return this;
}
Setter *OGLSetter::Set(unsigned v1, unsigned v2, unsigned v3) {
    glUniform3ui(mId, v1, v2, v3);
    return this;
}
Setter *OGLSetter::Set(unsigned v1, unsigned v2, unsigned v3, unsigned v4) {
    glUniform4ui(mId, v1, v2, v3, v4);
    return this;
}
Setter *OGLSetter::Set(bool value) {
    Set(static_cast<int>(value));
    return this;
}
Setter *OGLSetter::Set(bool v1, bool v2) {
    Set(static_cast<int>(v1), static_cast<int>(v2));
    return this;
}
Setter *OGLSetter::Set(bool v1, bool v2, bool v3) {
    Set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3));
    return this;
}
Setter *OGLSetter::Set(bool v1, bool v2, bool v3, bool v4) {
    Set(static_cast<int>(v1),
        static_cast<int>(v2),
        static_cast<int>(v3),
        static_cast<int>(v4));
    return this;
}

Setter *OGLSetter::Set(const glm::mat4 &matrix) {
    glUniformMatrix4fv(mId, 1, GL_FALSE, glm::value_ptr(matrix));
    return this;
}




} // namespace meov::core::shaders::gl

