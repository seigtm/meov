#include <common>

#include "editor/editor.hpp"

#include <core/core.hpp>
#include <core/scene/scene.hpp>
#include <utils/time/time_utils.hpp>

#include "editor/windows/windows.hpp"

namespace meov::editor {

Editor::Editor(std::unique_ptr<core::Core> &&core) : mCore{ std::move(core) } {
	mWindowManager = std::make_shared<Window::Manager>();

	if (mCore != nullptr)
		mCore->Initialize();

	if (auto sceneView{ mWindowManager->getAs<Window::Scene>("scene") }; sceneView)
		sceneView->Select(mCore->GetFrameBuffer());
	if (auto sceneTreeView{ mWindowManager->getAs<Window::SceneTree>("scene_tree") }; sceneTreeView)
		sceneTreeView->Select(mCore->GetScene());

	if (auto logView{ mWindowManager->getAs<Window::Log>("log") }; logView)
		utils::LogUtils::Instance()->GetLogStorage()->Subscribe(logView);
}

int Editor::run() {
	if (mCore == nullptr)
		return -1;

	utils::time::Clock clock{};
	while(mCore->IsRunning()) {
		clock.Update();

		startFrame();
		update(clock.Delta());
		mCore->Draw();
		serialize();
		renderFrame();

		mCore->HandleEvents();
	}

	return core::Core::SUCCESS;
}

void Editor::startFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(mCore->GetWindow());
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
	mCore->StartFrame();
}

void Editor::renderFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	mCore->RenderFrame();
}
void Editor::serialize() {
	mWindowManager->Draw();
}

void Editor::update(const double delta) {
	mCore->Update(delta);
	if (auto propertiesView{ mWindowManager->getAs<Window::Properties>("properties") }; propertiesView)
		propertiesView->Select(mCore->GetScene()->GetSelectedObjects());
}

} // namespace meov::editor
