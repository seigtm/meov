#pragma once

#include <glm/vec3.hpp>

namespace meov::core {

class Camera {
public:
    static constexpr float DefaultYaw{ -90.0f };
    static constexpr float DefaultPitch{};
    static constexpr float DefaultSpeed{ 0.5f };
    static constexpr float DefaultSensitivity{ 0.1f };
    static constexpr float DefaultZoom{ 35.0f };

    enum class Direction {
        Forward,
        Backward,
        Left,
        Right
    };

    Camera(const glm::vec3 pos = {},
           const glm::vec3 up = glm::vec3{ 0, 1, 0 },
           float yaw = DefaultYaw,
           float pitch = DefaultPitch);

    glm::mat4 ViewMatrix() const;
    const glm::vec3 &Position() const;
    float Yaw() const;
    float Pitch() const;
    float Speed() const;
    float MouseSensitivity() const;
    float Zoom() const;

    void SetPosition(glm::vec3 &&position);
    void SetSpeed(float value);
    void SetZoom(float value);
    void SetMouseSensitivity(float value);

    void Move(Direction dir, float delta);
    void OnMouseMove(float xOffset, float yOffset, bool constrainPitch = true);
    void OnMouseScroll(float yOffset);

private:
    const glm::vec3 mWorldUp;

    glm::vec3 mPosition;
    glm::vec3 mFrontDir;
    glm::vec3 mUpDir{};
    glm::vec3 mRightDir{};

    float mYaw;
    float mPitch;

    float mSpeed{ DefaultSpeed };
    float mMouseSensitivity{ DefaultSensitivity };
    float mZoom{ DefaultZoom };

    void UpdateDirections();
};

}  // namespace meov::core
