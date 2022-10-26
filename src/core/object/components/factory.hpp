#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <memory>
#include <vector>

namespace meov::core {
class Object;
} // namespace meov::core


namespace meov::core::components {

class Factory {
public:
	using AddComponentMethod = std::function<bool(std::shared_ptr<Object>)>;

	static void Register(std::string &&name, AddComponentMethod &&method);

	static void Build(std::shared_ptr<Object> object, const std::vector<std::string> &components);
	static void Build(std::shared_ptr<Object> object, const std::string &component);

	static std::vector<std::string> GetComponents();
private:
	static std::unordered_map<std::string, AddComponentMethod> mRegistry;
};

} // namespace meov::core::components
