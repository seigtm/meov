#include "common.hpp"

#include "scene.hpp"

#include "graphics.hpp"
#include "object.hpp"

namespace meov::core {

void Scene::Draw(Graphics &g) {
    for(auto &&obj : mObjects) {
        if(obj && obj->Enabled()) {
            obj->PreDraw(g);
            obj->Draw(g);
            obj->PostDraw(g);
        }
    }
}

void Scene::Update(double delta) {
    for(auto &&obj : mObjects) {
        if(obj && obj->Enabled()) {
            obj->PreUpdate(delta);
            obj->Update(delta);
            obj->PostUpdate(delta);
        }
    }
}

std::shared_ptr<Object> Scene::AddObject(const std::string_view name) {
    if(name.empty())
        return nullptr;

    auto found{ std::find_if(
        mObjects.begin(), mObjects.end(),
        [name](const std::shared_ptr<Object> &object) { return object->Name() == name; }) };

    if(found != mObjects.end())
        return *found;

    return mObjects.emplace_back(std::make_shared<Object>(std::string{ name }));
}

std::vector<std::weak_ptr<Object>> Scene::GetSelectedObjects() const {
    std::vector<std::weak_ptr<Object>> objects;

    objects.reserve(mObjects.size());
    for(auto object : mObjects) {
        if(object->IsSelected())
            objects.push_back(object);
    }
    objects.shrink_to_fit();

    return objects;
}
const std::vector<std::shared_ptr<Object>> &Scene::GetObjects() const {
    return mObjects;
}

}  // namespace meov::core
