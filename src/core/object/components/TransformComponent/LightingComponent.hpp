#pragma once

#include "component.hpp"

namespace meov::core::shaders {
class Program;
}  // namespace meov::core::shaders


namespace meov::core::components {

class LightingComponent final : public Component {
public:
    LightingComponent(/* std::shared_ptr<shader::Program> program */);
    ~LightingComponent() override = default;

    void Draw(Graphics &) override;
    void Update(double) override;
    void Serialize() override;

    bool Valid() const;

private:
    std::shared_ptr<shaders::Program> mProgram;

    bool mEnabled{ true };
    bool HasTransformComponent() const;
    bool HasModelComponent() const;
};

}  // namespace meov::core::components
