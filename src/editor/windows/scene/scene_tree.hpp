#pragma once

#include <utils/types.hpp>
#include "editor/windows/base/base_window.hpp"

namespace meov::core {
class Scene;
class Object;
namespace resources {
class Texture;
}  // namespace resources
}  // namespace meov::core

namespace meov::Window {

class SceneTree final : public Base {
public:
    explicit SceneTree() noexcept;
    ~SceneTree() override = default;

    void Select(wptr<core::Scene> &&scene);

private:
    wptr<core::Scene> mWrappedScene;
    const umap<std::string, sptr<core::resources::Texture>> mIcons;

    void DrawImpl() override;

    void Draw(const std::vector<std::shared_ptr<core::Object>> &objects);
    bool ImageButton(const std::string &icon, const ImColor &clr = IM_COL32_WHITE) const;
};

}  // namespace meov::Window
