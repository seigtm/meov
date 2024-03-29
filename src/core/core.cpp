#include <common>
#include <app_info/app_info.hpp>
#include <utils/time/time_utils.hpp>

#include "core/core.hpp"

#include "core/object/object.hpp"
#include "core/object/components/transform_component/transform_component.hpp"
#include "core/object/components/model_component/model_component.hpp"
#include "core/object/components/move_component/move_component.hpp"
#include "core/object/components/camera_component/camera_component.hpp"
#include "core/object/components/lighting_component/lighting_component.hpp"
#include "core/object/components/skybox_component/skybox_component.hpp"
#include "core/object/components/shader_component/shader_component.hpp"

#include "core/graphics/graphics.hpp"
#include "core/framebuffer/frame_buffer.hpp"
#include "core/resources/manager/resource_manager.hpp"
#include "core/camera/camera.hpp"

#include "core/scene/scene.hpp"

#include "core/event_manager/event_manager.hpp"

#include "core/initializer/initializer_factory.hpp"
#include "core/initializer/initializer.hpp"

namespace meov::core {

void Core::Initialize() {
    mGraphics->PushProgram(*RESOURCES->LoadProgram("shaders/default"));
    MakeTestScene(mScene, mGraphics);
    mRunning = true;

    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };                 // Clear color (background default color).
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);  // Set it up here.
}

Core::ExecutionResult Core::Run() {
    Initialize();

    utils::time::Clock mClock{};
    while(mRunning) {
        mClock.Update();

        StartFrame();
        Update(mClock.Delta());
        Draw();
        RenderFrame();

        HandleEvents();
    }

    return Core::SUCCESS;
}

SDL_Window *Core::GetWindow() {
    return mWindow;
}

bool Core::IsRunning() const {
    return mRunning;
}

std::shared_ptr<Scene> Core::GetScene() const {
    return mScene;
}
std::shared_ptr<Graphics> Core::GetGraphics() const {
    return mGraphics;
}
std::shared_ptr<FrameBuffer> Core::GetFrameBuffer() const {
    return mFrameBuffer;
}

void Core::StartFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Core::RenderFrame() {
    SDL_GL_SwapWindow(mWindow);
}

void Core::Update(const f64 delta) {
    mScene->Update(delta);
}

void Core::Draw() {
    mFrameBuffer->Bind();
    mScene->Draw(*mGraphics);
    mFrameBuffer->UnBind();
}

void Core::HandleEvents() {
    static auto handleKeyDownEvent{ [this](SDL_Event &event){
        if(event.key.keysym.sym == SDLK_F5) {
            std::deque<fs::path> textures;
            while(!mGraphics->CurrentProgram().IsValid()) {
                textures.push_front(mGraphics->CurrentProgram().GetPath());
                mGraphics->PopProgram();
            }
            for(auto&& path : textures) {
                mGraphics->PushProgram(*RESOURCES->LoadProgram(std::move(path), true));
            }
            LOGI << "Textures were reloaded";
        }
    } };

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        managers::KeyboardManager::HandleEvent(event);
        managers::MouseManager::HandleEvent(event);
        switch(event.type) {
            [[likely]] case SDL_KEYDOWN: {
                handleKeyDownEvent(event);
            } break;
            // case SDL_WINDOWEVENT_RESIZED: {
            // } break;
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

void Core::MakeTestScene(std::shared_ptr<Scene> scene, std::shared_ptr<Graphics> graphics) {
    auto camera{ scene->AddObject("Camera") };
    camera->AddComponent<components::TransformComponent>()->Move({ .0f, 2.f, 6.f });
    camera->AddComponent<components::MoveComponent>();
    camera->AddComponent<components::CameraComponent>(graphics);

    // Default model displayed when the application runs.
    if (auto environment{ scene->AddObject("environment") }; environment != nullptr) {
        environment->AddComponent<components::ShaderComponent>("shaders/lighting/PhongBased");
        auto objects{ scene->AddObject("Objects", environment) };
        auto object{ scene->AddObject("Test object", objects) };
        object->AddComponent<components::TransformComponent>();
        object->AddComponent<components::ModelComponent>("models/barrel/wine_barrel_01_4k.gltf");

        auto lights{ scene->AddObject("Lights", environment) };

        auto dirLight{ scene->AddObject("Directional light", lights) };
        dirLight->AddComponent<components::TransformComponent>()->Move({ 10, 10, 10 });
        dirLight->AddComponent<components::DirectionalLightingComponent>(glm::vec3{ -1.f, -1.f, -1.f });

        auto pointLight{ scene->AddObject("Point light", lights) };
        if (auto transform{ pointLight->AddComponent<components::TransformComponent>() }; transform) {
            transform->Move({ 1, 1, 1 });
            transform->Scale({ .5f, .5f, .5f });
        }
        pointLight->AddComponent<components::PointLightingComponent>();
        pointLight->AddComponent<components::ModelComponent>("models/blub/blub.fbx");

        auto spotLight{ scene->AddObject("Spot light", lights) };
        if (auto transform{ spotLight->AddComponent<components::TransformComponent>() }; transform) {
            transform->Move({ -1, 1, 1 });
            transform->Scale({ .5f, .5f, .5f });
        }
        spotLight->AddComponent<components::SpotLightingComponent>(glm::vec3{ 1.f, -1.f, -1.f });
        spotLight->AddComponent<components::ModelComponent>("models/blub/blub.obj");
    }

    auto skybox{ scene->AddObject("Skybox") };
    skybox->AddComponent<components::TransformComponent>();
    skybox->AddComponent<components::ModelComponent>("models/skybox/skybox.obj");
    skybox->AddComponent<components::SkyboxComponent>("models/skybox");
    skybox->AddComponent<components::ShaderComponent>("shaders/skybox/skybox");
}

Core::Core()
    : mInitTasks{
        utils::InitializerFactory::load("stb_image", this),
        utils::InitializerFactory::load("logger", this),
        utils::InitializerFactory::load("sdl", this),
        std::make_shared<utils::Initializer>(
            this, "SDL Window",
            [&win = this->mWindow, &ctx = this->mWinContext] {
                win = SDL_CreateWindow(
                    meov::AppInfo::Title().data(),
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
        utils::InitializerFactory::load("opengl", this),
        std::make_shared<utils::Initializer>(
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
                if(!ImGui_ImplOpenGL3_Init(AppInfo::GLSLVersion().data())) return false;
                return true;
            },
            [] {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplSDL2_Shutdown();
                ImGui::DestroyContext();
                return true;
            }),
        std::make_shared<utils::Initializer>(
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
