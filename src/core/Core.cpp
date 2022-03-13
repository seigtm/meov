#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"

#include "Core.hpp"

namespace meov::core {

Core::Core(std::vector<std::string> &&argv)
	: mInitTasks{
		std::make_unique<utilities::Initializer>(this, "SDL",
			[] {
				if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
					LOGF << "Error: " << SDL_GetError();
					return false;
				}
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, AppInfo::GLSLVersionMajor());
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, AppInfo::GLSLVersionMinor());
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

				// Create window with graphics context.
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
				SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
				return true;
			},
			[] {
				SDL_Quit();
				return true;
			}
		),
		std::make_unique<utilities::Initializer>(this, "SDL Window",
			[&win = this->mWindow, &ctx = this->mWinContext] {
				win = SDL_CreateWindow(
					meov::AppInfo::Name().c_str(),
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					1680, 960,
					SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
				);
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
				SDL_GL_DeleteContext(ctx); ctx = nullptr;
				SDL_DestroyWindow(win); win = nullptr;
				return true;
			}
		),
		std::make_unique<utilities::Initializer>(this, "OpenGL",
			[] {
				glbinding::Binding::initialize(
					[](const char* name) {
						return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name);
					}
				);
				glEnable(GL_DEPTH_TEST);

#if defined(_DEBUG)
				LOGD << "Debug callbacks initialization";
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback((GLDEBUGPROC)meov::utils::OpenGLLogCallback, nullptr);

				SDL_LogSetOutputFunction(meov::utils::SDLLogCallback, nullptr);
#endif
				return true;
			},
			[] {
				return true;
			}
		),
		std::make_unique<utilities::Initializer>(this, "ImGui",
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
				if (!ImGui_ImplSDL2_InitForOpenGL(win, ctx)) return false;
				if (!ImGui_ImplOpenGL3_Init(AppInfo::GLSLVersion().c_str())) return false;
				return true;
			},
			[] {
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplSDL2_Shutdown();
				ImGui::DestroyContext();
				return true;
			}
		)
	}
{ }

Core::ExecutionResult Core::Run() {
	return Core::SUCCESS;
}

void Core::OnFail(const std::string_view &) {
	exit(-1);
}

} // namespace meov::core