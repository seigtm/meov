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

std::shared_ptr<Object> Scene::AddObject(const std::string_view name, const std::shared_ptr<Object> &target) {
    std::string childName{ name.empty() ? "<no_name>" : name };
    std::shared_ptr<Object> insertTarget{ target == nullptr ? mRoot : target };
    while(insertTarget->find(childName) != nullptr)
        childName += "_";
    return insertTarget->addChild(std::make_shared<Object>(std::move(childName)));
}

std::vector<std::shared_ptr<Object>> Scene::AddObjectsUnderSelected(const std::string_view name) {
    if(name.empty())
        return {};

    std::vector<std::shared_ptr<Object>> newObjects;
    for (auto selected : GetSelectedObjects()) {
        if (auto object{ selected.lock() }; object) {
            newObjects.emplace_back(AddObject(name, object))->Select();
        }
    }
    if (newObjects.empty())
        newObjects.emplace_back(AddObject(name))->Select(); //< Add to the root
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
