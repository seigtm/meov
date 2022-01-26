#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Test.hpp"

int main(int, char**) {
    MEOV::Utils::Log::Instance()->Initialize();

    LOGI << "SDL Initialization";
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        LOGF << "Error: " << SDL_GetError();
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MEOV::AppInfo::GLSLVersionMajor());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MEOV::AppInfo::GLSLVersionMinor());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window with graphics context.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    LOGI << "Window Initialization";
    SDL_Window* window { SDL_CreateWindow(
        MEOV::AppInfo::Name().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI) };
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);  // Enable vsync.

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
    ImGui_ImplOpenGL3_Init(MEOV::AppInfo::GLSLVersion().c_str());

    // Our state.
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Dear ImGui windows.
    MEOV::Window::Git gitW;
    MEOV::Window::Test testW;
    testW.ToggleNoResize();
    testW.ToggleNoMove();

    // Main loop.
    LOGI << "Start main loop";
    // Main loop
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

        // Show the big demo window.
        ImGui::ShowDemoWindow(&show_demo_window);

        // Show Git info window.
        gitW.Draw();
        // Show another simple test window.
        testW.Draw();

        // Rendering.
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
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
