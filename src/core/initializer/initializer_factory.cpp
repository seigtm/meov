#include <common>
#include <app_info/app_info.hpp>
#include <utils/log_utils.hpp>

#include "core/initializer/initializer.hpp"
#include "core/initializer/initializer_factory.hpp"

namespace meov::utils {

using namespace std::string_literals;

std::unordered_map<std::string, InitializerFactory::Constructor> InitializerFactory::sStorage {
	{ "stb_image"s, [] (InitializerListener *listener) {
		return std::make_shared<Initializer>(listener, "STB Image",
			[] {
				stbi_set_flip_vertically_on_load(true);
				return true;
			},
			[] {
				return true;
			}
		);
	} },
	{ "logger"s, [] (InitializerListener *listener) {
		return std::make_shared<utils::Initializer>(listener, "Logger",
			[] {
				utils::LogUtils::Instance()->Initialize();
				LOGI << "Current directory: " << fs::current_path().string();
				return true;
			},
			[] {
				return true;
			}
		);
	} },
	{ "sdl"s, [] (InitializerListener *listener) {
		return std::make_shared<Initializer>(listener, "SDL",
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
		);
	} },
	{ "opengl"s, [] (InitializerListener *listener) {
		return std::make_shared<Initializer>(listener, "OpenGL",
			[] {
				glbinding::Binding::initialize(
					[](const char* name) {
						return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name);
					});
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
		);
	} }
};

Initializer::Shared InitializerFactory::load(const std::string &name, InitializerListener *listener) {
	if (name.empty())
		return nullptr;

	if (auto found{ sStorage.find(name) }; found != sStorage.end())
		return found->second(listener);

	return nullptr;
}

} // namespace meov::utils
