#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Log.hpp"

#include "vertex.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"

int main(int, char**) {
    meov::Utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    LOGI << "SDL Initialization";
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
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
        1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI) };
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);  // Enable vsync.

    glbinding::Binding::initialize(
        [](const char* name) {
            return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name);
        });

    // Setup Dear ImGui context
    LOGI << "ImGui Initialization";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style.
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends.
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(meov::AppInfo::GLSLVersion().c_str());

    // Dear ImGui windows.
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW1{ new meov::Window::Log{ "First" } };  // FIXME: ambiguous '::Ref' from Subscriber.

    auto logStorage{ meov::Utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW1);
    }

    meov::core::ShaderPtr shader{ std::make_shared<meov::core::Shader>() };
    meov::core::TexturePtr texture{ std::make_shared<meov::core::Texture>(
        "../../assets/textures/best-of-the-best.png") };
    const glm::vec4 white{ 1.f, 1.f, 1.f, 1.f };
    // clang-format off
    meov::core::MeshPtr mesh{ std::make_shared<meov::core::Mesh>(meov::core::Vertices{
        meov::core::Vertex{ glm::vec3{  0.5f,  0.5f, .0f }, white, glm::vec2{ 1.0f, 1.0f } },
        meov::core::Vertex{ glm::vec3{  0.5f, -0.5f, .0f }, white, glm::vec2{ 1.0f, 0.0f } },
        meov::core::Vertex{ glm::vec3{ -0.5f, -0.5f, .0f }, white, glm::vec2{ 0.0f, 0.0f } },
        meov::core::Vertex{ glm::vec3{ -0.5f,  0.5f, .0f }, white, glm::vec2{ 0.0f, 1.0f } },
    } ) };
    // clang-format on

    meov::core::Model triangle{ mesh, shader, texture };

    // Main loop.
    LOGI << "Start main loop";
    bool done = false;
    while(!done) {
        // Poll and handle events (inputs, window resize, etc.).
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if(event.type == SDL_QUIT)
                done = true;
            if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Show singleton log window.
        logW1->Draw();
        // Show Git info window.
        gitW.Draw();

        // Rendering.
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        static const ImVec4 clear_color{ .45f, .55f, .6f, 1.f };
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        triangle.draw();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
