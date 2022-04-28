#define SDL_MAIN_HANDLED

#include "ImGuiFileDialog.h"

#include "common.hpp"
#include "app_info.hpp"
#include "log_utils.hpp"
#include "time_utils.hpp"

#include "windows/git_window.hpp"
#include "windows/log_window.hpp"
#include "windows/toolbar_window.hpp"

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

int main() {
    stbi_set_flip_vertically_on_load(true);
    meov::utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    meov::core::Core core{ std::vector<std::string>{} };

    std::shared_ptr graphics{ std::make_shared<meov::core::Graphics>() };

    // Our state.
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };

    // clang-format off

    auto program{ RESOURCES->LoadProgram("shaders/default") };
    graphics->PushProgram(*program);

    const glm::u8vec4 white{ 0xFF, 0xFF, 0xFF, 0xFF };
    const glm::u8vec4 black{ 0x00, 0x00, 0x00, 0xFF };
    const glm::u8vec4 red{ 0xFF, 0x00, 0x00, 0xFF };
    const glm::u8vec4 green{ 0x00, 0xFF, 0x00, 0xFF };
    const glm::u8vec4 blue{ 0x00, 0x00, 0xFF, 0xFF };

    auto modelObject{ RESOURCES->LoadModel("D:\\OneDrive\\GitHub\\meov\\assets\\models\\backpack\\backpack.obj") };

    // clang-format on
    meov::core::gl::FrameBuffer buffer;
    buffer.Initialize();

    auto camera{ std::make_shared<meov::core::Camera>(glm::vec3{ .0f, .0f, 10.0f }) };

    glm::mat4 projection{ 1 };
    glm::mat4 model{ 1.f };

    bool isMousePressed{ false };
    glm::vec2 lastMouseCoords{};

    constexpr float step{ 0.05 };

    // Visibility booleans for windows.
    bool showScene{ true };
    bool showLog{ true };
    bool showGit{ true };
    bool showCamera{ true };

    // Main loop.
    bool done{ false };
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    meov::utilities::time::Clock clock;
    // Dear ImGui windows.
    meov::Window::ToolBar toolbarW{ modelObject, done, showLog, showGit, showCamera, showScene };
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW{ new meov::Window::Log{ "Log", { 1280, 850 } } };
    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW);
    }

    LOGI << "Start main loop";
    while(!done) {
        clock.Update();
        const auto view{ camera->ViewMatrix() };
        program->Use();
        program->Get("projection")->Set(projection);
        program->Get("view")->Set(view);
        program->Get("model")->Set(model);
        program->UnUse();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(core.mWindow);
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        buffer.Bind();
        if(modelObject)
            modelObject->Draw(*graphics);
        buffer.UnBind();

        toolbarW.Draw();


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

        // Show singleton log window.
        logW->Draw(showLog);
        // Show Git info window.
        gitW.Draw(showGit);

        if(showCamera) {
            ImGui::Begin("Camera");
            const auto &pos{ camera->Position() };
            ImGui::Text("Position:    [%.2f, %.2f, %.2f]", pos.x, pos.y, pos.z);
            ImGui::Text("Yaw | Pitch: [%.2f | %.2f]", camera->Yaw(), camera->Pitch());
            ImGui::Text("Speed:       [%.2f]", camera->Speed());
            ImGui::Text("Sensitivity: [%.2f]", camera->MouseSensitivity());
            ImGui::Text("Zoom:        [%.2f]", camera->Zoom());
            ImGui::Text(
                "View: [%.2f, %.2f, %.2f, %.2f]\n"
                "      [%.2f, %.2f, %.2f, %.2f]\n"
                "      [%.2f, %.2f, %.2f, %.2f]",
                view[0].x, view[0].y, view[0].z, view[0].w,
                view[1].x, view[1].y, view[1].z, view[1].w,
                view[2].x, view[2].y, view[2].z, view[2].w);
            ImGui::Text("Object position: [%.2f, %.2f, %.2f]", model[0].w, model[1].w, model[2].w);
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
                    camera->OnMouseScroll(event.wheel.y);
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

    buffer.Destroy();

    return 0;
}
