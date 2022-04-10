#include "common.hpp"

#include "graphics.hpp"
#include "core.hpp"
#include "core_initializers.hpp"

#include "resource_manager.hpp"

namespace meov::core {

Core::Core(std::vector<std::string>&& argv)
    : mInitTasks{
        initializers::MakeSDLInitializer(this),
        initializers::MakeSDLWindowInitializer(this, mWindow, mWinContext),
        initializers::MakeOpenGLInitializer(this),
        initializers::MakeImGuiInitializer(this, mWindow, mWinContext) }
    , mGraphics{ std::make_shared<meov::core::Graphics>() } {

    if(auto defShader{ RESOURCES->LoadProgram("shaders/default") }; defShader) {
        mGraphics->PushProgram(*defShader);
    } else {
        LOGE << "Cannot load default shaders!";
    }
}

Core::ExecutionResult Core::Run() {
    return Core::ExecutionResult::Success;
}

void Core::Update() {
    mClock.Update();
}

void Core::Draw() {
}

SDL_Window *Core::GetSDLWindow() {
    return mWindow;
}

std::shared_ptr<Graphics> Core::GetGraphics() {
    return mGraphics;
}

double Core::GetDeltaTime() const {
    return mClock.Delta();
}


void Core::OnFail(const std::string_view &task) {
    LOGF << "Booooom from " << task;
    exit(-1);
}


CoreHolder::CoreHolder(Core &core) : mCoreRef{ core } {}

Core &CoreHolder::GetCore() {
    return mCoreRef;
}

const Core &CoreHolder::GetCore() const {
    return mCoreRef;
}

}  // namespace meov::core