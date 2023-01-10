#include "common.hpp"
#include "app_info.hpp"

#include "impl_factory.hpp"
#include "ogl_impl_factory.hpp"


namespace meov::core::factories {

class VulcanImplFactory final : public ImplFactory {
public:
    std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(shaders::ShaderType, const std::string_view &) override { return nullptr; }
    std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(const std::string &) override { return nullptr; }
    std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() override { return nullptr; }
    std::shared_ptr<FrameBuffer::Impl> MakeFrameBufferImpl(int32_t width, int32_t height) override { return nullptr; }
};

class NullImplFactory final : public ImplFactory {
public:
    std::shared_ptr<shaders::Shader::Impl> MakeShaderImpl(shaders::ShaderType, const std::string_view &) override { return nullptr; }
    std::shared_ptr<shaders::Program::Impl> MakeProgramImpl(const std::string &) override { return nullptr; }
    std::shared_ptr<Graphics::Impl> MakeGraphicsImpl() override { return nullptr; }
    std::shared_ptr<FrameBuffer::Impl> MakeFrameBufferImpl(int32_t width, int32_t height) override { return nullptr; }
};

ImplFactory *ImplFactory::Instance() {
    if constexpr(AppInfo::IsOpenGL()) {
        static std::shared_ptr<ImplFactory> factory{ std::make_shared<OGLImplFactory>() };
        return factory.get();
    }
    if constexpr(AppInfo::IsVulkan()) {
        static std::shared_ptr<ImplFactory> factory{ std::make_shared<VulcanImplFactory>() };
        return factory.get();
    }
    LOGF << "Cannot make any generator for ImplFactory";
    static std::shared_ptr<ImplFactory> factory{ std::make_shared<NullImplFactory>() };
    return factory.get();
}

}  // namespace meov::core::factories
