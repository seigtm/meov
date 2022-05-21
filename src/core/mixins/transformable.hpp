#pragma once

#include <glm/glm.hpp>

namespace meov::core {
class Graphics;
}

namespace meov::core::mixin {

class Transformable {
public:
    void Move(const glm::vec3 &offset);
    void Rotate(float angle, const glm::vec3 &direction = { 0.f, 1.f, 0.f });
    void Scale(const glm::vec3 &factor);

    void PushTransform(core::Graphics &g) const;
    void PopTransform(core::Graphics &g) const;

    glm::vec3 GetPosition() const;

    const glm::mat4 &GetTransform() const;
    glm::mat4 &GetTransform();

    void SetForwardDirection(const glm::vec3 &direction);
    glm::vec3 GetForwardDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetUpDirection() const;

    class PushPopWrapper {
        friend class Transformable;
        PushPopWrapper(core::Graphics &g, const Transformable &parent);

    public:
        ~PushPopWrapper();

    private:
        core::Graphics &mGraphics;
    };

    PushPopWrapper MakePushPopWrapper(core::Graphics &g) const;

private:
    const glm::vec3 mWorldUp{ 0.0f, 1.0f, 0.0f };
    glm::mat4 mTransform{ 1.f };
    glm::vec3 mForwardDirection{ 0.0f, 0.0f, -1.0f };
    glm::vec3 mUpDirection{ 1.0f, 0.0f, 0.0f };
    glm::vec3 mRightDirection{ 0.0f, 1.0f, 0.0f };
};

}  // namespace meov::core::mixin
