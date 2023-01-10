#include "common.hpp"

#include "loader.hpp"
#include "shaders_program.hpp"
#include "scope_wrapper.hpp"

namespace meov::core::resources {

struct STBImage{
    int width{};
    int height{};
    int channels{};
    unsigned char *bytes{ nullptr };
    bool wasLoaded{ false };

    explicit STBImage(const std::string_view filename)
        : bytes{ stbi_load(filename.data(), &width, &height, &channels, 0) }
        , wasLoaded{ bytes != nullptr } { }
    ~STBImage() {
        if (wasLoaded) {
            stbi_image_free(bytes);
        }
    }
    bool operator==(const STBImage &other) const {
        return width == other.width && height == other.height && channels == other.channels;
    }

    STBImage(const STBImage &other) = delete;
    STBImage& operator=(const STBImage &other) = delete;

    STBImage(STBImage &&other) noexcept
        : width{ other.width }, height{ other.height }, channels{ other.channels }
        , bytes{ other.bytes }, wasLoaded{ other.wasLoaded } {
        other.width = 0;
        other.height = 0;
        other.channels = 0;
        other.bytes = nullptr;
        other.wasLoaded = false;
    }
    STBImage& operator=(STBImage &&other) noexcept {
        if (this == &other) return *this;

        if (wasLoaded) stbi_image_free(bytes);

        width = other.width;
        height = other.height;
        channels = other.channels;
        bytes = other.bytes;
        wasLoaded = other.wasLoaded;

        other.width = 0;
        other.height = 0;
        other.channels = 0;
        other.bytes = nullptr;
        other.wasLoaded = false;

        return *this;
    }
};

std::shared_ptr<Texture> Loader::LoadTexture(const fs::path& path, const Texture::Type type) {
    if(path.empty()) {
        LOGW << "Creating texture with empty path parameter!";
        return nullptr;
    }

    int width{};
    int height{};
    int channels{};
    auto bytes{ stbi_load(path.string().c_str(), &width, &height, &channels, 0) };
    if(nullptr == bytes) {
        LOGE << "Error while loading texture from '" << path.string() << "'";
        LOGE << "    " << stbi_failure_reason();
        return nullptr;
    }

    auto texture{ std::make_shared<meov::core::Texture>(bytes, width, height, channels, type) };
    texture->SetPath(path);

    stbi_image_free(bytes);

    return texture;
}

std::shared_ptr<Texture> Loader::LoadSkybox(const fs::path& path) {
    if(path.empty()) {
        LOGW << "Creating skybox texture with empty path parameter!";
        return nullptr;
    }

    // Vector of correctly named faces files.
    static constexpr std::array faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };
    // Disabling vertical flip to get textures right.

    const utils::ScopeWrapper stbiFlipVerticallyWrapper([] {
        stbi_set_flip_vertically_on_load(false);
    }, [] {
        stbi_set_flip_vertically_on_load(true);
    });

    // Array of bytes.
    constexpr size_t ImagesCount{ 6 };
    std::vector<STBImage> images;
    images.reserve(ImagesCount);
    // Load every face.
    const std::string pathForLog{ path.string() };
    for(const auto &face : faces) {
        const auto filename{ path / face };
        const auto &image{ images.emplace_back<const std::string_view>(filename.string()) };
        if(!image.wasLoaded) {
            LOGE << "Error while loading texture "
                 << "'" << face << "'"
                 << " from '" << path.string() << "'";
            LOGE << "    " << stbi_failure_reason();
            return nullptr;
        }
        if(images.size() > 1 && images.front() != image) {
            constexpr std::string_view errmsg{
                "Can't load skybox because its images don't have"
                " the same size and number of channels."
            };
            LOGE << errmsg.data() << " Path: " << pathForLog.c_str();
            throw std::invalid_argument{ std::string{ errmsg } };
        }
    }
    // Create texture with array<bytes> c-tor.
    std::array<unsigned char *, ImagesCount> bytes{};
    size_t id{};
    for (auto &image : images) {
        bytes.at(id++) = image.bytes;
    }
    auto &image{ images.front() };

    auto texture{
        std::make_shared<meov::core::Texture>(std::move(bytes),
            image.width, image.height, image.channels)
    };  ///< FIXME: We hope that every cubemap image has the same width, height and channels.

    texture->SetPath(path);

    LOGD << "Skybox texture '" << pathForLog.c_str() << "' was loaded!";
    return texture;
}

std::shared_ptr<shaders::Shader> Loader::LoadShader(const fs::path& path,
                                                    const shaders::ShaderType type) {
    if(type == shaders::ShaderType::Invalid || path.empty()) {
        return nullptr;
    }

    std::ifstream ifs{ path };
    const std::string sources{ { std::istreambuf_iterator<char>{ ifs } }, std::istreambuf_iterator<char>{} };

    auto shader{ std::make_shared<shaders::Shader>() };
    shader->Initialize(type, sources);
    return shader;
}

std::shared_ptr<shaders::Program> Loader::LoadProgram(const fs::path& path) {
    if(path.empty()) return nullptr;

    const auto name{ path.filename() };
    const auto root{ path.parent_path() };
    if(!fs::exists(root))
        return nullptr;

    auto program{ std::make_shared<shaders::Program>(name.string()) };
    program->SetPath(path);
    program->Initialize();
    for(const auto& entry : fs::directory_iterator(root)) {
        const fs::path entryPath{ entry };
        program->Attach(
            LoadShader(entryPath, shaders::getTypeByExtention(entryPath.extension().string())));
    }
    return program;
}

}  // namespace meov::core::resources
