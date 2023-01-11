#include "editor/windows/windows.hpp"
#include <app_info/app_info.hpp>

namespace meov::Window {

using namespace std::string_literals;

Manager::Manager()
	: mWindows{
		{ "log"s, std::make_shared<Window::Log>("Logger", ImVec2{ 1280, 850 }) },
		{ "properties"s, std::make_shared<Window::Properties>() },
		{ "scene_tree"s, std::make_shared<Window::SceneTree>() },
		{ "scene"s, std::make_shared<Window::Scene>() },
	}
{}

void Manager::Draw() {
	if constexpr (meov::AppInfo::IsDebugMode()) {
		ImGui::ShowDemoWindow();
	}
	for (auto &&[name, window] : mWindows) {
		window->Draw();
	}
}

} // namespace meov::Window
