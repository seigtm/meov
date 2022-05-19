#define SDL_MAIN_HANDLED

#include "ImGuiFileDialog.h"

#include "common.hpp"
#include "app_info.hpp"
#include "log_utils.hpp"
#include "time_utils.hpp"

#include "windows/git_window.hpp"
#include "windows/log_window.hpp"
#include "windows/toolbar_window.hpp"
#include "windows/properties.hpp"

#include "ogl_frame_buffer.hpp"
#include "shaders_program.hpp"
#include "mesh.h"
#include "model.hpp"
#include "vertex.h"
#include "texture.hpp"
#include "graphics.hpp"

#include "core.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"

#include "TransformComponent.hpp"
#include "ModelComponent.hpp"
#include "object.hpp"

int main() {
    stbi_set_flip_vertically_on_load(true);
    // Logger utilities.
    meov::utils::LogUtils::Instance()->Initialize();
    LOGI << "Current directory: " << fs::current_path().string();

    // Core application with SDL window in it.
    meov::core::Core core{ std::vector<std::string>{} };

    // Graphics object.
    std::shared_ptr graphics{ std::make_shared<meov::core::Graphics>() };

    // Loading shader program.
    auto program{ RESOURCES->LoadProgram("shaders\\default") };
    // Pushing it to our graphics object.
    graphics->PushProgram(*program);

    // Default model displayed when the application runs.
    auto object{ std::make_shared<meov::core::Object>("Test object") };
    object->AddComponent<meov::core::components::TransformComponent>();
    object->AddComponent<meov::core::components::ModelComponent>("models\\clothes.obj");

    // auto modelObject{ RESOURCES->LoadModel("models\\clothes.obj") };

    // Frame buffer object initialization.
    meov::core::gl::FrameBuffer buffer;
    buffer.Initialize();

    // Camera object and variables-helpers.
    auto camera{ std::make_shared<meov::core::Camera>(glm::vec3{ .0f, .0f, 60.0f }) };
    glm::mat4 projection{ 1 };
    // glm::mat4 model{ 1.f };
    glm::vec3 lightPos{ 1.f, 1.f, 1.f };
    bool blinn{ true };  // Use Phong reflection model.

    // Mouse pressed boolean and vector of last coordinates.
    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};

    // Visibility booleans for windows.
    bool showScene{ true };
    bool showLog{ true };
    bool showGit{ true };
    bool showCamera{ true };
    bool showLightning{ true };

    // Main loop variables.
    bool done{ false };
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };                 // Clear color (background default color).
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);  // Set it up here.
    meov::utilities::time::Clock clock;                                    // Timer.
    // Dear ImGui windows.
    // meov::Window::ToolBar toolbarW{ modelObject, done, showLog, showGit, showCamera, showScene, showLightning };  // Toolbar.
    meov::Window::Git gitW;                                                                                       // Git info.
    meov::Window::Log::Reference logW{ new meov::Window::Log{ "Log", { 1280, 850 } } };                           // Logger window.
    meov::Window::Properties propertiesW;
    propertiesW.Select(object);

    // Subscribing log storage to our logger window.
    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW);
    }
    // Start main loop.
    LOGI << "Start main loop";
    while(!done) {
        clock.Update();
        const auto view{ camera->ViewMatrix() };
        program->Use();
        program->Get("projection")->Set(projection);
        program->Get("view")->Set(view);
        // program->Get("model")->Set(model);
        program->UnUse();
        if(object)
            object->Update(clock.Delta());

        // Start the Dear ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(core.mWindow);
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw model object.
        buffer.Bind();
        // if(modelObject)
        // modelObject->Draw(*graphics);
        if(object)
            object->Draw(*graphics);
        buffer.UnBind();

        // Draw scene window.
        // TODO: Move it to SceneWindow class and make getters for this vars.
        ImVec2 scenePos{};
        ImVec2 sceneSize{};
        if(showScene) {
            ImGui::Begin("Scene");
            scenePos = ImGui::GetWindowPos();
            sceneSize = ImGui::GetContentRegionAvail();
            projection = glm::perspective(
                glm::radians(camera->Zoom()), sceneSize.x / sceneSize.y, .001f, 100.0f);
            // Add rendered texture to ImGUI scene window.
            uint32_t textureID = buffer.GetFrameTexture();
            ImGui::Image(reinterpret_cast<void *>(textureID),
                         ImVec2{ sceneSize.x, sceneSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            ImGui::End();
        }

        // toolbarW.Draw();
        logW->Draw(showLog);
        gitW.Draw(showGit);
        propertiesW.Draw();

        if(showCamera) {
            ImGui::Begin("Camera");
            auto position{ camera->Position() };
            if(ImGui::InputFloat3("Position", glm::value_ptr(position))) {
                camera->SetPosition(std::move(position));
            }
            ImGui::Text("Yaw | Pitch: [%.2f | %.2f]", camera->Yaw(), camera->Pitch());
            auto speed{ camera->Speed() };
            if(ImGui::InputFloat("Speed", &speed)) {
                camera->SetSpeed(speed);
            }
            auto sensitivity{ camera->MouseSensitivity() };
            if(ImGui::InputFloat("Sensitivity", &sensitivity)) {
                camera->SetMouseSensitivity(sensitivity);
            }
            auto zoom{ camera->Zoom() };
            if(ImGui::InputFloat("Zoom", &zoom)) {
                camera->SetZoom(zoom);
            }
            ImGui::Text(
                "View: [%.2f, %.2f, %.2f, %.2f]\n"
                "      [%.2f, %.2f, %.2f, %.2f]\n"
                "      [%.2f, %.2f, %.2f, %.2f]",
                view[0].x, view[0].y, view[0].z, view[0].w,
                view[1].x, view[1].y, view[1].z, view[1].w,
                view[2].x, view[2].y, view[2].z, view[2].w);
            // ImGui::Text("Object position: [%.2f, %.2f, %.2f]", model[0].w, model[1].w, model[2].w);
            ImGui::End();
        }
        // Draw lightning window.
        if(showLightning) {
            ImGui::Begin("Lightning");
            program->Use();
            if(ImGui::InputFloat3("Light position", glm::value_ptr(lightPos)))
                program->Get("lightPos")->Set(lightPos);
            if(ImGui::Checkbox("Use phong", &blinn))
                program->Get("blinn")->Set(blinn);
            program->UnUse();
            ImGui::End();
        }

        // Rendering.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(core.mWindow);

        // Poll and handle events (inputs, window resize, etc.).
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                    using namespace meov::core;
                    const auto &keysym = event.key.keysym;
                    switch(keysym.sym) {
                        case SDLK_s: camera->Move(Camera::Direction::Backward, clock.Delta()); break;
                        case SDLK_w: camera->Move(Camera::Direction::Forward, clock.Delta()); break;
                        case SDLK_a: camera->Move(Camera::Direction::Left, clock.Delta()); break;
                        case SDLK_d: camera->Move(Camera::Direction::Right, clock.Delta()); break;
                        default: break;
                    }
                } break;
                case SDL_MOUSEBUTTONDOWN: {
                    const glm::vec2 current{ event.button.x, event.button.y };
                    if(current.x < scenePos.x || current.y < scenePos.y) break;
                    if(current.x > scenePos.x + sceneSize.x || current.y > scenePos.y + sceneSize.y) break;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                    isMousePressed = true;
                    lastMouseCoords = current;
                } break;
                case SDL_MOUSEMOTION: {
                    if(!isMousePressed)
                        break;

                    const glm::vec2 current{ event.button.x, event.button.y };
                    const glm::vec2 offset{
                        current.x - lastMouseCoords.x,
                        lastMouseCoords.y - current.y
                    };
                    lastMouseCoords = current;
                    camera->OnMouseMove(offset.x, offset.y);
                } break;
                case SDL_MOUSEBUTTONUP: {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    isMousePressed = false;
                } break;
                case SDL_MOUSEWHEEL: {
                    camera->OnMouseScroll(event.wheel.preciseY);
                } break;
                case SDL_WINDOWEVENT:
                    if(event.window.windowID != SDL_GetWindowID(core.mWindow)) {
                        break;
                    }
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        glViewport(0, 0, event.window.data1, event.window.data2);
                        break;
                    } else if(event.window.event != SDL_WINDOWEVENT_CLOSE) {
                        break;
                    }
                case SDL_QUIT:
                    done = true;
                default:
                    break;
            }
        }
    }

    buffer.Destroy();  // Clean frame buffer.

    return 0;
}
