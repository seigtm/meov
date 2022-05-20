#pragma once

#include <glm/vec3.hpp>

namespace meov::core::components {

class MoveComponent : public Component {
public:
    explicit MoveComponent();
    ~MoveComponent() override = default;

    void Draw(Graphics &g) override;
    void Update(double delta) override;
    void Serialize() override;

    // bool Valid() const;

private:

};

}  // namespace meov::core::components
