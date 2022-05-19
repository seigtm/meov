#pragma once

#include <memory>
#include <string>

namespace meov::core {

class Graphics;

namespace components {

class Component {
public:
    using Shared = std::shared_ptr<Component>;

    explicit Component(std::string &&name);
    virtual ~Component() = default;

    const std::string &Name() const;

    virtual void Draw(Graphics &) = 0;
    virtual void Update(double) = 0;
    virtual void Serialize() {}  // for ImGui

private:
    const std::string mName;
};

}  // namespace components
}  // namespace meov::core
