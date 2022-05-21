#include "common.hpp"
#include "app_info.hpp"
#include "log_utils.hpp"

#include "core.hpp"

#include "object.hpp"
#include "transform_component.hpp"
#include "model_component.hpp"
#include "move_component.hpp"
#include "camera_component.hpp"

#include "graphics.hpp"
#include "frame_buffer.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"

#include "event_manager.hpp"

namespace meov::core {

ImGuiWindows::ImGuiWindows()
    : mLogWin{ std::make_shared<Window::Log>("Logger", ImVec2{ 1280, 850 }) } {}

void ImGuiWindows::Serialize() {
    mLogWin->Draw(true);
    mGitWin.Draw(true);
    mPropWin.Draw();
}

Core::ExecutionResult Core::Run() {
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };                 // Clear color (background default color).
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);  // Set it up here.

    // Default model displayed when the application runs.
    auto camera{ mObjects.emplace_back(std::make_shared<Object>("Camera")) };
    // camera->AddComponent<components::TransformComponent>();
    camera->AddComponent<components::MoveComponent>();
    camera->AddComponent<components::CameraComponent>(mGraphics);

    auto object{ mObjects.emplace_back(std::make_shared<Object>("Test object")) };
    object->AddComponent<components::TransformComponent>();
    object->AddComponent<components::ModelComponent>("models\\clothes.obj");

    SHIT_SHIT_SHIT.mPropWin.Select(camera);

    mRunning = true;
    utils::LogUtils::Instance()->GetLogStorage()->Subscribe(SHIT_SHIT_SHIT.mLogWin);
    while(mRunning) {
        mClock.Update();

        StartFrame();
        Update(mClock.Delta());
        Draw(*mGraphics);
        Serialize();
        RenderFrame();

        HandleEvents();
    }

    return Core::SUCCESS;
}

void Core::StartFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(mWindow);
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Core::RenderFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(mWindow);
}

void Core::Update(double delta) {
    for(auto object : mObjects)
        object->Update(delta);
}

void Core::Draw(Graphics& g) {
    mFrameBuffer->Bind();
    for(auto object : mObjects)
        object->Draw(g);
    mFrameBuffer->UnBind();
}

void Core::Serialize() {
    SHIT_SHIT_SHIT.Serialize();

    const auto im2glm = [](ImVec2&& vec) {
        return glm::vec2{ vec.x, vec.y };
    };

    ImGui::Begin("Scene");
    scenePos = im2glm(ImGui::GetWindowPos());
    sceneSize = im2glm(ImGui::GetContentRegionAvail());

    // Add rendered texture to ImGUI scene window.
    uint32_t textureID = mFrameBuffer->GetFrameTexture();
    ImGui::Image(reinterpret_cast<void*>(textureID),
                 ImVec2{ sceneSize.x, sceneSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    ImGui::End();
}


void Core::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        managers::KeyboardManager::HandleEvent(event);
        managers::MouseManager::HandleEvent(event);
        switch(event.type) {
            case SDL_QUIT: {
                mRunning = false;
            } break;
            default:
                break;
        }
    }
}


void Core::OnFail(const std::string_view&) {
    exit(-1);
}

Core::Core(std::vector<std::string>&& argv)
    : mInitTasks{
        std::make_shared<utilities::Initializer>(
            this, "STB Image",
            [] {
                stbi_set_flip_vertically_on_load(true);
                return true;
            },
            [] {
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "Logger",
            [] {
                utils::LogUtils::Instance()->Initialize();
                LOGI << "Current directory: " << fs::current_path().string();
                return true;
            },
            [] {
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "SDL",
            [] {
                if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
                    LOGF << "Error: " << SDL_GetError();
                    return false;
                }
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, AppInfo::GLSLVersionMajor());
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, AppInfo::GLSLVersionMinor());
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

                // Create window with graphics context.
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
                SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
                return true;
            },
            [] {
                SDL_Quit();
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "SDL Window",
            [&win = this->mWindow, &ctx = this->mWinContext] {
                win = SDL_CreateWindow(
                    meov::AppInfo::Name().c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    1680, 960,
                    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
                ctx = SDL_GL_CreateContext(win);
                if(SDL_GL_MakeCurrent(win, ctx) != 0) {
                    LOGF << "Error: " << SDL_GetError();
                    return false;
                }

                if(SDL_GL_SetSwapInterval(true) != 0) {
                    LOGW << "Cannot enable VSync!";
                }
                return win != nullptr;
            },
            [&win = this->mWindow, &ctx = this->mWinContext] {
                SDL_GL_DeleteContext(ctx);
                ctx = nullptr;
                SDL_DestroyWindow(win);
                win = nullptr;
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "OpenGL",
            [] {
                glbinding::Binding::initialize(
                    [](const char* name) {
                        return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name);
                    });
                glEnable(GL_DEPTH_TEST);
#if defined(_DEBUG)
                LOGD << "Debug callbacks initialization";
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallback((GLDEBUGPROC)meov::utils::OpenGLLogCallback, nullptr);

                SDL_LogSetOutputFunction(meov::utils::SDLLogCallback, nullptr);
#endif
                return true;
            },
            [] {
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "ImGui",
            [&win = this->mWindow, &ctx = this->mWinContext] {
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                auto& io{ ImGui::GetIO() };
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
                io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
                // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable viewports to drag windows outside of the main window.

                // Setup Dear ImGui style.
                ImGui::StyleColorsDark();

                // Setup Platform/Renderer backends.
                if(!ImGui_ImplSDL2_InitForOpenGL(win, ctx)) return false;
                if(!ImGui_ImplOpenGL3_Init(AppInfo::GLSLVersion().c_str())) return false;
                return true;
            },
            [] {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplSDL2_Shutdown();
                ImGui::DestroyContext();
                return true;
            }),
        std::make_shared<utilities::Initializer>(
            this, "Graphics",
            [this] {
                this->mGraphics = std::make_shared<Graphics>();
                this->mFrameBuffer = std::make_shared<FrameBuffer>();
                return true;
            },
            [] {
                return true;
            }),
    } {
}

}  // namespace meov::core
