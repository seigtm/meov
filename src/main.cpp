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
#include "vertex.h"
#include "texture.h"

#include "settings.hpp"

#include "Core.hpp"

int main() {
    stbi_set_flip_vertically_on_load(true);
    meov::utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    meov::core::Core core{ std::vector<std::string>{} };

    // Our state.
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };

    // Dear ImGui windows.
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW1{ new meov::Window::Log{ "First", { 1280, 850 } } };  // FIXME: ambiguous '::Ref' from Subscriber.

    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW1);
    }

    // FIXME: erase this shit later, it's for Settings tests!
    auto& inst{ meov::utilities::Settings::Instance() };
    LOGI << "Settings[Window][Height] = " << inst["Window"]["Width"].GetInt();

    // clang-format off
    auto vertShader{ std::make_shared<meov::core::shaders::Shader>() };
    vertShader->Initialize(meov::core::shaders::ShaderType::Vertex);

    auto fragShader{ std::make_shared<meov::core::shaders::Shader>() };
    fragShader->Initialize(meov::core::shaders::ShaderType::Fragment);

    meov::core::shaders::Program program;
    program.Initialize("Default shaders program");
    program.Attach(vertShader);
    program.Attach(fragShader);

    const glm::u8vec4 white{ 0xFF, 0xFF, 0xFF, 0xFF };
    const glm::u8vec4 black{ 0x00, 0x00, 0x00, 0xFF };
    const glm::u8vec4 red{ 0xFF, 0x00, 0x00, 0xFF };
    const glm::u8vec4 green{ 0x00, 0xFF, 0x00, 0xFF };
    const glm::u8vec4 blue{ 0x00, 0x00, 0xFF, 0xFF };

    auto mesh{ std::make_shared<meov::core::Mesh>(
        std::vector{
            // front
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, white, glm::vec2{ 1.0f, 1.0f } }, // 0
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, white, glm::vec2{ 1.0f, 0.0f } }, // 1
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, white, glm::vec2{ 0.0f, 0.0f } }, // 2
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, white, glm::vec2{ 0.0f, 1.0f } }, // 3

            // left
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, red, glm::vec2{ 1.0f, 1.0f } }, // 4
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, red, glm::vec2{ 1.0f, 0.0f } }, // 5
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, red, glm::vec2{ 0.0f, 0.0f } }, // 6
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, red, glm::vec2{ 0.0f, 1.0f } }, // 7

            // right
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, green, glm::vec2{ 1.0f, 1.0f } }, // 8
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, green, glm::vec2{ 1.0f, 0.0f } }, // 9
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, green, glm::vec2{ 0.0f, 0.0f } }, // 10
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, green, glm::vec2{ 0.0f, 1.0f } }, // 11

            // up
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, blue, glm::vec2{ 1.0f, 1.0f } }, // 12
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f, -0.5f }, blue, glm::vec2{ 1.0f, 0.0f } }, // 13
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f, -0.5f }, blue, glm::vec2{ 0.0f, 0.0f } }, // 14
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, blue, glm::vec2{ 0.0f, 1.0f } }, // 15

            // down
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, red, glm::vec2{ 1.0f, 1.0f } }, // 16
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f, -0.5f }, green, glm::vec2{ 1.0f, 0.0f } }, // 17
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f, -0.5f }, blue, glm::vec2{ 0.0f, 0.0f } }, // 18
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, black, glm::vec2{ 0.0f, 1.0f } }, // 19

            // back
            meov::core::Vertex{ glm::vec3{  0.5f,  0.5f,  0.5f }, black, glm::vec2{ 1.0f, 1.0f } },
            meov::core::Vertex{ glm::vec3{  0.5f, -0.5f,  0.5f }, black, glm::vec2{ 1.0f, 0.0f } },
            meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f,  0.5f }, black, glm::vec2{ 0.0f, 0.0f } },
            meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f,  0.5f }, black, glm::vec2{ 0.0f, 1.0f } },
        },
        std::vector{
            // front
            0u, 1u, 3u,
            1u, 2u, 3u,

            // left
            4u, 5u, 7u,
            5u, 6u, 7u,

            // right
            8u, 9u, 11u,
            9u, 10u, 11u,

            // up
            12u, 13u, 15u,
            13u, 14u, 15u,

            // down
            16u, 17u, 19u,
            17u, 18u, 19u,

            // back
            20u, 21u, 23u,
            21u, 22u, 23u,
        },
        std::vector{
            meov::core::Texture::Make("textures/best-of-the-best.png", meov::core::Texture::Type::Diffuse)
        }
    ) };
    // clang-format on

    meov::core::gl::FrameBuffer buffer;
    buffer.Initialize();
    glm::mat4 projection{ 1 };
    glm::mat4 view{ 1.f };
    glm::mat4 model{ 1.f };

    constexpr float step{ 0.05f };
    view = glm::translate(view, glm::vec3{ 0.0f, 0.0f, -2.0f });

    // Main loop.
    LOGI << "Start main loop";
    bool done = false;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

    meov::utilities::time::Clock clock;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!done) {
        clock.Update();
        model = glm::rotate<float>(model, clock.Delta(), glm::vec3{ 1.0f, 1.0f, 0.0f });
        program.Use();
        program.Get("projection")->Set(projection);
        program.Get("view")->Set(view);
        program.Get("model")->Set(model);
        program.UnUse();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(core.mWindow);
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        buffer.Bind();
        mesh->Draw(program);
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
    vertShader->Destroy();
    fragShader->Destroy();
    program.Destroy();

    return 0;
}
