#pragma once

#include "core/object/components/component.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace meov::core {

namespace shaders {
class Program;
}

namespace components {

class ShaderComponent : public Component {
public:
    explicit ShaderComponent(const fs::path &shaders) noexcept;
    ~ShaderComponent() override = default;

    void PreDraw(Graphics &) override;
    void Draw(Graphics &) override;
    void PostDraw(Graphics &) override;

    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::shared_ptr<shaders::Program> mProgram;
    fs::path mPath;
    std::string mTargetPath;
    std::string mStatus;
    bool mWasPushed{ false };
    bool mEnabled{ true };
};

}  // namespace components

}  // namespace meov::core