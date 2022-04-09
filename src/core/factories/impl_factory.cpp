#include "common.hpp"
#include "Definitions.hpp"

#include "impl_factory.hpp"
#include "ogl_impl_factory.hpp"


namespace meov::core::factories {

class VulcanImplFactory : public ImplFactory {
public:
    std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(shaders::ShaderType, const std::string_view &) override { return nullptr; }
    std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(const std::string &) override { return nullptr; }
    std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() { return nullptr; }
};

class NullImplFactory final : public ImplFactory {
public:
    std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(shaders::ShaderType, const std::string_view &) override { return nullptr; }
    std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(const std::string &) override { return nullptr; }
    std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() { return nullptr; }
};

ImplFactory *ImplFactory::Instance() {
    if constexpr(definitions::UsingOpenGL) {
        static std::shared_ptr<ImplFactory> factory{ std::make_unique<OGLImplFactory>() };
        return factory.get();
    }
    if constexpr(definitions::UsingVulcan) {
        static std::shared_ptr<ImplFactory> factory{ std::make_unique<VulcanImplFactory>() };
        return factory.get();
    }
    LOGF << "Cannot make any generator for ImplFactory";
    static std::shared_ptr<ImplFactory> factory{ std::make_unique<NullImplFactory>() };
    return factory.get();
}

}  // namespace meov::core::factories