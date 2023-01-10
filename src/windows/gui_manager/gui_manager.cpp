#include "windows/gui_manager/gui_manager.hpp"

#include "windows/log/log_window.hpp"
#include "windows/properties/properties_window.hpp"
#include "windows/scene/scene_tree.hpp"
#include "windows/scene/scene_window.hpp"

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
	ImGui::ShowDemoWindow();
	for (auto &&[name, window] : mWindows) {
		window->Draw();
	}
}

} // namespace meov::Window
