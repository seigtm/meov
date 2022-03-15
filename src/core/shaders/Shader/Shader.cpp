#include "Common.hpp"
#include "AppInfo.hpp"

#include "Shader.hpp"
#include "ImplFactory.hpp"

namespace meov::core::shaders {

std::string getShaderName(ShaderType type) {
    switch (type) {
        case ShaderType::Vertex: return "Vertex";
        case ShaderType::TesselationControl: return "Tesselation control";
        case ShaderType::TesselationEvaluation: return "Tesselation evaluation";
        case ShaderType::Geometry: return "Geometry";
        case ShaderType::Fragment: return "Fragment";
        case ShaderType::Compute: return "Compute";
    }
    return "Unknown shader type";
}

Shader::Impl::Impl(ShaderType type, uint32_t id)
    : mType{ type }
    , mId{ id }
{ }

uint32_t Shader::Impl::GetID() const {
    return mId;
}

ShaderType Shader::Impl::GetType() const {
    return mType;
}
std::string Shader::Impl::GetTypeName() const {
    return getShaderName(mType);
}

std::string loadSources(const std::string_view &path) {
    if(path.empty())
        return "";
    std::ifstream ifs{ path.data() };
    return std::string{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };
}


void Shader::Initialize(ShaderType type, const std::string_view &source) {
    mImpl = factories::ImplFactory::Instance()->MakeShaderImpl(type, source);
}
void Shader::Destroy() {
    mImpl.reset();
}

uint32_t Shader::GetID() const {
    if (mImpl) return mImpl->GetID();
    return 0;
}
ShaderType Shader::GetType() const {
    if (mImpl) return mImpl->GetType();
    return ShaderType::Invalid;
}
std::string Shader::GetTypeName() const {
    return getShaderName(GetType());
}
bool Shader::IsValid() const {
    return mImpl != nullptr && mImpl->IsValid();
}

}  // namespace meov::core::shaders