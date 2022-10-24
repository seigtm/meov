#pragma once

#include "initializer_listener.hpp"

#include <functional>
#include <memory>
#include <string>
#include <set>

namespace meov::utilities {

class Initializer final {
public:
	using Shared = std::shared_ptr<Initializer>;
	using Task = std::function<bool()>;

	Initializer(InitializerListener *parent, std::string &&name, Task &&onInit, Task &&onDestroy);
	~Initializer();

private:
	InitializerListener *mParent;
	std::string mName;
	Task mDestroyTask;

	void LogStatus(bool success,
		const std::string_view successMessage,
		const std::string_view failedMessage) const;
};

} // namespace meov::utilities