#include "common.hpp"
#include "app_info.hpp"

#include "core.hpp"

#include "object.hpp"
#include "transform_component.hpp"
#include "model_component.hpp"
#include "move_component.hpp"
#include "camera_component.hpp"
#include "lighting_component.hpp"
#include "skybox_component.hpp"
#include "shader_component.hpp"

#include "graphics.hpp"
#include "frame_buffer.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"

#include "scene.hpp"

#include "event_manager.hpp"

#include "initializer_factory.hpp"
#include "initializer.hpp"

#include "windows/gui_manager/gui_manager.hpp"
#include "windows/scene/scene_tree.hpp"
#include "windows/scene/scene_window.hpp"
#include "windows/log/log_window.hpp"
#include "windows/properties/properties_window.hpp"

namespace meov::core {

Core::ExecutionResult Core::Run() {
    initialize();

    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };                 // Clear color (background default color).
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);  // Set it up here.

    mRunning = true;
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

void Core::initialize() {
    mWindowManager = std::make_shared<Window::Manager>();
    mGraphics->PushProgram(*RESOURCES->LoadProgram("shaders/lighting/PhongBased"));

    auto skybox{ mScene->AddObject("Skybox") };
    skybox->AddComponent<components::TransformComponent>();
    skybox->AddComponent<components::ModelComponent>("models/skybox/skybox.obj");
    skybox->AddComponent<components::SkyboxComponent>("models/skybox");
    skybox->AddComponent<components::ShaderComponent>("shaders/skybox/skybox");

    auto camera{ mScene->AddObject("Camera") };
    camera->AddComponent<components::TransformComponent>();
    camera->AddComponent<components::MoveComponent>();
    camera->AddComponent<components::CameraComponent>(mGraphics);

    // Default model displayed when the application runs.
    auto objects{ mScene->AddObject("Objects") };
    auto object{ mScene->AddObject("Test object", objects) };
    object->AddComponent<components::TransformComponent>();
    object->AddComponent<components::ModelComponent>("models/clothes/clothes.obj");

    auto lights{ mScene->AddObject("Lights") };

    auto dirLight{ mScene->AddObject("Directional light", lights) };
    dirLight->AddComponent<components::TransformComponent>()->Move({ 10, 10, 10 });
    dirLight->AddComponent<components::DirectionalLightingComponent>(glm::vec3{ -1.f, -1.f, -1.f });

    auto lighting{ mScene->AddObject("Point light", lights) };
    lighting->AddComponent<components::TransformComponent>()->Move({ -10, 10, 10 });
    lighting->AddComponent<components::PointLightingComponent>();
    lighting->AddComponent<components::ModelComponent>("models/blub/blub.fbx");

    auto spotLight{ mScene->AddObject("Spot light", lights) };
    spotLight->AddComponent<components::TransformComponent>()->Move({ 10, 10, 10 });
    spotLight->AddComponent<components::SpotLightingComponent>(glm::vec3{ -1.f, -1.f, -1.f });
    spotLight->AddComponent<components::ModelComponent>("models/blub/blub.obj");

    if (auto sceneView{ mWindowManager->getAs<Window::Scene>("scene") }; sceneView)
        sceneView->Select(mFrameBuffer);
    if (auto sceneTreeView{ mWindowManager->getAs<Window::SceneTree>("scene_tree") }; sceneTreeView)
        sceneTreeView->Select(mScene);

    if (auto logView{ mWindowManager->getAs<Window::Log>("log") }; logView)
        utils::LogUtils::Instance()->GetLogStorage()->Subscribe(logView);

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
    mScene->Update(delta);
    if (auto propertiesView{ mWindowManager->getAs<Window::Properties>("properties") }; propertiesView)
        propertiesView->Select(mScene->GetSelectedObjects());
}

void Core::Draw(Graphics& g) {
    mFrameBuffer->Bind();
    mScene->Draw(g);
    mFrameBuffer->UnBind();
}

void Core::Serialize() {
    mWindowManager->Draw();
}


void Core::HandleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        managers::KeyboardManager::HandleEvent(event);
        managers::MouseManager::HandleEvent(event);
        switch(event.type) {
            case SDL_KEYDOWN: {
                if(event.key.keysym.sym == SDLK_F5) {
                    std::deque<fs::path> textures;
                    while(!mGraphics->CurrentProgram().IsValid()) {
                        textures.push_front(mGraphics->CurrentProgram().GetPath());
                        mGraphics->PopProgram();
                    }
                    for(auto&& path : textures) {
                        mGraphics->PushProgram(*RESOURCES->LoadProgram(std::move(path), true));
                    }
                    LOGI << "Textures was reloaded";
                }
            } break;
            case SDL_WINDOWEVENT_RESIZED: {
            } break;
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
        utilities::InitializerFactory::load("stb_image", this),
        utilities::InitializerFactory::load("logger", this),
        utilities::InitializerFactory::load("sdl", this),
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
        utilities::InitializerFactory::load("opengl", this),
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
            this, "Core active components",
            [this] {
                this->mGraphics = std::make_shared<Graphics>();
                this->mFrameBuffer = std::make_shared<FrameBuffer>();
                this->mScene = std::make_shared<Scene>();
                return true;
            },
            [] {
                return true;
            }),
    } {
}

}  // namespace meov::core
