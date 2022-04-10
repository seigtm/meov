#include "common.hpp"

#include "node.hpp"

namespace meov::scene {

Node::Node(core::Core &core, const std::string &name, const std::weak_ptr<Node> &parent)
    : core::CoreHolder{ core }
    , utilities::NamedObject{ name }
    , mParent{ parent } {
}

bool Node::AddChild(const std::shared_ptr<Node> &child) {
    return mChildren.insert(child).second;
}

bool Node::RemoveChild(const std::shared_ptr<Node> &child) {
    return mChildren.erase(child) != 0;
}

bool Node::RemoveChild(const std::string &childName) {
    return RemoveChild(GetChild(childName));
}

std::weak_ptr<Node> Node::GetParent() const {
    return mParent;
}
std::set<std::shared_ptr<Node>> Node::GetChildren() const {
    return mChildren;
}
std::shared_ptr<Node> Node::GetChild(const std::string &name) const {
    const auto found {
        std::find_if(
            mChildren.begin(), mChildren.end(),
            [&name](const std::shared_ptr<Node> &child) { return child->GetName() == name; })
    };
    if (found == mChildren.end()) {
        return nullptr;
    }
    return *found;
}

std::weak_ptr<Node> Node::GetRoot() const {
    if (this->IsRoot()) {
        return {};
    }
    if (const auto parent{ mParent.lock() }; parent) {
        std::weak_ptr root{ parent->GetRoot() };
        if (root.expired()) {
            return mParent;
        } else {
            return root;
        }
    }

    return {};
}

std::shared_ptr<Node> Node::FindChild(const std::string &name) const {
    for(const auto &child : mChildren) {
        if (child && child->GetName() == name) {
            return child;
        }
        if (auto found{ child->FindChild(name) }; found) {
            return found;
        }
    }
    return nullptr;
}

bool Node::IsRoot() const {
    return !mParent.expired();
}


}  // namespace meov::scene