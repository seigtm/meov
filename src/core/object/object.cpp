#include "common.hpp"

#include "object.hpp"

namespace meov::core {

Object::Object(std::string &&name)
    : mixin::Named{ std::move(name) } {
}

void Object::PreDraw(Graphics &g) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [&g](const std::shared_ptr<Object> &child) { child->PreDraw(g); });
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PreDraw(g); });
}

void Object::Draw(Graphics &g) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [&g](const std::shared_ptr<Object> &child) { child->Draw(g); });
    ForEachComponent([&g](components::Component::Shared &comp) { comp->Draw(g); });
}

void Object::PostDraw(Graphics &g) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [&g](const std::shared_ptr<Object> &child) { child->PostDraw(g); });
    ForEachComponent([&g](components::Component::Shared &comp) { comp->PostDraw(g); });
}

void Object::PreUpdate(double delta) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [delta](const std::shared_ptr<Object> &child) { child->PreUpdate(delta); });
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->PreUpdate(delta); });
}

void Object::Update(double delta) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [delta](const std::shared_ptr<Object> &child) { child->Update(delta); });
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->Update(delta); });
}

void Object::PostUpdate(double delta) {
    std::for_each(mChildren.rbegin(), mChildren.rend(),
        [delta](const std::shared_ptr<Object> &child) { child->PostUpdate(delta); });
    ForEachComponent([&delta](components::Component::Shared &comp) { comp->PostUpdate(delta); });
}

void Object::Serialize() {
    if(!ImGui::CollapsingHeader(Name().c_str()))
        return;

    ImGui::PushID(Name().c_str());
    ImGui::Indent();
    ForEachComponent([](components::Component::Shared &comp) {
        comp->Serialize();
        ImGui::Separator();
    });
    ImGui::Unindent();
    ImGui::PopID();
    ImGui::Spacing();
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

void Object::setParent(std::weak_ptr<Object> &&parent) {
    mParent = std::move(parent);
}

std::shared_ptr<Object> Object::addChild(std::shared_ptr<Object> &&child) {
    if (child == nullptr)
        return nullptr;
    if (find(child->Name()) != nullptr)
        return nullptr;
    child->setParent(std::enable_shared_from_this<Object>::weak_from_this());
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

}  // namespace meov::core
