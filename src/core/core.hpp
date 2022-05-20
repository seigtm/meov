#pragma once

#include <vector>
#include <string>
#include <memory>

#include "initializer.hpp"
#include "time_utils.hpp"

#include "windows/git_window.hpp"
#include "windows/log_window.hpp"
#include "windows/toolbar_window.hpp"
#include "windows/properties_window.hpp"

namespace meov::core {

class Graphics;
class Object;
class FrameBuffer;
class Camera;  // todo: Remove class and make CameraComponent

class ImGuiWindows {
public:
    Window::Git mGitWin;
    std::shared_ptr<Window::Log> mLogWin;
    Window::Properties mPropWin;

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
    std::shared_ptr<Graphics> mGraphics;
    std::shared_ptr<FrameBuffer> mFrameBuffer;
    std::shared_ptr<Camera> mCamera;
    glm::mat4 mProjection{ 1 };

    std::vector<utilities::Initializer::Shared> mInitTasks;
    std::vector<std::shared_ptr<Object>> mObjects;

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
