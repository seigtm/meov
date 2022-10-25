#include "common.hpp"

#include "object.hpp"

namespace meov::core {

Object::Object(std::string &&name)
    : mixin::Named{ std::move(name) } {
}

void Object::PreDraw(Graphics &g) {
    if (!Enabled())
        return;
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PreDraw(g); });
}

void Object::Draw(Graphics &g) {
    if (!Enabled())
        return;
    forEachChildren([&g](const std::shared_ptr<Object> &child) {
        child->PreDraw(g);
        child->Draw(g);
        child->PostDraw(g);
    });
    ForEachComponent([&g](components::Component::Shared &comp) { comp->Draw(g); });
}

void Object::PostDraw(Graphics &g) {
    if (!Enabled())
        return;
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PostDraw(g); });
}

void Object::PreUpdate(double delta) {
    CheckDeadGuys();
    if (!Enabled())
        return;
    ForEachComponent([delta](components::Component::Shared &comp) { comp->PreUpdate(delta); });
}

void Object::Update(double delta) {
    if (!Enabled())
        return;
    forEachChildren([delta](const std::shared_ptr<Object> &child) {
        child->PreUpdate(delta);
        child->Update(delta);
        child->PostUpdate(delta);
    });
    ForEachComponent([delta](components::Component::Shared &comp) { comp->Update(delta); });
}

void Object::PostUpdate(double delta) {
    if (!Enabled())
        return;
    ForEachComponent([delta](components::Component::Shared &comp) { comp->PostUpdate(delta); });
}

bool Object::Enabled() const {
    return mEnabled;
}
void Object::Enable() {
    mEnabled = true;
}
void Object::Disable() {
    mEnabled = false;
}

void Object::IWannaDead() {
    mIWannaDead = true;
}
bool Object::WannaDead() const {
    return mIWannaDead;
}

void Object::setParent(Object *parent) {
    mParent = parent;
}

std::shared_ptr<Object> Object::addChild(std::shared_ptr<Object> &&child) {
    if (child == nullptr)
        return nullptr;
    if (find(child->Name()) != nullptr)
        return nullptr;
    child->setParent(this);
    return mChildren.emplace_back(std::move(child));
}

void Object::removeChild(const std::shared_ptr<Object> &child) {
    if (child == nullptr)
        return;

    auto removed = std::remove_if(mChildren.begin(), mChildren.end(),
    [&child](const std::shared_ptr<Object> &found) {
        return found == child;
    });
    if (removed != mChildren.end())
        mChildren.erase(removed, mChildren.end());
}

void Object::removeChild(const std::string &name) {
    if (name.empty())
        return;

    auto removed = std::remove_if(mChildren.begin(), mChildren.end(),
    [&name](const std::shared_ptr<Object> &found) {
        return found->Name() == name;
    });
    if (removed != mChildren.end())
        mChildren.erase(removed, mChildren.end());
}

std::vector<std::shared_ptr<Object>> Object::children() const {
    return mChildren;
}

size_t Object::childrenCount() const {
    return mChildren.size();
}

std::shared_ptr<Object> Object::find(const std::string &name, bool recursive) const {
    if (name.empty())
        return nullptr;

    for (auto &child : mChildren) {
        if (child->Name() == name)
            return child;
        if (!recursive)
            continue;
        if (auto found{ child->find(name, recursive) }; found)
            return found;
    }
    return nullptr;
}

void Object::CheckDeadGuys() {
    auto removed = std::remove_if(mChildren.begin(), mChildren.end(),
        [](const auto &child){ return child->WannaDead(); });
    if (removed != mChildren.end())
        mChildren.erase(removed, mChildren.end());
}

}  // namespace meov::core
