#pragma once

#include <string_view>
#include <vector>
#include <memory>

namespace meov::core {

class Object;
class Graphics;

class Scene {
public:
    Scene();

    void Draw(Graphics &graphics);
    void Update(double delta);

    std::shared_ptr<Object> AddObject(
        const std::string_view name, const std::shared_ptr<Object> &target = nullptr);
    std::vector<std::shared_ptr<Object>> AddObjectsUnderSelected(const std::string_view name);

    std::vector<std::weak_ptr<Object>> GetSelectedObjects() const;
    std::vector<std::shared_ptr<Object>> GetObjects() const;

private:
    std::shared_ptr<Object> mRoot;
};

}  // namespace meov::core
