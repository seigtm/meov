#pragma once

#include <vector>
#include <string>
#include <memory>

#include "core/mixins/named.hpp"
#include "core/mixins/selectable.hpp"
#include "core/object/components/component.hpp"
#include "core/object/components/holder.hpp"

namespace meov::core {

class Object
    : public mixin::Named,
      public mixin::Selectable,
      public components::Holder {
public:
    explicit Object(std::string &&name);

    virtual void PreDraw(Graphics &g);
    virtual void Draw(Graphics &g);
    virtual void PostDraw(Graphics &g);
    virtual void PreUpdate(double delta);
    virtual void Update(double delta);
    virtual void PostUpdate(double delta);

    bool Enabled() const;
    void Enable();
    void Disable();

    void IWannaDead();
    bool WannaDead() const;

    void setParent(Object *parent);
    Object *parent() const;

    std::shared_ptr<Object> addChild(std::shared_ptr<Object> &&child);
    void removeChild(const std::shared_ptr<Object> &child);
    void removeChild(const std::string &child);

    std::vector<std::shared_ptr<Object>> children() const;
    size_t childrenCount() const;
    bool empty() const;

    std::shared_ptr<Object> find(const std::string &name, bool recursive = false) const;

    template<class Method>
    std::vector<std::weak_ptr<Object>> findIf(Method &&method, bool recursive = false) const;

    template<class Method>
    void forEachChildren(Method &&method);

private:
    Object *mParent;
    std::vector<std::shared_ptr<Object>> mChildren;
    bool mIWannaDead{ false };

    bool mEnabled{ true };

    void CheckDeadGuys();
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

template<class Method>
void Object::forEachChildren(Method &&method) {
    std::for_each(mChildren.rbegin(), mChildren.rend(), method);
}

}  // namespace meov::core
