#pragma once

#include "initializer_listener.hpp"

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

namespace meov::utils {

class Initializer;

class InitializerFactory {
public:
	using Constructor = std::function<std::shared_ptr<Initializer>(InitializerListener *)>;

	static std::shared_ptr<Initializer> load(const std::string &name, InitializerListener *listener);

private:
	static std::unordered_map<std::string, Constructor> sStorage;
};

} // namespace meov::utils
