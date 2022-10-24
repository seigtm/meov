#pragma once

#include <unordered_map>
#include <string_view>
#include <functional>
#include <string>

#include "component.hpp"

namespace meov::core::components {

class Holder : public std::enable_shared_from_this<Holder> {
public:
    template<class T>
    T *GetComponent();

    template<class T>
    bool RemoveComponent();

    template<class T, class... Args>
    T *AddComponent(Args &&...args);

    void ForEachComponent(std::function<void(Component::Shared &)> &&method);

private:
    std::unordered_map<std::string, Component::Shared> mComponents;

    template<class T>
    static std::string GetTypeName();
};

//======================================== Implementation ========================================//

template<class T>
T *Holder::GetComponent() {
    if(auto found{ mComponents.find(GetTypeName<T>()) }; found != mComponents.end()) {
        return static_cast<T *>(found->second.get());
    }
    return nullptr;
}

template<class T>
bool Holder::RemoveComponent() {
    return mComponents.erase(GetTypeName<T>()) != 0;
}


template<class T, class... Args>
T *Holder::AddComponent(Args &&...args) {
    if(auto comp{ GetComponent<T>() }; comp != nullptr) {
        return comp;
    }

    T *component{ new T{ std::forward<Args>(args)... } };
    component->SetHolder(std::enable_shared_from_this<Holder>::weak_from_this());
    mComponents.emplace(
        GetTypeName<T>(),
        components::Component::Shared{ component });
    return component;
}

template<class T>
std::string Holder::GetTypeName() {
    return std::string{ typeid(T).name() };
}

}  // namespace meov::core::components
