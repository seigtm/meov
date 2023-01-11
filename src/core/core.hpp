#pragma once

#include <vector>
#include <string>
#include <memory>

#include "core/initializer/initializer_listener.hpp"
#include <utils/time/time_utils.hpp>

namespace meov::utils {
class Initializer;
} // namespace meov::utils

namespace meov::Window {
class Manager;
} // namespace meov::Window

namespace meov::core {

class Graphics;
class Object;
class FrameBuffer;
class Scene;

class Core final : public utils::InitializerListener {
public:
    Core();

    enum ExecutionResult{
        SUCCESS,
        FAIL = -1
    };

    ExecutionResult Run();

private:
    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };

    bool mRunning{ false };
    utils::time::Clock mClock;
    std::shared_ptr<Scene> mScene;
    std::shared_ptr<Graphics> mGraphics;
    std::shared_ptr<FrameBuffer> mFrameBuffer;
    std::shared_ptr<Window::Manager> mWindowManager;
    glm::mat4 mProjection{ 1 };

    std::vector<std::shared_ptr<utils::Initializer>> mInitTasks;

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

    // utils::InitializerListener
    void OnFail(const std::string_view &taskName) override;

    static void MakeTestScene(std::shared_ptr<Scene> scene, std::shared_ptr<Graphics> graphics);
};

}  // namespace meov::core
