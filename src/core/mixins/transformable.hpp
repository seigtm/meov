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

    const glm::mat4 &GetTransform() const;
    glm::mat4 &GetTransform();

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
    glm::mat4 mTransform{ 1.f };
};

}  // namespace meov::core::mixin
