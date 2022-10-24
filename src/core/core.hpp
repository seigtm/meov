#pragma once

#include <vector>
#include <string>
#include <memory>

#include "initializer_listener.hpp"
#include "time_utils.hpp"

namespace meov::utilities {
class Initializer;
} // namespace meov::utilities

namespace meov::Window {
class Manager;
} // namespace meov::Window

namespace meov::core {

class Graphics;
class Object;
class FrameBuffer;
class Scene;

class Core final : public utilities::InitializerListener {
public:
    explicit Core(std::vector<std::string> &&argv);

    enum ExecutionResult{
        SUCCESS,
        FAIL = -1
    };

    ExecutionResult Run();

    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };

private:
    // ImGuiWindows SHIT_SHIT_SHIT;

    bool mRunning{ false };
    utilities::time::Clock mClock;
    std::shared_ptr<Scene> mScene;
    std::shared_ptr<Graphics> mGraphics;
    std::shared_ptr<FrameBuffer> mFrameBuffer;
    std::shared_ptr<Window::Manager> mWindowManager;
    glm::mat4 mProjection{ 1 };

    std::vector<std::shared_ptr<utilities::Initializer>> mInitTasks;

    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};
    glm::vec2 sceneSize{};
    glm::vec2 scenePos{};

    void initialize();

    void StartFrame();
    void RenderFrame();
    void Update(double delta);
    void Draw(Graphics &g);
    void Serialize();
    void HandleEvents();

    // utilities::InitializerListener
    void OnFail(const std::string_view &taskName) override;
};

}  // namespace meov::core
