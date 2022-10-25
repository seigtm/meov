#pragma once

#include "windows/base/base_window.hpp"

namespace meov::core {
class Scene;
class Object;
class Texture;
}  // namespace meov::core

namespace meov::Window {

class SceneTree final : public Base {
public:
    explicit SceneTree() noexcept;
    ~SceneTree() override = default;

    void Select(std::weak_ptr<core::Scene> &&scene);

private:
    std::weak_ptr<core::Scene> mWrappedScene;
    const std::unordered_map<std::string, std::shared_ptr<core::Texture>> mIcons;

    void DrawImpl() override;

    void Draw(const std::vector<std::shared_ptr<core::Object>> &objects);
    bool ImageButton(const std::string &icon, const ImColor &clr = IM_COL32_WHITE) const;
};

}  // namespace meov::Window
