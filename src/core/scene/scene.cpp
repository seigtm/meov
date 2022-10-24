#include "common.hpp"

#include "scene.hpp"

#include "graphics.hpp"
#include "object.hpp"

namespace meov::core {

Scene::Scene()
    : mRoot{ std::make_shared<Object>("root") }
{}

void Scene::Draw(Graphics &g) {
    mRoot->PreDraw(g);
    mRoot->Draw(g);
    mRoot->PostDraw(g);
}

void Scene::Update(double delta) {
    mRoot->PreUpdate(delta);
    mRoot->Update(delta);
    mRoot->PostUpdate(delta);
}

std::vector<std::shared_ptr<Object>> Scene::AddObject(const std::string_view name) {
    if(name.empty())
        return {};

    auto push = [name] (std::shared_ptr<Object> &object, std::vector<std::shared_ptr<Object>> &storage) {
        std::string childName{ name };
        if (object->find(childName) != nullptr)
            childName += "_";
        if (auto &&obj{ object->addChild(std::make_shared<Object>(std::move(childName))) }; obj)
            storage.emplace_back(std::move(obj));
    };

    std::vector<std::shared_ptr<Object>> newObjects;
    auto selected{ GetSelectedObjects() };
    if (selected.empty()) {
        push(mRoot, newObjects);
    }
    for (auto selected : selected) {
        if (auto object{ selected.lock() }; object) {
            push(object, newObjects);
        }
    }
    return newObjects;
}

std::vector<std::weak_ptr<Object>> Scene::GetSelectedObjects() const {
    return mRoot->findIf([] (const std::shared_ptr<Object> &child) {
        return child->IsSelected();
    }, true);
}
std::vector<std::shared_ptr<Object>> Scene::GetObjects() const {
    return mRoot->children();
}

}  // namespace meov::core
