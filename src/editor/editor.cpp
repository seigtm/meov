#include <common>
#include <core/core.hpp>

#include "editor/editor.hpp"

namespace meov::editor {

Editor::Editor(std::unique_ptr<core::Core> &&core) : mCore{ std::move(core) } {

}

int Editor::run() {
	if (mCore == nullptr)
		return -1;
	return mCore->Run();
}

} // namespace meov::editor
