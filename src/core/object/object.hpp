#pragma once

#include <vector>
#include <string>

#include "Named.h"
#include "component.hpp"

namespace meov::core {

class Object
    : public mixin::Named,
      public std::enable_shared_from_this<Object> {
public:
    explicit Object(std::string &&name);

    virtual void Draw(Graphics &g);
    virtual void Update(double delta);
    virtual void Serialize();  // for ImGui

    template<class T>
    T *GetComponent(std::string_view name);

    template<class T, class... Args>
    T *AddComponent(std::string_view name, Args &&...args);

protected:
    std::vector<components::Component::Shared> mComponents;
};

template<class T>
T *Object::GetComponent(std::string_view name) {
    if(name.empty())
        return nullptr;

    auto found{
        std::find_if(
            mComponents.begin(), mComponents.end(),
            [name](const auto &comp) {
                return comp && comp->Name() == name;
            })
    };
    if(found == mComponents.end())
        return nullptr;

    return static_cast<T *>(found->get());
}

template<class T, class... Args>
T *Object::AddComponent(std::string_view name, Args &&...args) {
    if(name.empty())
        return nullptr;

    auto found{
        std::find_if(
            mComponents.begin(), mComponents.end(),
            [name](const auto &comp) {
                return comp && comp->Name() == name;
            })
    };
    if(found != mComponents.end())
        return static_cast<T *>(found->get());

    T *component{ new T{ std::forward<Args>(args)... } };
    mComponents.push_back(components::Component::Shared{ component });
    return component;
}


}  // namespace meov::core
