/*
TODO: (16.3.22)
1. Material class. +
2. Texture ctor.
3. Node class.
4. Properties.
*/


#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"
#include "TimeUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Log.hpp"

#include "OGLFrameBuffer.hpp"
#include "ShadersProgram.hpp"
#include "mesh.h"
#include "model.hpp"
#include "vertex.h"
#include "texture.h"
#include "Graphics.hpp"

#include "Core.hpp"
#include "resource_manager.hpp"

int main() {
    stbi_set_flip_vertically_on_load(true);
    meov::utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    meov::core::Core core{ std::vector<std::string>{} };

    std::shared_ptr graphics{ std::make_shared<meov::core::Graphics>() };

    // Our state.
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };

    // Dear ImGui windows.
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW1{ new meov::Window::Log{ "First", { 1280, 850 } } };  // FIXME: ambiguous '::Ref' from Subscriber.

    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW1);
    }

    // clang-format off

    auto program{ RESOURCES->LoadProgram("shaders/default") };
    graphics->PushProgram(*program);

    const glm::u8vec4 white{ 0xFF, 0xFF, 0xFF, 0xFF };
    const glm::u8vec4 black{ 0x00, 0x00, 0x00, 0xFF };
    const glm::u8vec4 red{ 0xFF, 0x00, 0x00, 0xFF };
    const glm::u8vec4 green{ 0x00, 0xFF, 0x00, 0xFF };
    const glm::u8vec4 blue{ 0x00, 0x00, 0xFF, 0xFF };

    auto modelObject{ RESOURCES->LoadModel("models/boombox/BoomBox.gltf") };
    // meov::core::Model modelObject{"models\\boombox\\BoomBox.gltf"};

    // clang-format on
    meov::core::gl::FrameBuffer buffer;
    buffer.Initialize();

    meov::core::gl::FrameBuffer testBuffer;
    testBuffer.Initialize();
    glm::mat4 projection{ 1 };
    glm::mat4 view{ 1.f };
    glm::mat4 model{ 1.f };

    constexpr float step{ 10 };
    view = glm::translate(view, glm::vec3{ 0.0f, 0.0f, -1.0f });

    // Main loop.
    LOGI << "Start main loop";
    bool done = false;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

    meov::utilities::time::Clock clock;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!done) {
        clock.Update();
        model = glm::rotate<float>(model, clock.Delta(), glm::vec3{ 1.0f, 1.0f, 0.0f });
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
        if (modelObject)
            modelObject->Draw(*graphics);
        buffer.UnBind();

        ImGui::Begin("Scene");
        const auto [width, height]{ ImGui::GetContentRegionAvail() };
        projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        // Add rendered texture to ImGUI scene window.
        uint32_t textureID = buffer.GetFrameTexture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ width, height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();

        // Show singleton log window.
        logW1->Draw();
        // Show Git info window.
        gitW.Draw();

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
                    auto& keysym = event.key.keysym;
                    LOGD << "Key pressed: " << SDL_GetKeyName(keysym.sym);
                    glm::vec3 velocity{};
                    switch(keysym.sym) {
                        case SDLK_s: velocity.z -= step; break;
                        case SDLK_w: velocity.z += step; break;
                        case SDLK_a: velocity.x += step; break;
                        case SDLK_d: velocity.x -= step; break;
                    }
                    if(velocity != glm::vec3{}) {
                        view = glm::translate(view, velocity);
                    }
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
