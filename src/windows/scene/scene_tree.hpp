#pragma once

#include "windows/base/base_window.hpp"

namespace meov::core {
class Scene;
class Object;
}  // namespace meov::core

namespace meov::Window {

class SceneTree final : public Base {
public:
    explicit SceneTree() noexcept;
    ~SceneTree() override = default;

    void Select(std::weak_ptr<core::Scene> &&scene);

private:
	std::string mNewObjectName;
    std::weak_ptr<core::Scene> mWrappedScene;

    void Draw(const std::vector<std::shared_ptr<meov::core::Object>> &objects);

    void DrawImpl() override;
};

}  // namespace meov::Window
