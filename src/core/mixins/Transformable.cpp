#include "transformable.hpp"

#include "graphics.hpp"

namespace meov::core::mixin {

void Transformable::Move(const glm::vec3 &offset) {
    mTransform = glm::translate(mTransform, offset);
}

void Transformable::Rotate(float angle, const glm::vec3 &direction) {
    mTransform = glm::rotate(mTransform, angle, direction);
}

void Transformable::Scale(const glm::vec3 &factor) {
    mTransform = glm::scale(mTransform, factor);
}

void Transformable::PushTransform(core::Graphics &g) const {
    g.PushTransform(mTransform);
}
void Transformable::PopTransform(core::Graphics &g) const {
    g.PopTransform();
}

glm::vec3 Transformable::GetPosition() const {
    return mTransform[3];
}

const glm::mat4 &Transformable::GetTransform() const {
    return mTransform;
}
glm::mat4 &Transformable::GetTransform() {
    return mTransform;
}

void Transformable::SetForwardDirection(const glm::vec3 &direction) {
    mForwardDirection = direction;
    mRightDirection = glm::normalize(glm::cross(mForwardDirection, mWorldUp));
    mUpDirection = glm::normalize(glm::cross(mRightDirection, mForwardDirection));
}
glm::vec3 Transformable::GetForwardDirection() const {
    return mForwardDirection;
}
glm::vec3 Transformable::GetRightDirection() const {
    return mRightDirection;
}
glm::vec3 Transformable::GetUpDirection() const {
    return mUpDirection;
}

Transformable::PushPopWrapper Transformable::MakePushPopWrapper(core::Graphics &g) const {
    return PushPopWrapper{ g, *this };
}

Transformable::PushPopWrapper::PushPopWrapper(core::Graphics &g, const Transformable &parent)
    : mGraphics{ g } {
    mGraphics.PushTransform(parent.GetTransform());
}

Transformable::PushPopWrapper::~PushPopWrapper() {
    mGraphics.PopTransform();
}

}  // namespace meov::core::mixin
