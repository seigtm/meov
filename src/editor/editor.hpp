#pragma once

#include <memory>

namespace meov::core{
class Core;
class Graphics;
} // namespace meov::core


namespace meov::editor {

class Editor {
public:
	explicit Editor(std::unique_ptr<core::Core> &&core);

	[[nodiscard]] int run();

private:
	std::unique_ptr<core::Core> mCore;
};

template<class CoreType>
[[nodiscard]] static Editor make() {
	return Editor{ std::make_unique<CoreType>() };
}

} // namespace meov::editor
