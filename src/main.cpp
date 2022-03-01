#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Log.hpp"

#include "mesh.h"
#include "vertex.h"
#include "shader.h"
#include "texture.h"

int main() {
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
        });
    LOGI << "OpenGL was initialized: " << glGetString(GL_VERSION);
    // if (GL_ARB_direct_state_access)


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
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

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

    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    // };
    // unsigned int indices[] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };
    // unsigned int VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    auto shader{ std::make_shared<meov::core::Shader>(
        // "shaders/vertex_test.glsl",
        // "shaders/fragment_test.glsl"
        ) };
    auto mesh{ std::make_shared<meov::core::Mesh>(
        std::vector{
            meov::core::Vertex{ glm::vec4{ 0.5f, 0.5f, .0f, 1.f }, glm::vec4{ 1.f, 0.f, 0.f, 1.f }, glm::vec2{ 1.0f, 1.0f } },
            meov::core::Vertex{ glm::vec4{ 0.5f, -0.5f, .0f, 1.f }, glm::vec4{ 0.f, 1.f, 0.f, 1.f }, glm::vec2{ 1.0f, 0.0f } },
            meov::core::Vertex{ glm::vec4{ -0.5f, -0.5f, .0f, 1.f }, glm::vec4{ 0.f, 0.f, 1.f, 1.f }, glm::vec2{ 0.0f, 0.0f } },
            meov::core::Vertex{ glm::vec4{ -0.5f, 0.5f, .0f, 1.f }, glm::vec4{ 1.f, 1.f, 0.f, 1.f }, glm::vec2{ 0.0f, 1.0f } } },
        std::vector{
            0u, 1u, 3u,  // first triangle
            1u, 2u, 3u   // second triangle
        },
        std::vector{
            meov::core::Texture{ "textures/best-of-the-best.png", meov::core::Texture::Type::Diffuse } }) };

    // Main loop.
    LOGI << "Start main loop";
    bool done = false;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    while(!done) {
        // Poll and handle events (inputs, window resize, etc.).
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch(event.type) {
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

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh->Draw(shader);

        // Show singleton log window.
        logW1->Draw();
        // Show Git info window.
        gitW.Draw();

        // Rendering.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // trans = glm::rotate(trans, 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
        // triangle.shader()->Use();
        // triangle.shader()->Get("localTransform").Set(trans);
        // triangle.draw();
        SDL_GL_SwapWindow(window);
    }

    // Cleanup.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
