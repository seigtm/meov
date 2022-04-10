#pragma once

#include "core.hpp"

#include <set>
#include <memory>

#include "named_object.hpp"

namespace meov::scene {

class Node : public core::CoreHolder, public utilities::NamedObject {
public:
    Node(core::Core &core, const std::string &name, const std::weak_ptr<Node> &parent = {});

    bool AddChild(const std::shared_ptr<Node> &child);
    bool RemoveChild(const std::shared_ptr<Node> &child);
    bool RemoveChild(const std::string &childName);

    std::weak_ptr<Node> GetParent() const;
    std::set<std::shared_ptr<Node>> GetChildren() const;
    std::shared_ptr<Node> GetChild(const std::string &name) const;

    std::weak_ptr<Node> GetRoot() const;
    std::shared_ptr<Node> FindChild(const std::string &name) const;

    bool IsRoot() const;

    virtual void PreUpdate() = 0;
    virtual void Update() = 0;
    virtual void PostUpdate() = 0;

    virtual void PreDraw() = 0;
    virtual void Draw() = 0;
    virtual void PostDraw() = 0;

private:
    std::weak_ptr<Node> mParent;
    std::set<std::shared_ptr<Node>> mChildren;
};

} // namespace meov::scene