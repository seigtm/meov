#pragma once

#include <vector>
#include <string>
#include <utils/types.hpp>

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

    enum ExecutionResult : i8 {
        FAIL = -1,
        SUCCESS,
    };

    ExecutionResult Run();

    [[nodiscard]] SDL_Window *GetWindow();
    [[nodiscard]] bool IsRunning() const;
    [[nodiscard]] sptr<Scene> GetScene() const;
    [[nodiscard]] sptr<Graphics> GetGraphics() const;
    [[nodiscard]] sptr<FrameBuffer> GetFrameBuffer() const;

    void StartFrame();
    void RenderFrame();
    void Update(const f64 delta);
    void Draw();
    void HandleEvents();

private:
    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };

    bool mRunning{ false };
    sptr<Scene> mScene;
    sptr<Graphics> mGraphics;
    sptr<FrameBuffer> mFrameBuffer;
    glm::mat4 mProjection{ 1 };

    std::vector<sptr<utils::Initializer>> mInitTasks;

    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};
    glm::vec2 sceneSize{};
    glm::vec2 scenePos{};

    // utils::InitializerListener
    void OnFail(const std::string_view &taskName) override;

    static void MakeTestScene(sptr<Scene> scene, sptr<Graphics> graphics);
};

}  // namespace meov::core
