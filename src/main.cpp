#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"
#include "TimeUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Log.hpp"

#include "FrameBuffer.hpp"
#include "mesh.h"
#include "vertex.h"
#include "shader.h"
#include "texture.h"

int main() {
    stbi_set_flip_vertically_on_load(true);
    meov::utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    LOGI << "SDL Initialization";
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        LOGF << "Error: " << SDL_GetError();
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, meov::AppInfo::GLSLVersionMajor());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, meov::AppInfo::GLSLVersionMinor());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window with graphics context.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    LOGI << "Window Initialization";
    SDL_Window* window{ SDL_CreateWindow(
        meov::AppInfo::Name().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1680, 960,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI) };
    SDL_GLContext context{ SDL_GL_CreateContext(window) };
    SDL_GL_MakeCurrent(window, context);

    if(SDL_GL_SetSwapInterval(true) < 0) {
        LOGW << "Cannot enable VSync!";
    }

    LOGI << "OpenGL Initialization";
    glbinding::Binding::initialize(
        [](const char* name) {
            return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name);
        }
    );
    glEnable(GL_DEPTH_TEST);
    LOGI << "OpenGL was initialized: " << glGetString(GL_VERSION);

#if defined(_DEBUG)
    LOGD << "Debug callbacks initialization";
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)meov::utils::OpenGLLogCallback, nullptr);

    SDL_LogSetOutputFunction(meov::utils::SDLLogCallback, nullptr);
#endif

    // Setup Dear ImGui context
    LOGI << "ImGui Initialization";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto& io{ ImGui::GetIO() };
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable viewports to drag windows outside of the main window.

    // Setup Dear ImGui style.
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends.
    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(meov::AppInfo::GLSLVersion().c_str());

    // Our state.
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };

    // Dear ImGui windows.
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW1{ new meov::Window::Log{ "First", { 1250, 850 } } };  // FIXME: ambiguous '::Ref' from Subscriber.

    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW1);
    }

    // clang-format off
    auto shader{ std::make_shared<meov::core::Shader>(
        "shaders/vertex_test.glsl",
        "shaders/fragment_test.glsl"
    ) };

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
    meov::core::OpenGL_FrameBuffer buffer{};
    buffer.create_buffers(400, 400);
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
    while(!done) {
        clock.Update();
        model = glm::rotate<float>(model, clock.Delta(), glm::vec3{ 1.0f, 1.0f, 0.0f });
        shader->Use();
        shader->Get("projection").Set(projection);
        shader->Get("view").Set(view);
        shader->Get("model").Set(model);
        shader->UnUse();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        buffer.bind();
        mesh->Draw(shader);
        buffer.unbind();

        ImGui::Begin("Scene");
        const auto [width, height]{ ImGui::GetContentRegionAvail() };
        projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        // Add rendered texture to ImGUI scene window.
        uint32_t textureID = buffer.get_texture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ width, height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();

        // Show singleton log window.
        logW1->Draw();
        // Show Git info window.
        gitW.Draw();

        // Rendering.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);

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
                    if(event.window.windowID != SDL_GetWindowID(window)) {
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

    // Cleanup.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    buffer.delete_buffers();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
