#pragma once

#include <string>

namespace meov::core::shaders {

enum class ShaderType {
    Vertex,
    TesselationControl,
    TesselationEvaluation,
    Geometry,
    Fragment,
    Compute,

    Invalid
};

std::string getShaderName(ShaderType type);
ShaderType getTypeByExtention(const std::string &ext);

class Shader final {
public:
    class Impl {
    public:
        explicit Impl(ShaderType type, uint32_t id = 0);
        virtual ~Impl() = default;

        virtual uint32_t GetID() const;
        virtual bool IsValid() const = 0;

        ShaderType GetType() const;
        std::string GetTypeName() const;

    protected:
        ShaderType mType;
        uint32_t mId;
    };


    void Initialize(ShaderType type, const std::string_view &source = "");
    void Destroy();

    uint32_t GetID() const;
    ShaderType GetType() const;
    std::string GetTypeName() const;
    bool IsValid() const;

private:
    std::shared_ptr<Impl> mImpl;
};

}  // namespace meov::core::shaders
