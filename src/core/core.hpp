#pragma once

#include <vector>
#include <string>
#include <memory>

#include "initializer.hpp"
#include "time_utils.hpp"

#include "windows/git_window.hpp"
#include "windows/log_window.hpp"
#include "windows/properties_window.hpp"
#include "windows/scene_tree.hpp"
#include "windows/scene_window.hpp"

namespace meov::core {

class Graphics;
class Object;
class FrameBuffer;
class Scene;

class ImGuiWindows {
public:
    Window::Git mGitWin;
    std::shared_ptr<Window::Log> mLogWin;
    Window::Properties mPropWin;
    Window::SceneTree mSceneTree;
    Window::Scene mSceneWin;

    ImGuiWindows();
    void Serialize();
};

class Core final : public utilities::Initializer::Listener {
public:
    explicit Core(std::vector<std::string> &&argv);

    enum ExecutionResult { SUCCESS,
                           FAIL = -1 };

    ExecutionResult Run();

    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };

private:
    ImGuiWindows SHIT_SHIT_SHIT;

    bool mRunning{ false };
    utilities::time::Clock mClock;
    std::shared_ptr<Scene> mScene;
    std::shared_ptr<Graphics> mGraphics;
    std::shared_ptr<FrameBuffer> mFrameBuffer;
    glm::mat4 mProjection{ 1 };

    std::vector<utilities::Initializer::Shared> mInitTasks;

    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};
    glm::vec2 sceneSize{};
    glm::vec2 scenePos{};


    void StartFrame();
    void RenderFrame();
    void Update(double delta);
    void Draw(Graphics &g);
    void Serialize();
    void HandleEvents();

    // utilities::Initializer::Listener
    void OnFail(const std::string_view &taskName) override;
};

}  // namespace meov::core
