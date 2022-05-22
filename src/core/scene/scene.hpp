#pragma once

#include <string_view>
#include <vector>
#include <memory>

namespace meov::core {

class Object;
class Graphics;

class Scene {
public:
    void Draw(Graphics &graphics);
    void Update(double delta);

    std::shared_ptr<Object> AddObject(const std::string_view name);

    std::vector<std::weak_ptr<Object>> GetSelectedObjects() const;
    const std::vector<std::shared_ptr<Object>> &GetObjects() const;

private:
    std::vector<std::shared_ptr<Object>> mObjects;
};

}  // namespace meov::core
