#pragma once

#include <vector>
#include <string>
#include <memory>

#include "named.hpp"
#include "selectable.hpp"
#include "component.hpp"
#include "holder.hpp"

namespace meov::core {

class Object
    : public mixin::Named,
      public mixin::Selectable,
      public components::Holder,
      public std::enable_shared_from_this<Object> {
public:
    explicit Object(std::string &&name);

    virtual void PreDraw(Graphics &g);
    virtual void Draw(Graphics &g);
    virtual void PostDraw(Graphics &g);
    virtual void PreUpdate(double delta);
    virtual void Update(double delta);
    virtual void PostUpdate(double delta);
    virtual void Serialize();  // for ImGui

    bool Enabled() const;
    void Enable();
    void Disable();

    void setParent(std::weak_ptr<Object> &&parent);

    std::shared_ptr<Object> addChild(std::shared_ptr<Object> &&child);
    void removeChild(const std::shared_ptr<Object> &child);
    void removeChild(const std::string &child);

    std::vector<std::shared_ptr<Object>> children() const;

    std::shared_ptr<Object> find(const std::string &name, bool recursive = false) const;

    template<class Method>
    std::vector<std::weak_ptr<Object>> findIf(Method &&method, bool recursive = false) const;

private:
    std::weak_ptr<Object> mParent;
    std::vector<std::shared_ptr<Object>> mChildren;

    bool mEnabled{ true };
};

template<class Method>
std::vector<std::weak_ptr<Object>> Object::findIf(Method &&method, bool recursive) const {
    std::vector<std::weak_ptr<Object>> result;
    for (const auto &child : mChildren) {
        if (method(child))
            result.push_back(child);

        if (!recursive)
            continue;

        if (auto stack{ child->findIf(method, recursive) }; !stack.empty())
            result.insert(result.end(), stack.begin(), stack.end());
    }
    return result;
}

}  // namespace meov::core
