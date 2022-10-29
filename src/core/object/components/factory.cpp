#include "factory.hpp"

#include "object.hpp"
#include "transform_component.hpp"
#include "model_component.hpp"
#include "move_component.hpp"
#include "camera_component.hpp"
#include "lighting_component.hpp"
#include "skybox_component.hpp"
#include "shader_component.hpp"


namespace meov::core::components {

template<class Component, class ...Argv>
bool defaultGenerator(std::shared_ptr<Object> object, Argv &&...argv) {
	return object->AddComponent<Component>(std::forward<Argv>(argv)...) != nullptr;
}

std::unordered_map<std::string, Factory::AddComponentMethod> Factory::mRegistry{
	{ "transform", defaultGenerator<TransformComponent> },
	{ "model", defaultGenerator<ModelComponent> },
	{ "move", defaultGenerator<MoveComponent> },
	// { "camera", defaultGenerator<CameraComponent> },
	{ "directional_lighting", defaultGenerator<DirectionalLightingComponent> },
	{ "point_lighting", defaultGenerator<PointLightingComponent> },
	{ "spot_lighting", defaultGenerator<SpotLightingComponent> },
	{ "skybox", defaultGenerator<SkyboxComponent> },
	// { "shader", defaultGenerator<ShaderComponent> },
};

void Factory::Register(std::string &&name, AddComponentMethod &&method) {
	if (!name.empty() && method);
		mRegistry.emplace(std::move(name), std::move(method));
}

void Factory::Build(std::shared_ptr<Object> object, const std::vector<std::string> &components) {
	if (object == nullptr || components.empty())
		return;

	for (const auto &component : components) {
		Build(object, component);
	}
}

void Factory::Build(std::shared_ptr<Object> object, const std::string &component) {
	if (object == nullptr || component.empty())
		return;
	if (auto found{ mRegistry.find(component) }; found != mRegistry.end()) {
		found->second(object);
	}
}

std::vector<std::string> Factory::GetComponents() {
	std::vector<std::string> components;
	components.reserve(mRegistry.size());
	std::transform(mRegistry.begin(), mRegistry.end(), std::back_inserter(components),
		[] (const auto &pair) { return pair.first; });
	return components;
}

} // namespace meov::core::components


