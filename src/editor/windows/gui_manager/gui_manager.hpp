#pragma once

#include <unordered_map>
#include <memory>

#include "editor/windows/base/base_window.hpp"

namespace meov::Window {

class Manager {
public:
	Manager();

	void Draw();

	template<class T>
	std::shared_ptr<T> getAs(const std::string &name) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Base>> mWindows;
};

template<class T>
std::shared_ptr<T> Manager::getAs(const std::string &name) const {
	if (name.empty())
		return nullptr;

	if (auto found{ mWindows.find(name) }; found != mWindows.end())
		return std::static_pointer_cast<T>(found->second);
	return nullptr;
}

} // namespace meov::Window

