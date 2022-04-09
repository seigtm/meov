#pragma once

#include <vector>
#include <string>
#include <memory>

#include "initializer.hpp"

namespace meov::core {

class Core final : public utilities::Initializer::Listener {
public:
	explicit Core(std::vector<std::string> &&argv);

	enum ExecutionResult{ SUCCESS, FAIL = -1 };

	ExecutionResult Run();

	SDL_Window *mWindow{ nullptr };
	SDL_GLContext mWinContext{ nullptr };

private:
	std::vector<utilities::Initializer::Shared> mInitTasks;

	// utilities::Initializer::Listener
	void OnFail(const std::string_view &taskName) override;
};

} // namespace meov::core