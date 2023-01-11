#pragma once

#include <vector>
#include <string>
#include <memory>

#include "core/initializer/initializer_listener.hpp"

namespace meov::utils {
class Initializer;
} // namespace meov::utils

namespace meov::core {

class Graphics;
class Object;
class FrameBuffer;
class Scene;

class Core final : public utils::InitializerListener {
public:
    Core();

    void Initialize();

    enum ExecutionResult{
        SUCCESS,
        FAIL = -1
    };

    ExecutionResult Run();

    [[nodiscard]] SDL_Window *GetWindow();
    [[nodiscard]] bool IsRunning() const;
    [[nodiscard]] std::shared_ptr<Scene> GetScene() const;
    [[nodiscard]] std::shared_ptr<Graphics> GetGraphics() const;
    [[nodiscard]] std::shared_ptr<FrameBuffer> GetFrameBuffer() const;

    void StartFrame();
    void RenderFrame();
    void Update(double delta);
    void Draw();
    void HandleEvents();

private:
    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };

    bool mRunning{ false };
    std::shared_ptr<Scene> mScene;
    std::shared_ptr<Graphics> mGraphics;
    std::shared_ptr<FrameBuffer> mFrameBuffer;
    glm::mat4 mProjection{ 1 };

    std::vector<std::shared_ptr<utils::Initializer>> mInitTasks;

    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};
    glm::vec2 sceneSize{};
    glm::vec2 scenePos{};

    // utils::InitializerListener
    void OnFail(const std::string_view &taskName) override;

    static void MakeTestScene(std::shared_ptr<Scene> scene, std::shared_ptr<Graphics> graphics);
};

}  // namespace meov::core
