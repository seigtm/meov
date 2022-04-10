#pragma once

#include <vector>
#include <string>
#include <memory>

#include "initializer.hpp"
#include "time_utils.hpp"

namespace meov::core {

class Graphics;

class Core final : public utilities::Initializer::Listener {
public:
    explicit Core(std::vector<std::string> &&argv);

    enum class ExecutionResult : int {
        Success,
        Fail = -1
    };

    ExecutionResult Run();

    void Update();
    void Draw();

    SDL_Window *GetSDLWindow();
    std::shared_ptr<Graphics> GetGraphics();
    double GetDeltaTime() const;

private:
    SDL_Window *mWindow{ nullptr };
    SDL_GLContext mWinContext{ nullptr };
    std::shared_ptr<Graphics> mGraphics;
    utilities::time::Clock mClock;

    std::vector<utilities::Initializer::Shared> mInitTasks;

    // utilities::Initializer::Listener
    void OnFail(const std::string_view &taskName) override;
};

class CoreHolder {
public:
    explicit CoreHolder(Core &core);

    Core &GetCore();
    const Core &GetCore() const;

private:
    Core &mCoreRef;
};

}  // namespace meov::core