#pragma once

#include "core/object/components/component.hpp"

namespace meov::core {
class Graphics;

namespace shaders {
class Program;
}  // namespace shaders

}  // namespace meov::core


namespace meov::core::components {

class LightingComponent : public Component {
protected:
    explicit LightingComponent(std::string &&name);
    ~LightingComponent() override = default;

    void Serialize() override;

    virtual bool Valid() const;

    void SetupDefaults(const std::string &name, shaders::Program &program);

    bool mEnabled{ true };
    bool mSerializerOpened{ false };

    glm::vec3 mAmbient{ 1.0f, 1.0f, 1.0f };
    glm::vec3 mDiffuse{ 0.0f, 0.0f, 0.0f };
    glm::vec3 mSpecular{ 1.0f, 1.0f, 1.0f };

    bool HasTransformComponent() const;
};

class DirectionalLightingComponent final : public LightingComponent {
public:
    explicit DirectionalLightingComponent(glm::vec3 &&dir);
    ~DirectionalLightingComponent() override;

    void PreDraw(Graphics &) override;
    void Serialize() override;

private:
    static bool sInstanced;
    bool mAmIExcess{ false };
    glm::vec3 mDirection;
};

class PointLightingComponent final : public LightingComponent {
public:
    explicit PointLightingComponent();
    ~PointLightingComponent() override;

    void PreDraw(Graphics &) override;
    void Serialize() override;

private:
    struct ControlBlock {
        static constexpr size_t MaxPointLights{ 10 };
        bool mInitialized{ false };
        std::array<bool, MaxPointLights> mUsing{ false };
    };
    static ControlBlock sControl;

    int mId{};
    std::string mTextureName;
    float mConstant{ 1.0f };
    float mLinear{ 1.0f };
    float mQuadratic{ 1.0f };
};

class SpotLightingComponent final : public LightingComponent {
public:
    explicit SpotLightingComponent(glm::vec3 &&dir);
    ~SpotLightingComponent() override;

    void PreDraw(Graphics &) override;
    void Serialize() override;

private:
    static bool sInstanced;
    bool mAmIExcess{ false };
    glm::vec3 mDirection;

    float mCutOff;
    float mOuterCutOff;

    float mConstant{ 1.0f };
    float mLinear{ 1.0f };
    float mQuadratic{ 1.0f };
};

}  // namespace meov::core::components
