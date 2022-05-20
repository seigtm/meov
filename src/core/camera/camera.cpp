#include "common.hpp"

#include "camera.hpp"

namespace meov::core {

namespace {

template<class T>
T RoundByRange(T value, const T Min, const T Max) {
    if(value < Min) return Min;
    if(value > Max) return Max;
    return value;
}

}  // namespace

Camera::Camera(const glm::vec3 pos, const glm::vec3 up, float yaw, float pitch)
    : mWorldUp{ up }
    , mPosition{ pos }
    , mFrontDir{ 0.0f, 0.0f, -1.0f }
    , mYaw{ yaw }
    , mPitch{ pitch } {
    UpdateDirections();
}

glm::mat4 Camera::Projection(const glm::vec2 &screenSize) const {
    return glm::perspective(glm::radians(mZoom), screenSize.x / screenSize.y, .001f, 1000.0f);
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(mPosition, mPosition + mFrontDir, mUpDir);
}

const glm::vec3 &Camera::Position() const {
    return mPosition;
}

float Camera::Yaw() const {
    return mYaw;
}
float Camera::Pitch() const {
    return mPitch;
}
float Camera::Speed() const {
    return mSpeed;
}
float Camera::MouseSensitivity() const {
    return mMouseSensitivity;
}
float Camera::Zoom() const {
    return mZoom;
}

void Camera::SetPosition(glm::vec3 &&position) {
    mPosition = std::move(position);
}
void Camera::SetSpeed(float value) {
    mSpeed = value;
}
void Camera::SetZoom(float value) {
    mZoom = value;
}
void Camera::SetMouseSensitivity(float value) {
    mMouseSensitivity = value;
}

void Camera::Move(Direction dir, float delta) {
    switch(dir) {
        case Direction::Forward: mPosition += mFrontDir * (mSpeed * delta); break;
        case Direction::Backward: mPosition -= mFrontDir * (mSpeed * delta); break;
        case Direction::Left: mPosition -= mRightDir * (mSpeed * delta); break;
        case Direction::Right: mPosition += mRightDir * (mSpeed * delta); break;
        default: break;
    }
}

void Camera::OnMouseMove(float xOffset, float yOffset, bool constrainPitch) {
    mYaw += xOffset * mMouseSensitivity;
    mPitch += yOffset * mMouseSensitivity;
    if(constrainPitch) {
        constexpr float MaxPitch{ 89.0f };
        mPitch = RoundByRange(mPitch, -MaxPitch, MaxPitch);
    }
    UpdateDirections();
}

void Camera::OnMouseScroll(float yOffset) {
    constexpr float MinZoom{ 0.0f };
    constexpr float MaxZoom{ 45.0f };
    mZoom = RoundByRange(mZoom - yOffset, MinZoom, MaxZoom);
}

void Camera::UpdateDirections() {
    const float radPitch{ glm::radians(mPitch) };
    const float radYaw{ glm::radians(mYaw) };
    const glm::vec3 front{
        glm::cos(radYaw) * cos(radPitch),
        glm::sin(radPitch),
        glm::sin(radYaw) * glm::cos(radPitch)
    };
    mFrontDir = glm::normalize(front);
    mRightDir = glm::normalize(glm::cross(mFrontDir, mWorldUp));
    mUpDir = glm::normalize(glm::cross(mRightDir, mFrontDir));
}

}  // namespace meov::core
